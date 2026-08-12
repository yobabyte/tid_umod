#!/usr/bin/env python3

import sys
import argparse
from struct import pack
from intelhex import IntelHex

"""
Features/fixes:
    Short/Long key: change function: done
    RSSI/S-meter meter: in progress
    Fix Mode override: in progress
    Fix inverted colors for CT/DCS and FM channel
    Move AM mode to bottom?
    Fix frequency (FM too) pos in edit/enter mode
    Fix FM channel font and pos in edit/enter mode

Notes:
    top text to power bar 4px
    top text -> freq <- bottom text 6px
    bottom text to rect 11px (12px with Y offset 7)

    move top text +2px Y (=6px)
    move freq and fm channel +4px?
    move bottom text +6px
"""

FW_VERSION = "240702"
FW_FREESPACE = 0x07C4

# Offsets: common
LOGO_CODE_CAVE_ADDR = 0x0CEE
MAIN_INIT_HOOK_ADDR = 0x8AB9
MAIN_LOOP_HOOK_ADDR = 0x8B65
MAIN_SCREEN_KEY_HANDLER_ADDR = 0x62BF
TASK_HANDLE_KEYS_ADDR = 0xC332

# Offsets: mode override
RADIO_RX_ON_HOOK_ADDR = 0x8050
RADIO_RX_OPEN_HOOK_ADDR = 0xE9C2

# Offsets: white theme
POINTER_COLOR_ADDR = 0x4BB0
FM_FREQ_TEXT_COLOR_1 = 0x4C6F
FM_FREQ_TEXT_COLOR_2 = 0x41A2

# Offsets: filter border frequency
FILTER_FREQ_RX_HOOK = 0xDAF8  # Rx
FILTER_FREQ_TX_HOOK = 0xDB11  # Tx

# Offsets: fonts & icons
LARGE_FONT_ADDR = 0x0A8A
SMALL_FONT_ADDR = 0x4D40
DUAL_ICON_ADDR = 0x022F
BEEP_ICON_ADDR = 0x024F
RSSI_ICON_ADDR = 0x02BF
POINTER_ICON_ADDR = 0x035F
BATTERY_ICON_ADDR = 0x036F

# Offsets: fixes (small font)
SMALL_FONT_FIX_ADDR_1 = 0xBA73
SMALL_FONT_FIX_ADDR_2 = 0xE1A9  # +1 byte!
SMALL_FONT_FIX_ADDR_3 = 0xE1CA  # +1 byte!
SMALL_FONT_FIX_ADDR_4 = 0xCD3C
SMALL_FONT_FIX_ADDR_5 = 0xCD46

# Offsets: UI refine
# BEEP_ICON_DRAW_HOOK = 0x923B

# Contants for the main screen
RECTANGLE_OFFSET = 6
STATUSBAR_ICON_OFFSET_Y = 2
STATUSBAR_TEXT_OFFSET_X = 19
STATUSBAR_TEXT_OFFSET_Y = 6


class MemoryMap(object):
    def __init__(self, file_path: str) -> None:
        with open(file_path, "r") as map_file:
            listing = map_file.read()
            self._mmap = self._parse_map(listing)
            self._classes = self._parse_classes(listing)

    def find_class(self, name: str) -> tuple:
        if name not in self._classes:
            raise RuntimeError(f'Memory class "{name}" not found in the memory map')
        return self._classes[name]

    def find_symbol(self, name: str) -> bytes:
        if name not in self._mmap:
            raise RuntimeError(f'Symbol "{name}" not found in the memory map')
        return self._mmap[name]

    def resolve_symbol(self, name: str) -> int:
        return self.find_symbol(name)[0]

    def _parse_map(self, listing: str) -> dict:
        # strip paging
        while True:
            page_start = listing.find("\x0CLX51 LINKER/LOCATER")
            if page_start == -1:
                break
            page_end = listing.find("\n\n\n", page_start)
            listing = listing[:page_start] + listing[page_end + 3 :]

        start = listing.find("C O D E   M E M O R Y")
        start = listing.find("\n", start) + 1
        end = listing.find("\n\n", start)
        memory_map = listing[start:end].splitlines()
        memory_map = (x.split() for x in memory_map)
        return {x[-1]: (int(x[0][:-1], 16), int(x[2][:-1], 16)) for x in memory_map if x[-1] != "**GAP**"}

    def _parse_classes(self, listing: str) -> dict:
        start = listing.find("ACTIVE MEMORY CLASSES OF MODULE")
        start = listing.find("=\n", start) + 2
        end = listing.find("\n" * 3, start)
        classes = listing[start:end].splitlines()
        return {x[46:]: (int(x[14:20].strip(), 16), int(x[36:42].strip(), 16)) for x in classes if x[37] != " "}


class Patch(object):
    def __init__(self, addr: int, max_size: int = -1, desc: str = "") -> None:
        self.addr = addr
        self.desc = desc
        self.max_size = max_size

    def apply(self, firmware: bytes) -> bytes:
        raise NotImplementedError

    def _replace(self, firmware: bytes, new_bytes: bytes) -> bytes:
        if len(firmware) < self.addr:
            raise ValueError("Patch address is out of bounds")

        if self.max_size != -1 and len(new_bytes) > self.max_size:
            return False

        return firmware[: self.addr] + new_bytes + firmware[self.addr + len(new_bytes) :]


class BytePatch(Patch):
    """
    Replaces bytes at the specified address.
    """

    def __init__(self, addr: int, bytes_or_cb: callable, desc: str = "") -> None:
        super().__init__(addr, desc=desc)
        self._bytes_or_cb = bytes_or_cb

    def apply(self, firmware: bytes) -> bytes:
        if callable(self._bytes_or_cb):
            new_bytes = self._bytes_or_cb(firmware)
        else:
            new_bytes = bytes(self._bytes_or_cb)

        return self._replace(firmware, new_bytes)


class BranchPatch(Patch):
    """
    Inserts or replaces a branch instruction at the specified address.
    """

    TYPE_LJMP = 0x02
    TYPE_LCALL = 0x12

    def __init__(
        self,
        addr: int,
        branch_type: int,
        target_addr: int,
        fit_to_size: int = -1,
        desc: str = "",
    ) -> None:
        if branch_type not in (self.TYPE_LJMP, self.TYPE_LCALL):
            raise RuntimeError("Unknown branch instruction")
        super().__init__(addr, desc=desc)
        self._branch_type = branch_type
        self._target_addr = target_addr
        self._fit_to_size = fit_to_size

    def apply(self, firmware: bytes) -> bytes:
        trampoline = pack(">BH", self._branch_type, self._target_addr)
        if self._fit_to_size > len(trampoline):
            trampoline = trampoline + (b"\x00" * (self._fit_to_size - len(trampoline)))  # nops
        return self._replace(firmware, trampoline)


class PatchGroup(Patch):
    def __init__(self, patches: list, desc: str = "") -> None:
        super().__init__(0, desc=desc)
        self._patches = patches

    def apply(self, firmware: bytes) -> bytes:
        for patch in self._patches:
            firmware = patch.apply(firmware)

        return firmware


def extract_firmware_version(firmware: bytes) -> str:
    pos = firmware.find(b"POWER\x00GMRS_")
    if not pos:
        raise RuntimeError("Unable to extract firmware version")
    return firmware[pos + 11 : pos + 17].decode()


def create_killstun_patch(addr, memory_map) -> BranchPatch:
    return BranchPatch(
        addr,
        BranchPatch.TYPE_LCALL,
        memory_map.resolve_symbol("?PR?_KILLSTUN_CHECK_HOOK?HOOKS"),
        fit_to_size=4,
        desc=f"Killstun hook ({addr:04X})",
    )


def create_filter_freq_check_patch(addr, memory_map) -> BranchPatch:
    return BranchPatch(
        addr,
        BranchPatch.TYPE_LCALL,
        memory_map.resolve_symbol("?PR?_RFFILTER_CHECK_FREQ_HOOK?HOOKS"),
        fit_to_size=8,
        desc=f"Filter hook ({addr:04X})",
    )


def create_powerbar_patch(addr, max_size, memory_map, mod_data):
    symbol = memory_map.find_symbol("?PR?UMOD_DRAWPOWERMETER?UMOD")
    if symbol[1] > max_size:
        raise RuntimeError(f"Function uMod_DrawPowerMeter() is too big! ({symbol[1]-max_size} bytes exceeding)")
    return BytePatch(addr, mod_data[symbol[0] : symbol[0] + symbol[1]], "Power bar draw code")


def create_logo_draw_patch(max_size, memory_map, mod_data):
    symbol = memory_map.find_symbol("?PR?UMOD_DRAWLOGOHOOK?UMOD")
    if symbol[1] > max_size:
        raise RuntimeError("Function uMod_DrawLogoHook() is too big!")
    patch_data = list(mod_data[symbol[0] : symbol[0] + symbol[1]])
    if patch_data[-4] != 0x12 or patch_data[-1] != 0x22:
        raise RuntimeError("Wrong tail in uMod_DrawLogoHook()")
    patch_data[-4] = 0x02 # LJMP
    patch_data[-1] = 0x00 # NOP
    patch_data += b"\0" * (max_size - len(patch_data))  # fill NOPs
    return BytePatch(symbol[0], bytes(patch_data), "Replace boot logo")


def create_logo_code_cave_patch(memory_map, mod_data):
    symbol = memory_map.find_class("CODE_BMPCAVE")
    if symbol[1] > 960:
        raise RuntimeError('CODE_BMPCAVE segment is too big (see "menu.c")!')
    return BytePatch(symbol[0], mod_data[symbol[0] : symbol[0] + symbol[1]], "Mod menu code")


def create_font_code_cave_patch(memory_map, mod_data):
    symbol = memory_map.find_class("CODE_FNTCAVE")
    if symbol[1] > 126:
        raise RuntimeError('CODE_FNTCAVE segment is too big (see "_fntcave.c")!')
    return BytePatch(symbol[0], mod_data[symbol[0] : symbol[0] + symbol[1]], "Misc code")


def create_test_mode_code_cave_patch(memory_map, mod_data):
    symbol_code = memory_map.find_class("CODE_TSTCAVE")
    symbol_const = memory_map.find_class("CONST_TSTCAVE")
    segment_size = symbol_code[1] + symbol_const[1]
    if (symbol_code[1] + symbol_const[1]) > 61:
        raise RuntimeError('CODE_TSTCAVE/CONST_TSTCAVE segments is too big (see "_tstcave.c")!')
    return BytePatch(symbol_code[0], mod_data[symbol_code[0] : symbol_code[0] + segment_size], "Misc code")


def create_status_text_font_color_patch(addr, memory_map, desc=""):
    return BranchPatch(
        addr,
        BranchPatch.TYPE_LCALL,
        memory_map.resolve_symbol("?PR?_MEDIUM_TO_SMALL_STATUS_TEXT_HOOK?HOOKS"),
        desc=desc,
    )


def create_medium_to_small_text_patch(addr, memory_map, desc=""):
    return BranchPatch(
        addr, BranchPatch.TYPE_LCALL, memory_map.resolve_symbol("?PR?_MEDIUM_TO_SMALL_TEXT_HOOK?HOOKS"), desc=desc
    )


def create_vfoch_text_color_patch(addr, memory_map, desc=""):
    return BranchPatch(
        addr, BranchPatch.TYPE_LCALL, memory_map.resolve_symbol("?PR?_CH_VFO_TEXT_COLOR_HOOK?HOOKS"), desc=desc
    )


def create_status_bar_separator_patches(memory_map, mod_data):
    max_size = 0x1A
    symbol = memory_map.find_symbol("?PR?UMOD_DRAWSTATUSBARSEPARATORHOOK?UMOD")
    if symbol[1] > max_size:
        raise RuntimeError(
            f"Function uMod_DrawStatusBarSeparatorHook() is too big! ({symbol[1]-max_size} bytes exceeding)"
        )
    data = mod_data[symbol[0] : symbol[0] + symbol[1]]
    if symbol[1] < max_size:
        data = data + (b"\x00" * (max_size - symbol[1]))
    return PatchGroup(
        [
            BytePatch(symbol[0], data, "Status bar seperator draw function"),
            BranchPatch(0xC433, BranchPatch.TYPE_LCALL, symbol[0], desc="Hook for status bar separator draw"),
        ],
        "Status bar separator patches",
    )


def read_large_font(_) -> bytes:
    with open("Resources/font_large_ocr.bin", "rb") as f:  # font_large_spleen
        return f.read()


def read_small_font(_) -> bytes:
    with open("Resources/font_small_portfolio.bin", "rb") as f:
        return f.read()


def read_battery_icon(_) -> bytes:
    with open("Resources/icon_battery.bin", "rb") as f:
        return f.read()


def read_pointer_icon(_) -> bytes:
    with open("Resources/icon_pointer.bin", "rb") as f:
        return f.read()


def read_rssi_icon(_) -> bytes:
    with open("Resources/icon_signal.bin", "rb") as f:
        return f.read()


def read_beep_icon(_) -> bytes:
    with open("Resources/icon_beep.bin", "rb") as f:
        return f.read()


def read_dual_icon(_) -> bytes:
    with open("Resources/icon_dual.bin", "rb") as f:
        return f.read()


def create_patches(memory_map, mod_data) -> list:
    return [
        create_logo_draw_patch(113, memory_map, mod_data),
        create_logo_code_cave_patch(memory_map, mod_data),
        create_font_code_cave_patch(memory_map, mod_data),
        create_test_mode_code_cave_patch(memory_map, mod_data),
        create_status_bar_separator_patches(memory_map, mod_data),
        BranchPatch(
            0x5277, BranchPatch.TYPE_LJMP, memory_map.resolve_symbol("?PR?_OPEN_TX_HOOK?HOOKS"), desc="Hook for Tx"
        ),
        BranchPatch(
            0x5C86,
            BranchPatch.TYPE_LCALL,
            memory_map.resolve_symbol("?PR?_OPEN_RX_HOOK?HOOKS"),
            fit_to_size=4,
            desc="Hook for Rx",
        ),
        BranchPatch(
            0x61E8,
            BranchPatch.TYPE_LJMP,
            memory_map.resolve_symbol("?PR?_HANDLE_PTT1_HOOK?HOOKS"),
            desc="Hook for PTT#1 (dual watch check)",
        ),
        BranchPatch(
            0x6213,
            BranchPatch.TYPE_LJMP,
            memory_map.resolve_symbol("?PR?_HANDLE_PTT2_HOOK?HOOKS"),
            desc="Hook for PTT#2 (dual watch check)",
        ),
        BranchPatch(
            MAIN_LOOP_HOOK_ADDR,
            BranchPatch.TYPE_LJMP,
            memory_map.resolve_symbol("?PR?_MAIN_LOOP_HOOK?HOOKS"),
            desc="Hook main loop",
        ),
        BranchPatch(
            MAIN_SCREEN_KEY_HANDLER_ADDR,
            BranchPatch.TYPE_LCALL,
            memory_map.resolve_symbol("?PR?_MAIN_SCREEN_KEY_HANDLER_HOOK?HOOKS"),
            desc="Hook main screen key handler",
        ),
        BranchPatch(
            TASK_HANDLE_KEYS_ADDR,
            BranchPatch.TYPE_LJMP,
            memory_map.resolve_symbol("?PR?_TASK_HANDLE_KEYS_HOOK?HOOKS"),
            desc="Hook global key handler",
        ),
        # VHF/UHF filter boundary frequency hooks
        PatchGroup(
            [
                BranchPatch(
                    FILTER_FREQ_RX_HOOK,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_RF_FILTER_FREQ_HOOK?HOOKS"),
                    desc=f"VHF/UHF filter boundary frequency Rx hook",
                ),
                BranchPatch(
                    FILTER_FREQ_TX_HOOK,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_RF_FILTER_FREQ_HOOK?HOOKS"),
                    desc=f"VHF/UHF filter boundary frequency Tx hook",
                ),
            ],
            "Hooks for VHF/UHF filter boundary frequency",
        ),
        # Light theme hooks
        PatchGroup(
            [
                BranchPatch(
                    POINTER_COLOR_ADDR,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_POINTER_COLOR_HOOK?HOOKS"),
                    fit_to_size=9,
                    desc="Hook for the pointer color",
                ),
                BranchPatch(
                    FM_FREQ_TEXT_COLOR_1,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_FMFREQ_COLOR_HOOK?HOOKS"),
                    desc="Hook for the FM frequency text color (#1)",
                ),
                BranchPatch(
                    FM_FREQ_TEXT_COLOR_2,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_FMFREQ_COLOR_HOOK?HOOKS"),
                    fit_to_size=7,
                    desc="Hook for the FM frequency text color (#2)",
                ),
            ],
            "Hooks for light theme",
        ),
        # Resources (icons, fonts)
        BytePatch(LARGE_FONT_ADDR, read_large_font, "Replace the large font to OCR A 12x24"),
        BytePatch(SMALL_FONT_ADDR, read_small_font, "Replace the small font to Portfolio 6x8 (91 glyph)"),
        BytePatch(DUAL_ICON_ADDR, read_dual_icon, "Replace the dual watch icon"),
        BytePatch(BEEP_ICON_ADDR, read_beep_icon, "Replace the beep icon"),
        BytePatch(RSSI_ICON_ADDR, read_rssi_icon, "Replace the RSSI icon"),
        BytePatch(POINTER_ICON_ADDR, read_pointer_icon, "Replace the pointer icon"),
        BytePatch(BATTERY_ICON_ADDR, read_battery_icon, "Replace the battery icon (+ 1px height)"),
        # Small font fixes
        PatchGroup(
            [
                BytePatch(SMALL_FONT_FIX_ADDR_1, [0x22], "Fix 6x8 bitmap font draw (#1)"),
                BytePatch(SMALL_FONT_FIX_ADDR_2, [0x06], "Fix small font glyph size (#2)"),
                BytePatch(SMALL_FONT_FIX_ADDR_3, [0x06], "Fix small font glyph size (#3)"),
                BytePatch(SMALL_FONT_FIX_ADDR_4, [0] * 5, "Fix small font draw for space character (#4)"),
                BytePatch(SMALL_FONT_FIX_ADDR_5, [0] * 22, "Fix small font glyph position for numbers (#5)"),
            ],
            "Small font fixes",
        ),
        # Modulation override
        PatchGroup(
            [
                BranchPatch(
                    RADIO_RX_ON_HOOK_ADDR,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_RADIO_OPENRX_HOOK?HOOKS"),
                    desc="Hook RADIO_RxOn()",
                ),
                BranchPatch(
                    RADIO_RX_OPEN_HOOK_ADDR,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_RF_OPENRX_HOOK?HOOKS"),
                    desc="Hook RADIO_RxOpen()",
                ),
            ],
            "Hooks for RF modulation override",
        ),
        # UI refine
        PatchGroup(
            [
                # Power bar
                create_powerbar_patch(0x82C1, 310, memory_map, mod_data),
                # Icon: battery
                BytePatch(0xDDB4 + 1, [106], desc="Position of battery icon (X)"),  # 108
                BytePatch(0xDD81 + 1, [STATUSBAR_ICON_OFFSET_Y] + [0] * 9, desc="Position of battery icon (Y)"),
                # Icon: bluetooth
                BytePatch(0xD726 + 1, [72], desc="Position of bluetooth icon (X)"),
                BytePatch(
                    0xD6E9 + 1, [STATUSBAR_ICON_OFFSET_Y + 1] + [0] * 9, desc="Position of bluetooth icon (Y)"
                ),  # NOTE: +1px when moving lock icon
                # Icons: beep & dual
                BytePatch(0x923E + 1, [86], desc="Position of beep icon (X)"),
                BytePatch(0x91F4 + 1, [59], desc="Position of dual icon (X)"),
                BytePatch(0x4C77, [0x7D, STATUSBAR_ICON_OFFSET_Y, 0, 0], desc="Position of beep & dual (Y)"),
                # Icon: RSSI
                BytePatch(0xDD76 + 1, [2], desc="Signal strength icon (X)"),  # 4
                BytePatch(0xDD3C + 1, [STATUSBAR_ICON_OFFSET_Y] + [0] * 9, desc="Signal strength icon (Y)"),
                # Radio settings (power, bandwidth, power save, direction, reverse mode)
                BytePatch(0x74B6 + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 0)], desc="Power level text (X)"),
                BytePatch(0x74D1 + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 1)], desc="Bandwidth text (X)"),
                BytePatch(0x9214 + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 2)], desc="Power save (X)"),
                BytePatch(0x75AC + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 3) - 1], desc="Direction text (X #1)"),
                BytePatch(0x75CB + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 3) - 1], desc="Direction text (X #2)"),
                BytePatch(0x74EC + 1, [STATUSBAR_TEXT_OFFSET_X + (8 * 4) - 2], desc="Reverse mode text (X)"),
                BytePatch(0x920B, [0x75, 0x53, STATUSBAR_TEXT_OFFSET_Y, 0, 0, 0], desc="Power save (Y)"),
                # VFO/CH, Dual Watch, Key Lock
                BytePatch(0x916A + 2, [25], desc="Bottom bar text and icon position (Y)"),  # 62 + 8
                BytePatch(0x4BCB, [00], desc="Fix keypad lock icon position (Y)"),
                BytePatch(0x91CE + 1, [2], desc="VFO/CH (X)"),
                BytePatch(0x84CD + 1, [2], desc="VFO/CH on edit (X)"),
                BytePatch(0x841A + 1, [27], desc="VFO/CH on edit (Y)"),  # MOV 0x53, Y
                # Frequency (large and medium text), FM radio channel
                BranchPatch(
                    0x86BA,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_MEDIUM_TO_SMALL_TEXT_HOOK?HOOKS"),
                    desc="Replace medium text to small text (#1)",
                ),
                BranchPatch(
                    0xA468,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_MEDIUM_TO_SMALL_TEXT_HOOK?HOOKS"),
                    desc="Replace medium text to small text (#2)",
                ),
                BytePatch(0x85F7 + 1, [108], desc="Position of FM radio channel number (X #1)"),
                BytePatch(0x85EE, [0x75, 0x53, 45], desc="Position of FM radio channel number (Y #1)"),
                BytePatch(0xA466 + 1, [108], desc="Position of FM radio channel number on input (X #2)"),
                BytePatch(0xA41D + 1, [45], desc="Position of FM radio channel number on input (Y #2)"),

                BytePatch(0x4119 + 2, [40 + 3], desc="Frequency large text position on input (Y)"),
                BytePatch(0x8571 + 2, [40 + 3], desc="Frequency/channel large text position (Y)"),
                BytePatch(0x86B1 + 1, [8 + 5], desc="Position of frequency small text (Y)"),
                # Frequency/Channel name (No Sync)
                BytePatch(0x8C0B + 2, [63 - 34], desc="NOSYNC: Channel name (Y)"),
                BytePatch(0x8CE8 + 2, [81 - 34], desc="NOSYNC: Frequency text (Y)"),
                BytePatch(0x2D8F + 2, [81 - 34], desc="NOSYNC: Frequency text on input (Y)"),
                BytePatch(0xA426 + 1, [81 - 34], desc="NOSYNC: FM radio channel on input (Y)"),
                BytePatch(0xCAA1 + 2, [63 - 34], desc="NOSYNC: FM radio text (Y)"),
                BytePatch(0xCAD1 + 2, [81 - 34], desc="NOSYNC: FM radio frequency (Y)"),
                BytePatch(0xCAFB + 2, [81 - 34], desc="NOSYNC: FM radio channel (Y)"),
                BytePatch(0x758E + 1, [80 - 8], desc="NOSYNC: CTDCS (X)"),
                BytePatch(0x7588 + 2, [109], desc="NOSYNC: CTDCS (Y)"),
                BytePatch(0x9175 + 2, [107], desc="NOSYNC: VFO/CH number(Y)"),
                BytePatch(0x8423 + 1, [109], desc="NOSYNC: VFO/CH number on input (Y)"),
                # Dialog rectangles (menu, dtmf)
                BytePatch(0xC6B5 + 2, [76 + RECTANGLE_OFFSET], desc="Dialog rectangle (Y)"),
                BytePatch(0x4BE8 + 1, [127 - (76 + RECTANGLE_OFFSET)], desc="Dialog background fill (Y)"),
                BytePatch(0x4BEA + 1, [76 + RECTANGLE_OFFSET], desc="Dialog background fill (Y)"),
                # DTMF text
                BytePatch(0x86EF + 2, [80 + RECTANGLE_OFFSET], desc="DTMF dialog header #1 (Y)"),
                BytePatch(0x8798 + 2, [80 + RECTANGLE_OFFSET], desc="DTMF dialog header #2 (Y)"),
                BytePatch(0x87FD + 2, [98 + RECTANGLE_OFFSET], desc="DTMF dialog value #1 (Y)"),
                BytePatch(0x877B + 2, [98 + RECTANGLE_OFFSET], desc="DTMF dialog value #2 (Y)"),
                # Menu text
                BytePatch(0x1B45 + 2, [81 + RECTANGLE_OFFSET], desc="Menu option name (Y)"),
                BytePatch(0x1B4B + 1, [11 + 1], desc="Menu option name (X)"),
                BytePatch(0x1B27 + 1, [99 + RECTANGLE_OFFSET + 2], desc="Menu option value clear (Y)"),
                BytePatch(0x4A93 + 2, [99 + RECTANGLE_OFFSET + 2], desc="Menu option value (Y)"),
                BytePatch(0x2BCA + 2, [99 + RECTANGLE_OFFSET + 2], desc="Menu Offset option value (Y)"),
                # A/B bottom
                BytePatch(0x0011 + 2, [81 + RECTANGLE_OFFSET], desc="Rectangle position (Y)"),
                BytePatch(0x8FC7 + 2, [85 + RECTANGLE_OFFSET], desc="Channel A name/freq (Y)"),
                BytePatch(0x904A + 2, [85 + RECTANGLE_OFFSET], desc="Channel A name/freq (Y)"),
                BytePatch(0x7F42 + 2, [103 + RECTANGLE_OFFSET], desc="Channel B name/freq (Y)"),
                BytePatch(0x8000 + 2, [103 + RECTANGLE_OFFSET], desc="Channel B name/freq (Y)"),
                BytePatch(0xE219 + 1, [83 + RECTANGLE_OFFSET], desc="Channel A Tx (Y)"),
                BytePatch(0xE21E + 1, [101 + RECTANGLE_OFFSET], desc="Channel B Tx (Y)"),
                # CT/DCS + modulation bottom
                BytePatch(0x753C + 2, [84 + RECTANGLE_OFFSET + 1], desc="CT/DCS (Y)"),
                BytePatch(0x7600 + 1, [100], desc="Modulation text (X)"),
                BytePatch(0x75FA, [0x75, 0x53, 103 + RECTANGLE_OFFSET], desc="Modulation text (Y)"),  # MOV 0x53, Y
                # Pointers
                BytePatch(0xD5C6 + 1, [84 + RECTANGLE_OFFSET], desc="Position of pointer for channel A (#1)"),
                BytePatch(0xD5D6 + 1, [84 + RECTANGLE_OFFSET], desc="Position of pointer for channel A (#2)"),
                BytePatch(0xD5E9 + 1, [102 + RECTANGLE_OFFSET], desc="Position of pointer for channel B (#1)"),
                BytePatch(0xD5B3 + 1, [102 + RECTANGLE_OFFSET], desc="Position of pointer for channel B (#2)"),
                BytePatch(0xE090 + 1, [80 + RECTANGLE_OFFSET], desc="Position of pointer for option name (#1)"),
                BytePatch(0xE097 + 1, [80 + RECTANGLE_OFFSET], desc="Position of pointer for option name (#2)"),
                BytePatch(0xE086 + 1, [100 + RECTANGLE_OFFSET], desc="Position of pointer for option value (#1)"),
                BytePatch(0xE0A1 + 1, [100 + RECTANGLE_OFFSET], desc="Position of pointer for option value (#2)"),
            ],
            "UI refine (positions)",
        ),
        PatchGroup(
            [
                create_status_text_font_color_patch(0x74B8, memory_map, "Transmit power small font"),
                create_status_text_font_color_patch(0x74D3, memory_map, "Bandwidth small font"),
                create_status_text_font_color_patch(0x74EE, memory_map, "Reverse mode small font"),
                create_status_text_font_color_patch(0x75AE, memory_map, "Offset direction small font (#1)"),
                create_status_text_font_color_patch(0x75CD, memory_map, "Offset direction small font (#2)"),
                create_status_text_font_color_patch(0x9216, memory_map, desc="Power save small font"),
            ],
            "UI refine (status bar text font and color)",
        ),
        PatchGroup(
            [
                # VFO/CH + CTDCS + Modulation text
                create_vfoch_text_color_patch(0x91CB, memory_map, "VFO/Channel Name text color"),
                create_vfoch_text_color_patch(0x84CA, memory_map, "VFO/Channel Name text color (on edit)"),
                create_vfoch_text_color_patch(0x7542, memory_map, "CTDCS text color (Sync)"),
                create_vfoch_text_color_patch(0x758B, memory_map, "CTDCS text color (No Sync)"),
                create_vfoch_text_color_patch(0x75FD, memory_map, "Modulation text color"),
                # Icons (status bar)
                BytePatch(0x4BCD + 2, [0xCE], desc="Icons color (LO)"),
                BytePatch(0x4BD5 + 1, [0x79], desc="Icons color (HI)"),
                BytePatch(0x4C7B + 2, [0xCE], desc="Beep & dual icons color (LO)"),
                BytePatch(0x4C83 + 1, [0x79], desc="Beep & dual icons color (HI)"),
                # A/B bottom
                BytePatch(0x004F + 1, [0x79], desc="Rect color (LO, #1)"),
                BytePatch(0x0084 + 1, [0x79], desc="Rect color (LO, #1)"),
                BytePatch(0x008F + 1, [0x79], desc="Rect color (LO, #1)"),
                BytePatch(0x001D + 2, [0xCE], desc="Rect color (HI, #1)"),
                BytePatch(0x0039 + 2, [0xCE], desc="Rect color (HI, #2)"),
                BytePatch(0x004C + 2, [0xCE], desc="Rect color (HI, #3)"),
                BytePatch(0x0081 + 2, [0xCE], desc="Rect color (HI, #4)"),
            ],
            "UI refine (colors)",
        ),
        PatchGroup(
            [
                BranchPatch(
                    0xDD78,
                    BranchPatch.TYPE_LJMP,
                    memory_map.resolve_symbol("?PR?_DRAW_SIGNAL_STRENGTH_HOOK?HOOKS"),
                    desc="Draw signal strength hook",
                ),
                #BytePatch(0x5E69, [0] * 3, desc="Always update signal strength"),
            ],
            "S-meter",
        ),
        PatchGroup(
            [
                BranchPatch(
                    0xD0C2,
                    BranchPatch.TYPE_LJMP,
                    memory_map.resolve_symbol("?PR?_BATTERY_UPDATE_HOOK?HOOKS"),
                    desc="Battery update hook",
                ),
                BranchPatch(
                    0xDDB6,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?_BATTERY_DRAW_HOOK?HOOKS"),
                    desc="Battery draw hook",
                ),
            ],
            "Battery hooks (draw and update)",
        ),
        # PatchGroup(
        #     [
        #         BytePatch(0x72A5, [0] * 2),
        #         BranchPatch(
        #             0x7236,
        #             BranchPatch.TYPE_LCALL,
        #             memory_map.resolve_symbol("?PR?_TIMER_HOOK_10MS?HOOKS"),
        #         ),
        #     ],
        #     "Timer hook for RSSI update (10ms)",
        # ),
        BranchPatch(
            0x7602,
            BranchPatch.TYPE_LCALL,
            memory_map.resolve_symbol("?PR?_MODULATION_TEXT_HOOK?HOOKS"),
            desc="Modulation text hook",
        ),
        PatchGroup(
            [
                BranchPatch(
                    0x8699,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?UMOD_FREQUENCYCOLORHOOK?_TSTCAVE"),
                    fit_to_size=6,
                    desc="Frequency color large",
                ),
                BranchPatch(
                    0x86B5,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?UMOD_FREQUENCYCOLORHOOK?_TSTCAVE"),
                    desc="Frequency color small",
                ),
                BranchPatch(
                    0x42A1,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?UMOD_FREQUENCYCOLORHOOK?_TSTCAVE"),
                    fit_to_size=6,
                    desc="Frequency color large on input",
                ),
                BranchPatch(
                    0x42BD,
                    BranchPatch.TYPE_LCALL,
                    memory_map.resolve_symbol("?PR?UMOD_FREQUENCYCOLORHOOK?_TSTCAVE"),
                    desc="Frequency color small on input",
                ),
            ],
            desc="Frequency color hooks",
        ),
    ]


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        "TIDRADIO firmware patcher for uMod",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("-i", "--infile", type=str, required=True, help="input firmware file")
    parser.add_argument("-o", "--outfile", type=str, required=True, help="output firmware file")
    parser.add_argument("--mapfile", type=str, required=True, help="keil map file")
    parser.add_argument("--hexfile", type=str, required=True, help="mod hex file")
    # parser.add_argument("-d", "--debug", type=bool)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    with open(args.infile, "rb") as fw_file:
        firmware = fw_file.read()

    with open(args.hexfile, "r") as hex_file:
        fwmod = IntelHex(hex_file).tobinstr()

    firmware_version = extract_firmware_version(firmware)
    if firmware_version != FW_VERSION:
        raise RuntimeError("Unsupported firmware version")

    # Prepare firmware patches
    fwmod_memory_map = MemoryMap(args.mapfile)
    patches = create_patches(fwmod_memory_map, fwmod)

    mod_size = len(fwmod) - len(firmware)
    if mod_size > FW_FREESPACE:
        raise RuntimeError(f"Mod is too big ({mod_size-FW_FREESPACE} bytes exceeding).")

    patches_total = 0
    for patch in patches:
        if isinstance(patch, PatchGroup):
            patches_total += len(patch._patches)
        else:
            patches_total += 1

    # Apply firmware patches
    print(f"Patches total: {patches_total}")
    for patch in patches:
        print(
            f'Applying patch "{patch.desc}"'
            + (f" at 0x{patch.addr:04X}" if not isinstance(patch, PatchGroup) else "")
            + " ..."
        )
        firmware = patch.apply(firmware)

    # Append mod to firmware
    firmware += fwmod[len(firmware) :]

    with open(args.outfile, "wb") as fw_file:
        fw_file.write(firmware)

    print(f"Output firmware size: {len(firmware)} bytes (+ {mod_size} bytes)")


if __name__ == "__main__":
    try:
        main()
    except Exception as ex:
        sys.exit(f"ERROR: {ex}")
