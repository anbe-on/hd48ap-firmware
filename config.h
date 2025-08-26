#pragma once

#define NO_MUSIC_MODE

// Matrix size - Defines grid; used in matrix.c for scanning loops and hd48ap.h for layout macro
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

// Charlieplex pins - Array of your 14 pins (AVR names from Pro Micro pinout); used in matrix.c for scanning
#define NUM_PINS 14

// Diode direction - COL2ROW means diodes point column to row; used in matrix.c for reading logic (test with multimeter if keys reverse)
#define DIODE_DIRECTION COL2ROW  // Adjust to ROW2COL if tests show swapped

// OLED pins - Standard I2C; used by QMK OLED driver (relates to oled_task_user() in keymap.c)
#define I2C1_SDA_PIN D1
#define I2C1_SCL_PIN D0

// Encoder pins - Your CLK/DT; used in encoder_update_user() in keymap.c
//#define ENCODERS_PAD_A { D4 }  // CLK
//#define ENCODERS_PAD_B { D5 }  // DT
//#define ENCODER_RESOLUTION 4  // Steps per click; adjust for sensitivity

// Mousekey config - Defaults; enables movement/click/scroll (use in keymap with MOUSEKEY_ON/OFF or assign to keys)
#define MOUSEKEY_INTERVAL 20     // Update interval (ms)
#define MOUSEKEY_DELAY 0         // Delay before movement
#define MOUSEKEY_TIME_TO_MAX 60  // Time to reach max speed
#define MOUSEKEY_MAX_SPEED 7     // Max cursor speed
#define MOUSEKEY_WHEEL_DELAY 0   // Wheel scroll delay

// OLED menu - Global for modes; used in keymap.c for encoder switching and oled_task_user()
#define MENU_MODES 5  // 0: images, 1: Layer 0, 2: Layer 1, 3: Layer 2, 4: Layer 3

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRIN
