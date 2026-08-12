#ifndef __MENU_H__
#define __MENU_H__

#define MENU_POS_X                2
#define MENU_POS_Y                76
#define MENU_WIDTH                (DISPLAY_X - MENU_POS_X - MENU_BORDER_WIDTH)
#define MENU_HEIGHT               50

#define MENU_BORDER_WIDTH         1
#define MENU_FONT_W               6
#define MENU_FONT_H               8
#define MENU_TITLE_X							(MENU_POS_X + 4)
#define MENU_TITLE_Y							(MENU_POS_Y + 4)
#define MENU_TITLE_HEIGHT         16
#define MENU_TITLE_SEP_X          88

#define MENU_ITEM_NUM_X           (MENU_POS_X + 90)
#define MENU_ITEM_NUM_Y           (MENU_POS_Y + 4)

#define MENU_ITEM_NAME_X          (MENU_POS_X + 4)
#define MENU_ITEM_NAME_Y          (MENU_POS_Y + 22)

#define MENU_ITEM_VALUE_X         (DISPLAY_X - (MENU_POS_X + 5))
#define MENU_ITEM_VALUE_Y         (MENU_POS_Y + 36)

#define MENU_ITEM_WIDTH           (MENU_WIDTH - 9)
#define MENU_ITEM_HEIGHT          22

typedef enum {
	MENU_OPTION_MODE = 0,
	MENU_OPTION_DEVIATION,
	MENU_OPTION_FILTER,
	MENU_OPTION_THEME,
	MENU_OPTION_FREQ_COLOR,
	MENU_OPTION_BATTERY_STYLE,
	MENU_OPTION_CHANNEL_SWITCH,
	MENU_OPTION_SMETER_SPEED,
	MENU_OPTION_SHOW_NOISE_BAR,
	MENU_OPTION_LONG_KEY_FN,
	MENU_OPTION_SHORT_KEY_FN,
	MENU_OPTION_RESET_SETTINGS,
	MENU_OPTION_MAX
} menu_option_t;

extern void MENU_Init(void);
extern void MENU_Open(void);
extern void MENU_Close(void);
extern void MENU_ToggleOption(void);
extern void MENU_ChangeOption(void);
extern void MENU_HandleKeys(void);

extern char code* code str_option_mode_values[];

#endif
