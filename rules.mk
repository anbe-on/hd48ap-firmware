# MCU and bootloader configuration - Standard for ATmega32U4 with Caterina bootloader
MCU = atmega32u4
BOOTLOADER = caterina

# Compilation optimizations for performance and size
# Optimize for size to fit more features
OPT = s
# Link Time Optimization for better performance and smaller size
LTO_ENABLE = yes
# Additional LTO flags
EXTRAFLAGS += -flto

# Core QMK features for fast typing response
# Disable bootmagic to save space and boot time
BOOTMAGIC_ENABLE = no
# Enable mouse keys for Layer 2 mouse functions
MOUSEKEY_ENABLE = yes
# Enable media/system keys for volume/brightness control
EXTRAKEY_ENABLE = yes
# N-Key Rollover for fast typing without ghosting
NKRO_ENABLE = yes

# Hardware-specific features
# Enable OLED display support
OLED_ENABLE = yes
# Specify SSD1306 OLED driver
OLED_DRIVER = ssd1306
# Enable rotary encoder support
ENCODER_ENABLE = yes
# Enable words-per-minute calculation
WPM_ENABLE = yes

# Disable unused features to save flash space and improve performance
# Disable console for debugging (saves flash)
CONSOLE_ENABLE = no
# Disable command mode (saves flash)
COMMAND_ENABLE = no
# Disable audio features
AUDIO_ENABLE = no
# Disable music mode
MUSIC_ENABLE = no
# No backlight on this keyboard
BACKLIGHT_ENABLE = no
# No RGB lighting on this keyboard
RGBLIGHT_ENABLE = no
# No Bluetooth support needed
BLUETOOTH_ENABLE = no
# No RGB matrix support
RGB_MATRIX_ENABLE = no
# No LED matrix support
LED_MATRIX_ENABLE = no

# Disable advanced features that add latency or aren't needed
# Disable Space Cadet Shift to avoid typing delays
SPACE_CADET_ENABLE = no
# Disable Grave/Esc dual function for cleaner behavior
GRAVE_ESC_ENABLE = no
# Disable magic key combinations
MAGIC_ENABLE = no
# Disable tap dance for faster single-tap response
TAP_DANCE_ENABLE = no
# Disable combos for simpler key processing
COMBO_ENABLE = no
# Disable tri-layer functionality
TRI_LAYER_ENABLE = no
# Disable layer lock feature
LAYER_LOCK_ENABLE = no
# Disable caps word feature
CAPS_WORD_ENABLE = no
# Disable repeat key feature
REPEAT_KEY_ENABLE = no

# Use standard QMK matrix scanning (no custom matrix needed)
# Use QMK's optimized matrix scanning
CUSTOM_MATRIX = no

# Performance tuning flags
# Per-key debouncing for fastest response
DEBOUNCE_TYPE = sym_defer_pk
# Not a split keyboard
SPLIT_KEYBOARD = no
# Don't wait for USB connection on boot
WAIT_FOR_USB = no
