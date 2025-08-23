#pragma once

// Vial specific configuration
#define VIAL_KEYBOARD_UID {0x11, 0x08, 0x60, 0x90, 0x23, 0x14, 0x10, 0x23}

// Security
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

// Enable Vial features
#define VIAL_ENABLE
#define VIAL_INSECURE

// OLED configuration
#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 60000

// Animation settings
#define BONGOCAT_WPM_THRESHOLD 20
#define OLED_UPDATE_INTERVAL 50

// Screen modes
typedef enum {
    SCREEN_BONGOCAT,
    SCREEN_SYSTEM_INFO,
    SCREEN_MAX
} screen_mode_t;
