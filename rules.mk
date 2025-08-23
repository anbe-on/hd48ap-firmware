# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes        # Enable rotary encoder support
OLED_ENABLE = yes           # Enable OLED display
WPM_ENABLE = yes            # Enable WPM calculation for animations

# Custom matrix implementation
CUSTOM_MATRIX = lite

# Custom source files
SRC += matrix.c

# OLED Driver
OLED_DRIVER = SSD1306

# Default to yes
LTO_ENABLE = yes
