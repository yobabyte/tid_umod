#include "umod.h"
#include "menu.h"
#include "smeter.h"
#include "colors.h"
#include "firmware.h"

// Linear interpolation
#define INTERP(value, old_min, old_max, new_min, new_max) \
  (((((value) - (old_min)) * ((new_max) - (new_min))) / ((old_max) - (old_min))) + (new_min))

// Global variables (xdata)
settings_t xdata settings _at_ UMOD_XDATA_SETTINGS_ADDR;
int16_t xdata rf_rssi _at_ UMOD_XDATA_VAR_ADDR(1);
int16_t xdata rf_noise _at_ UMOD_XDATA_VAR_ADDR(3);

// Local variables (idata)
long idata battery_vdd _at_ 0x71;
uint8_t idata battery_pct _at_ 0x75;

// 0x40-0x41
IDATA_VAR1(0x38);
IDATA_VAR2(0x3A);
IDATA_VAR1(0x3E);
IDATA_VAR1(0x65);
IDATA_VAR1(0x66);
IDATA_VAR1(0x67);
IDATA_VAR2(0x6b);

const char code str_boot_title[] = "TIDRADIO H3";
const char code str_boot_powered_by[] = "Powered by uMod";
const char code str_boot_build_version[] = "R3-240812";
//const char code str_boot_build_version[] = "DEV-DEBUG";

//
// Utils
//

void UTIL_Itoa3(int value) {
	str_buf[1] = '0' + (value / 100);
	str_buf[2] = '0' + ((value % 100) / 10);
	str_buf[3] = '0' + ((value % 100) % 10);
	str_buf[4] = 0;
}

void UTIL_Ljust3() {
	if (str_buf[1] == '0') {
		if (str_buf[2] == '0') {
			str_buf[2] = str_buf[3];
			str_buf[3] = ' ';
		}
		
		str_buf[1] = str_buf[2];
		str_buf[2] = str_buf[3];
		str_buf[3] = ' ';
	}
}

#define UTIL_PrefixedItoa3(prefix, value)\
	str_buf[0] = (prefix);\
	UTIL_Itoa3((value));\
	UTIL_Ljust3()

//
// uMod
//

uint16_t uMod_AdjustColor(uint16_t color) {
	if (color == COLOR_WHITE) {
		return color;
	}
	return settings.color_theme ? ~color : color;
}

uint16_t uMod_ThemeColor(uint16_t color_dark, uint16_t color_light) {
	return settings.color_theme ? color_light : color_dark;
}

void uMod_Startup(void) {
	MENU_Init();

	uMod_LoadSettings();
	uMod_ToggleTheme();
}

void uMod_SaveSettings(void) {
	EEPROM_Write(UMOD_FLASH_SETTINGS_ADDR, sizeof(settings_t), &settings);
}

void uMod_ResetSettings(void) {
	//uMod_ClearSettings();
	uMod_SaveSettings();
}

void uMod_ToggleTheme(void) {
	ST7735_SendCommand(settings.color_theme != OPTION_THEME_DARK ? ST77XX_INVON : ST77XX_INVOFF);
}

void uMod_DrawLogoHook(void) {
	uMod_Startup();

	if ((*(uint8_t xdata*)(0x146)) & 0x80) {
		UI_DrawSmallText(str_boot_title, 29, 54, COLOR_WHITE);
		UI_DrawSmallText(str_boot_powered_by, 17, 66, uMod_AdjustColor(COLOR_POWERED_BY));
		UI_DrawSmallText(str_boot_build_version, 36, 116, COLOR_GRAY_2);
		return;
	}
	
	// Replaced to LJMP by patched
	((void (code*)(void))(0x9625))();
}

void uMod_HandleMenuKeys(void) {
	MENU_HandleKeys();
}

void uMod_CheckHotkey(void) {	
	INPUT_StartLongPress();

	do {
		if (INPUT_KeyPressed == KEY_NONE)
			break;
		WDT_Clear();
		INPUT_ReadKeys();
	} while (INPUT_LongPressTime < 2);

	if (INPUT_LongPressTime > 1) {
		Beep_Play(BEEP_TONE_3);
		MENU_Open();
	} else {
		INPUT_IsKeyHandled = true;
		INPUT_KeyPressed = KEY_7;
		Keypad_HandleInput();
	}
}

void uMod_HotkeyHook(void) {
	if ((INPUT_KeyPressed == KEY_7) && !INPUT_IsKeyHandled) {
		INPUT_IsKeyHandled = true;
		uMod_CheckHotkey();
	}
}

//
// Custom battery indicator
//

#define BATTERY_MIN_V 590 // 600-610?
#define BATTERY_MAX_V 840

void uMod_DrawBattery(void) {
	/*
	battery_vdd = (BATTERY_AnalogValue * (long)2055) / 100000;
	str_buf[0] = '0' + (battery_vdd / 10);
	str_buf[1] = '.';
	str_buf[2] = '0' + (battery_vdd % 10);	
	str_buf[3] = 'V';
	str_buf[4] = 0;
	*/

	battery_vdd = (BATTERY_AnalogValue * (long)2055) / 10000;

	if (settings.battery_style == OPTION_BATTERY_STYLE_VOLTAGE) {
		str_buf[1] = '0' + (battery_vdd / 100);
		str_buf[2] = '.';
		str_buf[3] = '0' + ((battery_vdd / 10) % 10); /* + ((battery_vdd % 10) / 5); // drifting too much? */
		str_buf[4] = 'V';
		str_buf[5] = 0;
	} else {
		if (battery_vdd < BATTERY_MIN_V)
			battery_vdd = BATTERY_MIN_V;
		//if (battery_vdd > BATTERY_MAX_V)
		//	battery_vdd = BATTERY_MAX_V;

		battery_pct = INTERP(battery_vdd, BATTERY_MIN_V, BATTERY_MAX_V, 0, 100);
		UTIL_Itoa3(battery_pct);
		if (str_buf[1] == '0') { // Right adjust
			str_buf[1] = ' ';
			if (str_buf[2] == '0')
				str_buf[2] = ' ';
		}
		str_buf[4] = '%';
	}
	
	UI_DrawSmallText(&str_buf[1], 102, 6, 0x79CE);
}

//
// Signal Meter / RSSI
//

void uMod_DrawPowerMeter(void) {
#ifndef UMOD_DISABLE_SMETER
#define i ivar_0x65.u8
#define signal_width ivar_0x66.u8
#define noise_width ivar_0x67.u8
#define color ivar_0x6b.u16

	if (smeter_full_draw) {	
		uMod_FillRect(
			SIGNAL_METER_X,
			SIGNAL_METER_Y,
			SIGNAL_METER_NORMAL_WIDTH - 1,
			1,
			COLOR_SMETER_SCALE);
		uMod_FillRect(
			SIGNAL_METER_X + SIGNAL_METER_NORMAL_WIDTH - 1,
			SIGNAL_METER_Y,
			SIGNAL_METER_PLUS_WIDTH,
			1,
			uMod_AdjustColor(COLOR_SMETER_SCALE_P));

		// Draw scale (S3-S9, S9+30)
		for (i = SIGNAL_METER_X + SIGNAL_METER_LEVEL_WIDTH - 2; i <= (SIGNAL_METER_WIDTH + SIGNAL_METER_X); i += SIGNAL_METER_LEVEL_WIDTH) {
			color = i > (SIGNAL_METER_X + SIGNAL_METER_NORMAL_WIDTH) ? uMod_AdjustColor(COLOR_SMETER_SCALE_P) : COLOR_SMETER_SCALE;
			uMod_FillRect(
				i,
				SIGNAL_METER_Y - SIGNAL_METER_HEIGHT,
				1,
				SIGNAL_METER_HEIGHT - 1,
				color
			);
		}
		
		smeter_full_draw = false;
	}

	noise_width = 0;
	signal_width = SIGNAL_METER_WIDTH;

	if (RADIO_IsTxOn) {
		if (RADIO_OutputPower != RADIO_POWER_HIGH) {
			signal_width = 40;
		}
	} else if (RADIO_IsRxOn) {
		if (rf_rssi < SIGNAL_METER_DBM_S3S9_MAX) {
			signal_width = SIGNAL_METER_NORMAL_WIDTH + (SIGNAL_METER_DBM_S3S9_MAX - rf_rssi);
		} else {
			// RSSI to pixels
			signal_width = INTERP(
				rf_rssi,
				SIGNAL_METER_DBM_S3S9_MIN,
				SIGNAL_METER_DBM_S3S9_MAX,
				1,
				SIGNAL_METER_NORMAL_WIDTH);
		}
		
		// Noise to pixels
		if (settings.show_noise_bar) {
			noise_width = INTERP(
				rf_noise,
				SIGNAL_METER_DBM_S3S9_MIN + 1,
				SIGNAL_METER_DBM_S3S9_MAX,
				0,
				SIGNAL_METER_NORMAL_WIDTH);
		}
	}
	
	for (i = 0; i < SIGNAL_METER_WIDTH; i += 2) {
		color = uMod_ThemeColor(COLOR_SMETER_BG, COLOR_SMETER_BG_W);

		if (RADIO_IsTxOn && (i < signal_width)) {
			color = uMod_AdjustColor(COLOR_RED);
		} else if (RADIO_IsRxOn) {
			if (i < noise_width) {
				color = uMod_AdjustColor(COLOR_SMETER_NOISE);
			} else if (i < signal_width) {
				color = i >= SIGNAL_METER_NORMAL_WIDTH ? uMod_AdjustColor(COLOR_SMETER_LEVEL_P) : COLOR_SMETER_LEVEL;
			}
		}

		uMod_FillRect(SIGNAL_METER_X + i, SIGNAL_METER_Y + 2, 1, SIGNAL_METER_HEIGHT - 1, color);
	}

#undef color
#undef noise_width
#undef signal_width
#undef i
#endif
}

void uMod_DrawSignalStrengthHook(void) {
#ifndef UMOD_DISABLE_SMETER
	if (!draw_rssi_arg_0 || !RADIO_IsRxOn) {
		rf_rssi = 0;
		rf_noise = 0;
		
		// Clear RSSI/Noise/dBm text
		Display_Fill(
			102,
			FMRADIO_IsActive ? 70 : 45,
			FMRADIO_IsActive ? 10 : 35,
			COLOR_BLACK);
		
		// Draw S-meter for TX
		if (!RADIO_IsNoaaMode) {
			smeter_full_draw = true;
			uMod_DrawPowerMeter();
		}
	} else {
		RF_Read(0x67);
		rf_rssi = RF_RegValue & 0x1FF; 
		RF_Read(0x65);
		rf_noise = RF_RegValue & 0x7F;
		
		/*
		if (!FMRADIO_IsActive && settings.show_rssi_noise) {
			// Draw RSSI value
			UTIL_PrefixedItoa3('S', rf_rssi);
			UI_DrawSmallText(str_buf, 102, 45, uMod_AdjustColor(COLOR_RSSI_TEXT));
			
			// Draw Ex-Noise value
			UTIL_PrefixedItoa3('N', rf_noise);
			UI_DrawSmallText(str_buf, 102, 56, uMod_AdjustColor(COLOR_NOISE_TEXT));
    }
		*/
		
		rf_rssi /= 2;

		// Apply correction for AM
		if (RADIO_IsAmMod || (settings.mode == OPTION_MODE_AM)) {
			rf_rssi -= SIGNAL_METER_AM_CORR;
			//rf_noise -= SIGNAL_METER_AM_CORR;
		}
		
		// Convert RSSI/Ex-Noise to dBm
		rf_rssi -= (160 + SIGNAL_METER_RSSI_CAL);
		rf_noise -= (160 + SIGNAL_METER_RSSI_CAL);
		if (rf_noise < 0)
			rf_noise = -rf_noise;

		// Draw dBm value
		str_buf[0] = rf_rssi < 0 ? '-' : '+';
		if (rf_rssi < 0) {
			rf_rssi = -rf_rssi;
		}
		UTIL_Itoa3(rf_rssi);
		UTIL_Ljust3();
		UI_DrawSmallText(str_buf, 102, SIGNAL_METER_Y - 4, COLOR_WHITE);

		// Limit RSSI for S-meter bar
		if (rf_rssi < SIGNAL_METER_DBM_S9_PLUS30) {
			rf_rssi = SIGNAL_METER_DBM_S9_PLUS30;
		} else if (rf_rssi > SIGNAL_METER_DBM_S3S9_MIN) {
			rf_rssi = SIGNAL_METER_DBM_S3S9_MIN;
		}
		
		// Limit Ex-Noise for S-meter bar
		if (rf_noise < SIGNAL_METER_DBM_S3S9_MAX) {
			rf_noise = SIGNAL_METER_DBM_S3S9_MAX;
		} else if (rf_noise > (SIGNAL_METER_DBM_S3S9_MIN+1)) {
			rf_noise = (SIGNAL_METER_DBM_S3S9_MIN+1);
		}
		
		// Draw S-meter for RX
		smeter_full_draw = false;
		uMod_DrawPowerMeter();
	}
#endif
}

//
// Misc
//

#pragma SAVE
#pragma OPTIMIZE(8)
void uMod_DrawStatusBarSeparatorHook(void) {
	//uMod_FillRect(0, 21, 128, 1, 0x79CE);
	Display_Fill(0, 21, 1, 0x79CE);
	
	// Bottom 1px line fill for white theme
	//uMod_FillRect(0, 127, 128, 1, COLOR_WHITE);
	
	// Original call
	((void (code*)(void))(0x7482))();
}
#pragma RESTORE
