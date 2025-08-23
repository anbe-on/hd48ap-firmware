#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x4B53  // "KS" for Kasep
#define PRODUCT_ID      0x4841  // "HA" for HD48AP
#define DEVICE_VER      0x0001
#define MANUFACTURER    Kasep
#define PRODUCT         HD48AP

/* key matrix size - Using 8x6 to handle your weird matrix */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* Since your matrix is completely custom, we need custom matrix */
#define CUSTOM_MATRIX

/* Rotary Encoder */
#define ENCODERS_PAD_A { D4 }
#define ENCODERS_PAD_B { D5 }
#define ENCODER_RESOLUTION 4

/* OLED Display */
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 64
#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 128

/* I2C for OLED (SDA=D1/pin2, SCL=D0/pin3 based on your pinout) */
#define I2C1_SCL_PIN        D0  // Pin 3
#define I2C1_SDA_PIN        D1  // Pin 2
#define I2C_DRIVER I2CD1

/* Mouse keys */
#define MOUSEKEY_ENABLE
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_INTERVAL 50
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

/* Vial-specific config */
#define VIAL_KEYBOARD_UID {0x11, 0x08, 0x60, 0x90, 0x23, 0x14, 0x10, 0x23}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 11 }

/* WPM calculation for animations */
#define WPM_ENABLE
#define WPM_LAUNCH_CONTROL
#define WPM_ALLOW_COUNT_REGRESSION

/* Animation settings */
#define OLED_UPDATE_INTERVAL 50
#define BONGOCAT_WPM_THRESHOLD 20

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
