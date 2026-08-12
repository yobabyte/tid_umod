#ifndef __COLORS_H__
#define __COLORS_H__

//#define RGB565LE(r, g, b) ((r & 0x1F) | (((g) & 0x3F) << 5) | (((b) & 0x1F) << 11))
//#define RGB565(r, g, b) ((RGB565LE(r, g, b) >> 8) | ((RGB565LE(r, g, b) & 0xFF) << 8))

#define RGB565(r,g,b) ((((r) & 0x1f) << 8) | (((g) >> 3) | (((g) & 0x7) << 13)) | (((b) & 0x1F) << 3))

typedef enum {
	COLOR_BLACK            = RGB565( 0,  0,  0),
	COLOR_WHITE            = RGB565(31, 63, 31),
	COLOR_WHITE_2          = RGB565(31, 62, 31),
	COLOR_RED              = RGB565(31,  0,  0),
	COLOR_GREEN            = RGB565( 0, 55,  0),
	COLOR_GREEN_W          = RGB565( 0, 45,  0),// 45
	COLOR_BLUE             = RGB565( 0,  0, 31),
	COLOR_YELLOW           = RGB565(25, 52,  0),
	COLOR_GRAY             = RGB565(28, 56, 28),
	COLOR_GRAY_W           = RGB565( 6, 12,  6), //RGB565(10, 21, 10),
	COLOR_GRAY_2           = RGB565(14, 28, 14), //RGB565( 7, 14,  7),
	
	COLOR_RED_RF           = RGB565(26, 10,  3),
	COLOR_BLUE_RF          = RGB565( 0, 14, 20),
	
	COLOR_SMETER_BG        = RGB565(12, 24, 12), // 7,14,7
	COLOR_SMETER_BG_W      = RGB565( 3,  7,  3), // 4/8/4
	
	COLOR_SMETER_SCALE     = COLOR_WHITE,
	COLOR_SMETER_LEVEL     = COLOR_WHITE, // COLOR_GREEN_W

	COLOR_SMETER_SCALE_P   = RGB565(21, 20, 31), //RGB565(27, 7, 28), //RGB565(13, 30, 23), // 0x45e9,
	COLOR_SMETER_LEVEL_P   = COLOR_SMETER_SCALE_P, //COLOR_SMETER_SCALE_P, //RGB565(31, 13, 6), // 0x45e9,

	COLOR_SMETER_NOISE     = RGB565(31, 47, 29),

	COLOR_RSSI_TEXT        = COLOR_GREEN_W,
	COLOR_NOISE_TEXT       = RGB565(16, 33, 15),
	
	COLOR_MENU_VALUE       = RGB565(0, 30, 29), // RGB565(0, 33, 31),
	
	COLOR_POWERED_BY       = RGB565(4, 41, 23) // RGB565(0, 45, 31)
	
};

// cool blue
// RGB565(4, 41, 23)

#endif