#pragma userclass (code = BMPCAVE)

#include "menu.h"
#include "umod.h"
#include "colors.h"
#include "firmware.h"

// 0003BDH
IDATA_VAR1(0x4A);

extern void uMod_ResetSettings(void);

const char code str_off[] = "Off";
const char code str_default[] = "Default";

// String constants (not stored in BMPCAVE)
const char code* code str_menu_items[] = {
	"RF Modulation",
	"Deviation",
	"VHF/UHF Filter",
	"Color Theme",
	"Frequency Color",
	"Battery Style",
	"Channel Switch",
	"S-meter Update",
	"Show Noise Meter",
	"Long Key Fn",
	"Short Key Fn",
	"Reset Mod Settings"
};

const char code str_title[] = "UMOD MENU";

const char code* code str_option_toggle_values[] = {
	str_off,
	"On"
};

const char code* code str_option_theme_values[] = {
	"Dark",
	"Light"
};

const char code* code str_option_filter_values[] = {
	str_default, // 300 MHz
	"280 MHz",
	"270 MHz",
	"265 MHz"
};

const char code* code str_option_mode_values[] = {
	"Auto",
	"AM",
	"FM",
	"DSB",
};

const char code* code str_option_fnkey_values[] = {
	"None",
	"FM Radio",
	"Lamp",
	"Monitor",
	"Tx Tone",
	"Alarm",
	"Weather"
};

const char code* code str_option_battery_values[] = {
	"Icon",
	"Voltage",
	"Percent"
};

const char code* code str_option_channel_switch_values[] = {
	str_default,
	"Tx Only",
	"Rx Only",
	"Both"
};

const char code* code str_option_freq_color_values[] = {
	str_default,
	"Blue",
	"Blue 2",
	"Green",
	"Green 2",
	"Red",
	"Yellow",
	"Magenta"
};

const char code* code str_option_smeter_speed_values[] = {
	"Fast",
	"Slow",
	"Disabled"
};

const char code str_apply[] = "Apply";

extern settings_t xdata settings;

// Global variables (xdata)
int8_t xdata menu_option_index _at_ UMOD_XDATA_VAR_ADDR(0);

// Global variables (bits)
uint8_t bdata _BITS_UMOD _at_ UMOD_BITS_BASE_ADDR;
sbit menu_active = _BITS_UMOD ^ 7;

// Local variables (idata)
const char* idata menu_option_value _at_ 0x79; // up to 12+ bytes

void MENU_Draw(void) {
	// Get option number text
	UTIL_Itoa3(menu_option_index + 1);
	str_buf[4] = '/';
	str_buf[5] = '1';
	str_buf[6] = '1';
	str_buf[7] = 0;

	// Draw option number
	UI_DrawSmallText(
		str_buf + 2,
		MENU_ITEM_NUM_X,
		MENU_ITEM_NUM_Y,
		COLOR_WHITE_2);
	
	// Get option value text
	switch (menu_option_index) {
		case MENU_OPTION_MODE:
			menu_option_value = str_option_mode_values[settings.mode];
			break;
		case MENU_OPTION_DEVIATION:
			UTIL_Itoa3(settings.deviation);
			str_buf[0] = '1';
			str_buf[1] += 2;
			menu_option_value = str_buf;
			break;
		case MENU_OPTION_FILTER:
			menu_option_value = str_option_filter_values[settings.filter];
			break;
		case MENU_OPTION_THEME:
			menu_option_value = str_option_theme_values[settings.color_theme];
			break;
		case MENU_OPTION_FREQ_COLOR:
			menu_option_value = str_option_freq_color_values[settings.freq_color];
			break;
		case MENU_OPTION_BATTERY_STYLE:
			menu_option_value = str_option_battery_values[settings.battery_style];
			break;
		case MENU_OPTION_CHANNEL_SWITCH:
			menu_option_value = str_option_channel_switch_values[settings.channel_switch];
			break;
		case MENU_OPTION_SMETER_SPEED:
			menu_option_value = str_option_smeter_speed_values[settings.smeter_speed];
			break;
		case MENU_OPTION_SHOW_NOISE_BAR:
			menu_option_value = str_option_toggle_values[settings.show_noise_bar];
			break;
		case MENU_OPTION_LONG_KEY_FN:
			menu_option_value = str_option_fnkey_values[fn_keys[FN_LONG_KEY]];
			break;
		case MENU_OPTION_SHORT_KEY_FN:
			menu_option_value = str_option_fnkey_values[fn_keys[FN_SHORT_KEY]];
			break;
		case MENU_OPTION_RESET_SETTINGS:
		default:
			menu_option_value = str_apply;
		  break;
	}
	
	// Clear
	uMod_FillRect(
		MENU_ITEM_NAME_X,
		MENU_ITEM_NAME_Y,
		MENU_ITEM_WIDTH,
		MENU_ITEM_HEIGHT,
		COLOR_BLACK);
	
	// Draw option name
	UI_DrawSmallText(
		str_menu_items[menu_option_index],
		MENU_ITEM_NAME_X,
		MENU_ITEM_NAME_Y,
		COLOR_WHITE_2);
	
	// Draw option value
	UI_DrawSmallText(
		menu_option_value,
		MENU_ITEM_NAME_X, //MENU_ITEM_VALUE_X - (strlen(menu_option_value) * MENU_FONT_W),
		MENU_ITEM_VALUE_Y,
		uMod_AdjustColor(COLOR_MENU_VALUE)); // COLOR_GREEN_W 0xe0f8
}

void MENU_ToggleOption(void) {
	switch (menu_option_index) {
		case MENU_OPTION_MODE:
			settings.mode++;
			if (settings.mode > OPTION_MODE_MAX)
				settings.mode = 0;
			break;
		case MENU_OPTION_DEVIATION:
			settings.deviation++;
		  if (settings.deviation > OPTION_DEVIATION_MAX)
				settings.deviation = 0;
			break;
		case MENU_OPTION_FILTER:
			settings.filter++;
			if (settings.filter > OPTION_FILTER_MAX)
				settings.filter = OPTION_FILTER_DEFAULT;
			break;
		case MENU_OPTION_THEME:
			settings.color_theme = !settings.color_theme;
			uMod_ToggleTheme();
			break;
		case MENU_OPTION_FREQ_COLOR:
			settings.freq_color++;
			if (settings.freq_color > OPTION_FREQ_COLOR_MAX)
				settings.freq_color = 0;
			break;
		case MENU_OPTION_BATTERY_STYLE:
			settings.battery_style++;
			if (settings.battery_style > OPTION_BATTERY_STYLE_MAX)
				settings.battery_style = 0;
			break;
		case MENU_OPTION_CHANNEL_SWITCH:
			settings.channel_switch++;
		  if (settings.channel_switch > OPTION_CHANNEL_SWITCH_MAX)
				settings.channel_switch = 0;
			break;
		case MENU_OPTION_SMETER_SPEED:
			settings.smeter_speed++;
			if (settings.smeter_speed > OPTION_SMETER_SPEED_MAX)
				settings.smeter_speed = 0;
			break;
		case MENU_OPTION_SHOW_NOISE_BAR:
			settings.show_noise_bar = !settings.show_noise_bar;
			break;
		case MENU_OPTION_LONG_KEY_FN:
			fn_keys[FN_LONG_KEY]++;
			if (fn_keys[FN_LONG_KEY] > KEY_FUNC_MAX)
				fn_keys[FN_LONG_KEY] = KEY_FUNC_NONE;
			SETTINGS_SaveFuncKey();
			break;
		case MENU_OPTION_SHORT_KEY_FN:
			fn_keys[FN_SHORT_KEY]++;
			if (fn_keys[FN_SHORT_KEY] == KEY_FUNC_MONITOR) {
				fn_keys[FN_SHORT_KEY]++;
			}
			if (fn_keys[FN_SHORT_KEY] > KEY_FUNC_MAX) {
				fn_keys[FN_SHORT_KEY] = KEY_FUNC_NONE;
			}
			SETTINGS_SaveFuncKey();
			break;
		case MENU_OPTION_RESET_SETTINGS:
			uMod_ResetSettings();
			uMod_ToggleTheme();
			MENU_Close();
			return;
	}

	MENU_Draw();

	Beep_Play(BEEP_TONE_1);
}

void MENU_ChangeOption(void) {
	if (INPUT_UpDownKeyState == INPUT_KEY_DOWN) {
		menu_option_index--;
		
		if (menu_option_index < 0)
			menu_option_index = MENU_OPTION_MAX - 1;		
	} else {
		menu_option_index++;
		
		if (menu_option_index > (MENU_OPTION_MAX - 1))
			menu_option_index = 0;
	}

	MENU_Draw();

	Beep_Play(BEEP_TONE_3);
}

void MENU_Init(void) {
	menu_option_index = 0;
}

void MENU_Open(void) {
	menu_active = true;

	// Clear display
	Display_Fill(0, 64, DISPLAY_Y, COLOR_BLACK);

	/*
	uMod_FillRect(MENU_POS_X, MENU_POS_Y, MENU_WIDTH - 1, MENU_BORDER_WIDTH, COLOR_WHITE);
	uMod_FillRect(MENU_POS_X, MENU_POS_Y + MENU_HEIGHT, MENU_WIDTH - 1, MENU_BORDER_WIDTH, COLOR_WHITE);
	uMod_FillRect(MENU_POS_X, MENU_POS_Y + MENU_TITLE_HEIGHT, MENU_WIDTH - 1, MENU_BORDER_WIDTH, COLOR_WHITE); // title horizontal sep 
	uMod_FillRect(MENU_TITLE_SEP_X, MENU_POS_Y, MENU_BORDER_WIDTH, MENU_TITLE_HEIGHT, COLOR_WHITE); // title vertical sep
	uMod_FillRect(MENU_POS_X, MENU_POS_Y, MENU_BORDER_WIDTH, MENU_HEIGHT, COLOR_WHITE);
	uMod_FillRect(MENU_WIDTH, MENU_POS_Y, MENU_BORDER_WIDTH, MENU_HEIGHT, COLOR_WHITE);
	*/
	
	// Draw form borders
	uMod_FillRect(MENU_POS_X, MENU_POS_Y, MENU_WIDTH - 1, MENU_HEIGHT, COLOR_WHITE);
	uMod_FillRect(
		MENU_POS_X + MENU_BORDER_WIDTH,
		MENU_POS_Y + MENU_BORDER_WIDTH,
		MENU_WIDTH - 1 - (MENU_BORDER_WIDTH * 2),
		MENU_HEIGHT - (MENU_BORDER_WIDTH * 2),
		COLOR_BLACK);

  // Title horizontal separator
	uMod_FillRect(MENU_POS_X, MENU_POS_Y + MENU_TITLE_HEIGHT, MENU_WIDTH - 1, MENU_BORDER_WIDTH, COLOR_WHITE);
	// Title vertical separator
	uMod_FillRect(MENU_TITLE_SEP_X, MENU_POS_Y, MENU_BORDER_WIDTH, MENU_TITLE_HEIGHT, COLOR_WHITE);
	
  // Draw title
	UI_DrawSmallText(str_title, MENU_TITLE_X, MENU_TITLE_Y, COLOR_WHITE);
	
	// Draw menu text
	MENU_Draw();
}

void MENU_Close(void) {
	menu_active = false;

	// Save mod settings to EEPROM
	uMod_SaveSettings();
	
	Beep_Play(BEEP_TONE_1); // BEEP_TONE_2

	// Back to the main screen
	UI_ShowMainScreen();
}

void MENU_HandleKeys(void) {
	if (INPUT_IsKeyHandled)
		return;

	/*
	if (INPUT_KeyPressed == KEY_MENU) {
		INPUT_IsKeyHandled = true;
		MENU_ToggleOption();
	} else if (INPUT_KeyPressed == KEY_BACK) {
		MENU_Close();
	} else if (INPUT_KeyPressed == KEY_UP) {
		INPUT_IsKeyHandled = true;
		INPUT_UpDownKeyState = INPUT_KEY_UP;
		MENU_ChangeOption();
	} else if (INPUT_KeyPressed == KEY_DOWN) {
		INPUT_IsKeyHandled = true;
		INPUT_UpDownKeyState = INPUT_KEY_DOWN;
		MENU_ChangeOption();
	}
  */
	
	switch (INPUT_KeyPressed) {
		case KEY_MENU:
			INPUT_IsKeyHandled = true;
			MENU_ToggleOption();
			break;
		case KEY_BACK:
			MENU_Close();
			break;
		case KEY_UP:
			INPUT_IsKeyHandled = true;
			INPUT_UpDownKeyState = INPUT_KEY_UP;
			MENU_ChangeOption();
			break;
		case KEY_DOWN:
			INPUT_IsKeyHandled = true;
			INPUT_UpDownKeyState = INPUT_KEY_DOWN;
			MENU_ChangeOption();
			break;
	}
	
	// WDT_Clear();
}