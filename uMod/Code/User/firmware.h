#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

#include "bool.h"
#include "ta3782f.h"
#include "firmware_offsets.h"

typedef enum {
	KEY_NONE = 0,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_MENU,
	KEY_UP,
	KEY_DOWN,
	KEY_BACK,
	KEY_STAR,
	KEY_SIGN,
	KEY_CUSTOM = 18,
	KEY_PTT_1 = 19,
	KEY_PTT_2 = 26
} key_t;

typedef enum {
	BEEP_TONE_1 = 1,
	BEEP_TONE_2,
	BEEP_TONE_3,
	BEEP_TONE_MAX
} beep_tone_t;

typedef enum {
	KEY_FUNC_NONE = 0,
	KEY_FUNC_FM_RADIO,
	KEY_FUNC_FLASHLIGHT,
	KEY_FUNC_MONITOR,
	KEY_FUNC_RPT_TONE,
	KEY_FUNC_ALARM,
	KEY_FUNC_WEATHER,
	KEY_FUNC_MAX = KEY_FUNC_WEATHER
} key_func_t;

#define FN_SHORT_KEY 1
#define FN_LONG_KEY 4

//
// Flashlight & LEDs
//
sbit LAMP = P3^5;

sbit TX_ULED = P1^2;
sbit TX_VLED = P3^1;

sbit RX_ULED = P1^0;
sbit RX_VLED = P3^0;

//
// Timer & Watchdog
//
#define WDT_Clear() \
	((void (code*)(void))(WDT_CLEAR_ADDR))()

#define TMR_ResetFlag() \
	((void (code*)(void))(TMR_RESET_FLAG_ADDR))()
		
#define Delay_Ms(msec) \
	((void (code*)(uint16_t))(DELAY_MS_ADDR))((msec))


//
// Input
//
#define INPUT_ReadKeys() \
	((void (code*)(void))(INPUT_READ_KEYS_ADDR))()

#define INPUT_StartLongPress() \
	((void (code*)(void))(INPUT_START_LONG_PRESS_ADDR))()

extern uint8_t xdata INPUT_KeyPressed;
//extern uint8_t xdata INPUT_LongPressKey;
extern uint8_t xdata INPUT_LongPressTime; // half a sec? 0.75 sec?

extern bit INPUT_IsKeyHandled;
extern bit INPUT_UpDownKeyState;
	
#define INPUT_KEY_UP 1
#define INPUT_KEY_DOWN 0

//
// Display & UI
//
#define ST77XX_INVOFF 0x20
#define ST77XX_INVON  0x21

#define ST7735_SendCommand(cmd) \
	((void (code*)(uint8_t))(ST7735_SEND_COMMAND_ADDR))((cmd))

#define ST7735_DrawPixel(x, y, color) \
	*(uint8_t idata*)(ST7735_DRAW_PIXEL_COLOR_IADDR) = (color) >> 8; \
	((void (code*)(uint8_t, uint8_t, uint8_t))(ST7735_DRAW_PIXEL_ADDR))((x), (y), (color) & 0xFF)
	
#define Display_Fill(x, y, wh, color) \
	*(uint16_t idata*)(DISPLAY_FILL_COLOR_IADDR) = (color); \
  ((void (code*)(uint8_t, uint8_t, uint8_t))(DISPLAY_FILL_ADDR))((x), (y), (wh))

#define Display_FillRect(x, y, w, h, color) \
	*(uint16_t idata*)(DISPLAY_FILL_RECT_H_ADDR) = (h); \
	*(uint16_t idata*)(DISPLAY_FILL_RECT_COLOR_ADDR) = (color); \
  ((void (code*)(uint16_t, uint16_t, uint16_t))(DISPLAY_FILL_RECT_ADDR))((x), (y), (w) - 1)

#define _Display_DrawBitmap_Copy(buf, sz) \
	for (i = 0; i < sz; ++i) { *(uint8_t idata*)(DISPLAY_DRAW_BITMAP_BUF_ADDR + i) = (buf)[i]; }
	
#define Display_DrawBitmap_8x16(x, y, color, bg_color, buf) \
	_Display_DrawBitmap_Copy(buf, 16); \
	*(uint8_t idata*)(DISPLAY_DRAW_BITMAP_COLOR_ADDR) = (color) >> 8; \
	*(uint16_t idata*)(DISPLAY_DRAW_BITMAP_COLOR_BG_ADDR) = (bg_color); \
  ((void (code*)(uint8_t, uint8_t, uint8_t))(DISPLAY_DRAW_BITMAP_8_16_ADDR))((x), (y), (color) & 0xFF)

#define Display_DrawBitmap_16x16(x, y, color, bg_color, buf) \
	_Display_DrawBitmap_Copy(buf, 32); \
	*(uint8_t idata*)(DISPLAY_DRAW_BITMAP_COLOR_ADDR) = (color) >> 8; \
	*(uint16_t idata*)(DISPLAY_DRAW_BITMAP_COLOR_BG_ADDR) = (bg_color); \
  ((void (code*)(uint8_t, uint8_t, uint8_t))(DISPLAY_DRAW_BITMAP_16_16_ADDR))((x), (y), (color) & 0xFF)

// Helper
#define UI_SetSmallTextColor(color)\
	*(uint16_t idata*)(UI_DRAW_SMALL_TEXT_COLOR_IADDR) = (color)

#define UI_DrawSmallText_NoColor(str, x, y)\
	*(uint8_t idata*)(UI_DRAW_SMALL_TEXT_Y_IADDR) = (y); \
	((void (code*)(char*, uint8_t))(UI_DRAW_SMALL_TEXT_ADDR))((str), (x))
	
/* No glyph after W, i.e. XYZ[ and so on ... */
#define UI_DrawSmallText(str, x, y, color)\
	*(uint8_t idata*)(UI_DRAW_SMALL_TEXT_Y_IADDR) = (y); \
	*(uint16_t idata*)(UI_DRAW_SMALL_TEXT_COLOR_IADDR) = (color); \
	((void (code*)(char*, uint8_t))(UI_DRAW_SMALL_TEXT_ADDR))((str), (x))
	
#define UI_DrawMediumText(str, x, y, color)\
	*(uint8_t idata*)(UI_DRAW_MEDIUM_TEXT_Y_IADDR) = (y); \
	*(uint16_t idata*)(UI_DRAW_MEDIUM_TEXT_COLOR_IADDR) = (color); \
	((void (code*)(char*, uint8_t))(UI_DRAW_MEDIUM_TEXT_ADDR))((str), (x))

#define UI_ShowMainScreen() \
	((void (code*)())(UI_SHOW_MAIN_SCREEN_ADDR))()


//
// EEPROM
//
#define EEPROM_Read(addr, sz, buf) \
	*(void * idata*)(EEPROM_READ_BUFPTR_IADDR) = (buf); \
	((void (code*)(uint8_t, uint8_t, uint8_t))(EEPROM_READ_ADDR))(((addr)>>8), ((addr)&0xFF), (sz))

#define EEPROM_Write(addr, sz, buf) \
	*(void * idata*)(EEPROM_WRITE_BUFPTR_IADDR) = (buf); \
	((void (code*)(uint8_t, uint8_t, uint8_t))(EEPROM_WRITE_ADDR))(((addr)>>8), ((addr)&0xFF), (sz))

#define SETTINGS_Save()\
	((void (code*)(void))(SETTINGS_SAVE_ADDR))()


//
// RF / Radio
//
extern uint16_t xdata RF_RegValue; // buffer for result of RF_Read() calls
extern bit RADIO_IsRxOn;
extern bit RADIO_IsTxOn;
extern bit RADIO_IsAmMod;
extern bit RADIO_IsNoaaMode;
extern bit RADIO_IsRssiUpdated;
extern bit FMRADIO_IsActive;

//sbit VRX_CTRL = P4 ^ 4;
//sbit URX_CTRL = P5 ^ 5;
	
#define RF_Read(reg) \
	((void (code*)(uint8_t))(RF_READ_ADDR))((reg))
	
#define RF_Write(reg, hi, lo) \
  ((void (code*)(uint8_t, uint8_t, uint8_t))(RF_WRITE_ADDR))((reg), (hi), (lo))

#define RF_WriteU16(reg, value) \
	RF_Write((reg), (value) >> 8, (value) & 0xFF)

#define RF_SetAfBwAgc(mode) \
	((void (code*)(uint16_t))(RF_SET_AF_BW_AGC_ADDR))((mode))

#define RADIO_POWER_LOW 0
#define RADIO_POWER_HIGH 1
#define RADIO_OutputPower ((*(uint8_t xdata*)(0x02c2) >> 4) & 1)
	
//
// Misc
//
extern key_func_t xdata fn_keys[6];

extern int idata BATTERY_AnalogValue;

extern char xdata str_buf[9];
	
extern bit _BitArg_2D_0;
extern bit draw_rssi_arg_0;
extern bit smeter_full_draw;
	
#define strlen(str) \
	((uint8_t (code*)(const char *))(STRLEN_ADDR))((str))

#define Beep_Play(tone) \
	((void (code*)(uint8_t))(BEEP_PLAY_ADDR))((tone))

#define Keypad_HandleInput() \
	((void (code*)())(KEYPAD_HANDLER_ADDR))()

	
#define _Reset() \
	TA = 0xAA; TA = 0x55; WDCON = 0x0; \
	TA = 0xAA; TA = 0x55; WDCON = 0x80;
	
extern void SETTINGS_SaveFuncKey(void);
	
#endif