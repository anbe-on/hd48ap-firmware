#pragma once

// Disable music mode completely to save flash
#define NO_MUSIC_MODE

// Matrix configuration - 6 columns x 8 rows as per PCB layout
// Uses standard QMK matrix scanning instead of custom charlieplexing
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

// OLED display configuration - Force 128x64 and correct rotation
#define I2C1_SDA_PIN D1  // Standard I2C SDA pin for Pro Micro
#define I2C1_SCL_PIN D0  // Standard I2C SCL pin for Pro Micro
#define OLED_DISPLAY_128X64  // Force 128x64 resolution (not 128x32)

// Performance optimizations for fast typing response
#define DEBOUNCE 5          // Standard debounce timing (ms) - good balance of speed/stability
#define USB_POLLING_INTERVAL_MS 1  // 1000Hz USB polling for minimal input latency
#define QUICK_TAP_TERM 0    // Disable tap-hold quick tap for faster layer switching

// WPM tracking configuration
#define WPM_LAUNCH_CONTROL  // Enable WPM launch control features
#define WPM_ALLOW_COUNT_REGRESSION  // Allow WPM to decrease naturally

// Menu system for OLED encoder navigation
// 0: Main (animated + stats), 1-6: Layer displays (layers 0-2, left/right split)
#define MENU_MODES 7

// Encoder configuration for different layer behaviors
// Layer 0: Volume control, Layer 1: Brightness control, Layer 2: Reserved for future use
#define ENCODER_RESOLUTION 4  // 4 pulses per detent for standard rotary encoder

// Mouse acceleration levels (0: slow, 1: medium, 2: fast)
#define MK_3_SPEED

// Last key pressed tracking for OLED display
#define LAST_KEY_BUFFER_SIZE 1  // Store last key presses for display

// Personal best WPM tracking (resets on power cycle)
// Will be stored in RAM, not EEPROM to avoid wear
#define WPM_PERSONAL_BEST_ENABLE
