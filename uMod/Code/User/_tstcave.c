#pragma userclass (code = TSTCAVE)
#pragma userclass (const = TSTCAVE)

#include "umod.h"
#include "colors.h"
#include "firmware.h"

//
// Kill/Stun
//

void uMod_ResetKillStun(void) {
	*((uint8_t xdata*)(SETTINGS_KILL_STUN_ADDR)) &= 0xE7;

	// Full redraw
	//_BitArg_2D_0 = true;

	// Draw main screen, play beep tone 1 and save settings
	((void (code*)(void))(0xcc3a))(); 
}

//
// Frequency color
//
const uint16_t code frequency_colors[] = {
	COLOR_WHITE,
	
	COLOR_BLUE,
	0xC3CB, // blue 2

	RGB565(8, 61, 0), // green P1
	RGB565(7, 48, 1), // green 2

	COLOR_RED,
	
	RGB565(25, 52, 0), // yellow
	RGB565(31, 0, 31) // magenta
};

void uMod_FrequencyColorHook(void) {
	*(uint16_t idata*)(UI_DRAW_MEDIUM_TEXT_COLOR_IADDR) = uMod_AdjustColor(frequency_colors[settings.freq_color]);
}
