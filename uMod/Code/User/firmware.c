#include "ta3782f.h"
#include "firmware_offsets.h"

// Bits
uint8_t bdata _BITS_25 _at_ 0x25;
uint8_t bdata _BITS_26 _at_ 0x26;
uint8_t bdata _BITS_29 _at_ 0x29;
uint8_t bdata _BITS_2D _at_ 0x2d;
uint8_t bdata _BITS_2E _at_ 0x2E;

//
// Flashlight & LEDs
//
sbit LAMP = P3^5;

sbit TX_ULED = P1^2;
sbit TX_VLED = P3^1;

sbit RX_ULED = P1^0;
sbit RX_VLED = P3^0;


uint8_t xdata INPUT_KeyPressed _at_ INPUT_PRESSED_KEY_ADDR;
//uint8_t xdata INPUT_LongPressKey _at_ INPUT_LONG_PRESS_KEY_ADDR;
uint8_t xdata INPUT_LongPressTime _at_ INPUT_LONG_PRESS_TIME_ADDR; // half a sec? 0.75 sec?

sbit INPUT_IsKeyHandled = _BITS_29 ^ 3;
sbit INPUT_UpDownKeyState = _BITS_29 ^ 7;

//
// RF / Radio
//
uint16_t xdata RF_RegValue _at_ RF_READ_VALUE_ADDR; // buffer for result of RF_Read() calls
sbit RADIO_IsRxOn = _BITS_25 ^ 1;
sbit RADIO_IsTxOn = _BITS_26 ^ 3;
sbit RADIO_IsAmMod = _BITS_25 ^ 2;
sbit RADIO_IsNoaaMode = _BITS_29 ^ 1;
sbit RADIO_IsRssiUpdated = _BITS_2E ^ 6;
sbit FMRADIO_IsActive = _BITS_2D ^ 5;

sbit VRX_CTRL = P4 ^ 4;
sbit URX_CTRL = P5 ^ 5;
	
//
// Misc
//
uint8_t xdata fn_keys[6] _at_ FNKEYS_XDATA_ADDR;

int idata BATTERY_AnalogValue _at_ 0x0E;

//char xdata str_buf[9] _at_ 0x0342;
char xdata str_buf[9] _at_ 0x035a;

sbit _BitArg_2D_0 = _BITS_2D ^ 0;
sbit draw_rssi_arg_0 = _BITS_2D ^ 2;
sbit smeter_full_draw = _BITS_2D ^ 1;

#define _EEPROM_Write(addr, sz, buf) \
	*(void * idata*)(EEPROM_WRITE_BUFPTR_IADDR) = (buf); \
	((void (code*)(uint8_t, uint8_t, uint8_t))(EEPROM_WRITE_ADDR))(((addr)>>8), ((addr)&0xFF), (sz))

void SETTINGS_SaveFuncKey(void) {
	_EEPROM_Write(FNKEYS_FLASH_ADDR, sizeof(fn_keys), &fn_keys);
}