#ifndef __OFFSETS_H__
#define __OFFSETS_H__

#define BASE_FW 240702

#if (BASE_FW == 240530)

#define WDT_CLEAR_ADDR                      0xef29

#define STRLEN_ADDR                         0xecdb

#define DELAY_MS_ADDR                       0xea0d

#define KEYPAD_HANDLER_ADDR                 0xe52f // name TDB

#define DISPLAY_FILL_ADDR                   0xd434
#define DISPLAY_FILL_COLOR_IADDR            0x50

#define DISPLAY_FILL_RECT_ADDR              0xb88d
#define DISPLAY_FILL_RECT_H_ADDR            0x53
#define DISPLAY_FILL_RECT_COLOR_ADDR        0x55
																						
#define DISPLAY_DRAW_BITMAP_8_16_ADDR       0xba48
#define DISPLAY_DRAW_BITMAP_16_16_ADDR      0x9930
#define DISPLAY_DRAW_BITMAP_BUF_ADDR        0xAA
#define DISPLAY_DRAW_BITMAP_COLOR_ADDR      0x5F
#define DISPLAY_DRAW_BITMAP_COLOR_BG_ADDR   0x60

#define ST7735_SEND_COMMAND_ADDR            0xee61
#define ST7735_DRAW_PIXEL_ADDR              0xdf9f
#define ST7735_DRAW_PIXEL_COLOR_IADDR       0x6a

#define UI_DRAW_SMALL_TEXT_ADDR             0xcc9f
#define UI_DRAW_SMALL_TEXT_Y_IADDR          0x43
#define UI_DRAW_SMALL_TEXT_COLOR_IADDR      0x44
#define UI_DRAW_MEDIUM_TEXT_ADDR            0xae58
#define UI_DRAW_MEDIUM_TEXT_Y_IADDR         0x53
#define UI_DRAW_MEDIUM_TEXT_COLOR_IADDR     0x54

#define UI_SHOW_MAIN_SCREEN_ADDR            0xee21

#define BEEP_PLAY_ADDR                      0xb6c6
																	          
#define EEPROM_READ_ADDR                    0xd233
#define EEPROM_READ_BUFPTR_IADDR            0x4d
#define EEPROM_WRITE_ADDR                   0xd8c8
#define EEPROM_WRITE_BUFPTR_IADDR           0x3c

#define INPUT_READ_KEYS_ADDR                0x6dc0
#define INPUT_START_LONG_PRESS_ADDR         0x2ba8
#define INPUT_LONG_PRESS_TIME_ADDR          0x0463
#define INPUT_PRESSED_KEY_ADDR              0x0478

#define RF_READ_VALUE_ADDR                  0x02f5
#define RF_READ_ADDR                        0xc800
#define RF_WRITE_ADDR                       0xe638
#define RF_SET_AF_BW_AGC_ADDR               0xd336

#else if (BASE_FW == 240702)

// Watchdog
#define WDT_CLEAR_ADDR                      0xef94

// TODO: move to libcode
#define STRLEN_ADDR                         0xed46

// Time
#define DELAY_MS_ADDR                       0xea78

#define KEYPAD_HANDLER_ADDR                 0xe59a // name TDB

#define DISPLAY_FILL_ADDR                   0xd4a9
#define DISPLAY_FILL_COLOR_IADDR            0x50

#define DISPLAY_FILL_RECT_ADDR              0xb902
#define DISPLAY_FILL_RECT_H_ADDR            0x53
#define DISPLAY_FILL_RECT_COLOR_ADDR        0x55
																						
#define DISPLAY_DRAW_BITMAP_8_16_ADDR       0xba2a
#define DISPLAY_DRAW_BITMAP_16_16_ADDR      0x99a5
#define DISPLAY_DRAW_BITMAP_BUF_ADDR        0xAA
#define DISPLAY_DRAW_BITMAP_COLOR_ADDR      0x5F
#define DISPLAY_DRAW_BITMAP_COLOR_BG_ADDR   0x60

#define ST7735_SEND_COMMAND_ADDR            0xeecc
#define ST7735_DRAW_PIXEL_ADDR              0xe00a
#define ST7735_DRAW_PIXEL_COLOR_IADDR       0x6a

#define UI_DRAW_SMALL_TEXT_ADDR             0xcd14
#define UI_DRAW_SMALL_TEXT_Y_IADDR          0x43
#define UI_DRAW_SMALL_TEXT_COLOR_IADDR      0x44
#define UI_DRAW_MEDIUM_TEXT_ADDR            0xaecd
#define UI_DRAW_MEDIUM_TEXT_Y_IADDR         0x53
#define UI_DRAW_MEDIUM_TEXT_COLOR_IADDR     0x54

#define UI_SHOW_MAIN_SCREEN_ADDR            0xee8c

#define BEEP_PLAY_ADDR                      0xb73b
																	          
#define EEPROM_READ_ADDR                    0xd2a8
#define EEPROM_READ_BUFPTR_IADDR            0x4d
#define EEPROM_WRITE_ADDR                   0xd8ed
#define EEPROM_WRITE_BUFPTR_IADDR           0x3c

#define SETTINGS_SAVE_ADDR                  0xd5f1
#define SETTINGS_KILL_STUN_ADDR             0x14a

#define INPUT_READ_KEYS_ADDR                0x6e28
#define INPUT_START_LONG_PRESS_ADDR         0x2ba6
#define INPUT_LONG_PRESS_TIME_ADDR          0x0463
#define INPUT_PRESSED_KEY_ADDR              0x0479

#define RF_READ_VALUE_ADDR                  0x02f5
#define RF_READ_ADDR                        0xc875
#define RF_WRITE_ADDR                       0xe6a3
#define RF_SET_AF_BW_AGC_ADDR               0xd3ab

#endif

//
// Common
//
#define FNKEYS_XDATA_ADDR                   0x0009
#define FNKEYS_FLASH_ADDR                   0xc90

//
// uMod Specific
//
#define UMOD_XDATA_BASE_ADDR       0x0fe0
#define UMOD_XDATA_SETTINGS_ADDR   UMOD_XDATA_BASE_ADDR
#define UMOD_XDATA_VARIABLES_ADDR	 (UMOD_XDATA_BASE_ADDR+sizeof(settings_t))
#define UMOD_FLASH_SETTINGS_ADDR   0x1fa0 /* old address - 0x1ffb */
#define UMOD_BITS_BASE_ADDR        0x2f

#define UMOD_XDATA_VAR_ADDR(n)     (UMOD_XDATA_VARIABLES_ADDR+(n))

#endif