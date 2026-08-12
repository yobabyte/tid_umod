#pragma userclass (code = FNTCAVE)

#include "umod.h"
#include "menu.h"
#include "firmware.h"

//
// Helpers for ASM
//

const char* uMod_GetModeOverrideString(void) {
	return str_option_mode_values[settings.mode];
}

//
// Modulation override
//

void uMod_ModulationOverrideHook(void) {
	switch (settings.mode) {
		case OPTION_MODE_AM:
			RF_SetAfBwAgc(true);
			break;
		case OPTION_MODE_FM:
			RF_SetAfBwAgc(false);
			break;
		case OPTION_MODE_USB:
			// Set AF
			RF_WriteU16(0x47, 0x6540); // REG_47 | (5 << 8) // BASEBAND2
		
			// Set Bandwidth (3.4 MHz)
			RF_WriteU16(0x43, 0x28);
		
			// Set AGC (0 dB)
		  RF_WriteU16(0x13, 0x3ff);
			break;
	}
	
	// IF selection (zero or 8.46 kHz)
	if (settings.mode == OPTION_MODE_USB) {
		RF_WriteU16(0x3D, 0);	
	} else {
		RF_WriteU16(0x3D, 0x2AAB);	
	}
}
