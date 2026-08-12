#ifndef __UMOD_H__
#define __UMOD_H__

#define DISPLAY_X 128
#define DISPLAY_Y 128

typedef enum {
	OPTION_TOGGLE_OFF = 0,
	OPTION_TOGGLE_ON,
	OPTION_TOGGLE_MAX = OPTION_TOGGLE_ON
} option_toggle_t;

typedef enum {
	OPTION_FILTER_DEFAULT = 0, // 300 MHz
	OPTION_FILTER_280,
	OPTION_FILTER_270,
	OPTION_FILTER_265,
	OPTION_FILTER_MAX = OPTION_FILTER_265
} option_filter_t;

typedef enum {
	OPTION_THEME_DARK = 0,
	OPTION_THEME_LIGHT,
	OPTION_THEME_MAX = OPTION_THEME_LIGHT
} option_theme_t;

typedef enum {
	OPTION_MODE_OFF = 0,
	OPTION_MODE_AM,
	OPTION_MODE_FM,
	OPTION_MODE_USB,
	OPTION_MODE_MAX = OPTION_MODE_USB
} option_mode_t;

typedef enum {
	OPTION_BATTERY_STYLE_ICON = 0,
	OPTION_BATTERY_STYLE_VOLTAGE,
	OPTION_BATTERY_STYLE_PERCENT,
	OPTION_BATTERY_STYLE_MAX = OPTION_BATTERY_STYLE_PERCENT
} option_battery_style_t;

typedef enum {
	OPTION_CHANNEL_SWITCH_DEFAULT = 0,
	OPTION_CHANNEL_SWITCH_TX,
	OPTION_CHANNEL_SWITCH_RX,
	OPTION_CHANNEL_SWITCH_BOTH,
	OPTION_CHANNEL_SWITCH_MAX = OPTION_CHANNEL_SWITCH_BOTH
} option_channel_switch_t;

typedef enum {
	OPTION_FREQ_COLOR_DEFAULT = 0,
	OPTION_FREQ_COLOR_1,
	OPTION_FREQ_COLOR_2,
	OPTION_FREQ_COLOR_3,
	OPTION_FREQ_COLOR_4,
	OPTION_FREQ_COLOR_5,
	OPTION_FREQ_COLOR_6,
	OPTION_FREQ_COLOR_7,
	OPTION_FREQ_COLOR_MAX = OPTION_FREQ_COLOR_7
} option_freq_color_t;

typedef enum {
	OPTION_SMETER_SPEED_SLOW = 0,
	OPTION_SMETER_SPEED_FAST,
	OPTION_SMETER_SPEED_DISABLED,
	OPTION_SMETER_SPEED_MAX = OPTION_SMETER_SPEED_DISABLED
} option_smeter_speed_t;

/*
typedef struct {
	option_filter_t filter;
	option_theme_t theme;
	option_toggle_t show_noise_bar:1;
	option_toggle_t show_rssi_noise:1;
	option_battery_t battery_style:2;
	option_channel_switch_t channel_switch:2;
	option_mode_t mode;
	option_freq_color_t freq_color;
} settings_t;
*/

typedef unsigned char option_deviation_t;
#define OPTION_DEVIATION_MAX 250

typedef struct {
	option_mode_t mode;
	option_filter_t filter;
	option_deviation_t deviation;
	option_theme_t color_theme;
	option_freq_color_t freq_color;
	option_battery_style_t battery_style;
	option_channel_switch_t channel_switch;
	option_smeter_speed_t smeter_speed;
	option_toggle_t show_noise_bar;
	//option_toggle_t max_power;
} settings_t;

extern settings_t xdata settings;

void UTIL_Itoa3(int value);
void uMod_ToggleTheme(void);
void uMod_SaveSettings(void);
void uMod_ResetSettings(void);

/* Not initialized flash (first time run), set defaults */
#define uMod_LoadSettings()\
	EEPROM_Read(UMOD_FLASH_SETTINGS_ADDR, sizeof(settings_t), &settings); \
	if (settings.mode > OPTION_MODE_MAX) settings.mode = 0; \
	if (settings.filter > OPTION_FILTER_MAX) settings.filter = 0; \
	if (settings.deviation > OPTION_DEVIATION_MAX) settings.deviation = 0; \
	if (settings.color_theme > OPTION_THEME_MAX) settings.color_theme = 0; \
	if (settings.freq_color > OPTION_FREQ_COLOR_MAX) settings.freq_color = 0; \
  if (settings.battery_style > OPTION_BATTERY_STYLE_MAX) settings.battery_style = 0; \
	if (settings.channel_switch > OPTION_CHANNEL_SWITCH_MAX) settings.channel_switch = 0; \
	if (settings.smeter_speed > OPTION_SMETER_SPEED_MAX) settings.smeter_speed = 0; \
	if (settings.show_noise_bar > OPTION_TOGGLE_MAX) settings.show_noise_bar = 0

/*
#define uMod_SaveSettings()\
	EEPROM_Write(UMOD_FLASH_SETTINGS_ADDR, sizeof(settings_t), &settings);
*/

#define uMod_ClearSettings()\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+0) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+1) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+2) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+3) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+4) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+5) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+6) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+7) = 0;\
	*(uint8_t xdata*)(UMOD_XDATA_SETTINGS_ADDR+8) = 0

/*
#define uMod_ToggleTheme()\
	ST7735_SendCommand(settings.theme != OPTION_THEME_DARK ? ST77XX_INVON : ST77XX_INVOFF)
*/

#ifdef __FILLRECT_USE_IMPL
// NOTE: Allocates 8 bytes in IDATA (check linker options!)
// _DATA_GROUP_ (D:0x6b)
void uMod_FillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
	uint8_t px, py;
	for (py = 0; py < h; ++py) {
		for (px = 0; px < w; ++px) {
			ST7735_DrawPixel(px + x, py + y, color);
		}
	}
}
#else
#define uMod_FillRect Display_FillRect
#endif

extern unsigned int uMod_AdjustColor(unsigned int);
extern unsigned int uMod_ThemeColor(unsigned int, unsigned int);

// Helpers for variables
#define IDATA_VAR1(addr) \
	union { \
		int8_t i8; \
		uint8_t u8; \
	} idata ivar_##addr _at_ addr
	
#define IDATA_VAR2(addr) \
	union { \
		int8_t i8; \
		uint8_t u8; \
		int16_t i16; \
		uint16_t u16; \
	} idata ivar_##addr _at_ addr
	
#define IDATA_VAR4(addr) \
	union { \
		int8_t i8; \
		uint8_t u8; \
		int16_t i16; \
		uint16_t u16; \
		int16_t i32; \
		uint16_t u32; \
	} idata ivar_##addr _at_ addr

#endif