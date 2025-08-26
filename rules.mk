# MCU and bootloader - Standard for Pro Micro/ATmega32U4; no change needed
MCU = atmega32u4
BOOTLOADER = caterina

# Optimize for size instead of speed
OPT = s
# Link Time Optimization
LTO_ENABLE = yes
# Enables - These turn on features; relate to code in keymap.c e.g., OLED_ENABLE allows oled_task_user
# For bootmagic or reset combos
BOOTMAGIC_ENABLE = no
# For media/system keys
EXTRAKEY_ENABLE = yes
# Switches off the dual-role Grave/Esc tapped/held behavior GRAVE_ESC_ENABLE=no
# Disables Space Cadet Shift: tapping Shift outputs parentheses (e.g., tap left shift → “(”, hold → Shift)
SPACE_CADET_ENABLE=no
# OLED screen support
OLED_ENABLE = yes
# Your SSD1306 OLED
OLED_DRIVER = ssd1306
# Rotary encoder
ENCODER_ENABLE = yes
# Words per minute
WPM_ENABLE = no
# Mouse keys movement, click, scroll
MOUSEKEY_ENABLE = yes
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no

# Disable unused to save space - These reduce firmware size; no impact on code unless enabled
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
NKRO_ENABLE = no
BACKLIGHT_ENABLE = no
RGBLIGHT_ENABLE = no
# Enable Bluetooth
BLUETOOTH_ENABLE = no
AUDIO_ENABLE = no
MUSIC_ENABLE = no
TRI_LAYER_ENABLE = no
LAYER_LOCK_ENABLE = no
CAPS_WORD_ENABLE = no
TAP_DANCE_ENABLE = no
REPEAT_KEY_ENABLE = no
COMBO_ENABLE = no
EXTRAFLAGS += -flto

# Custom matrix - Tells QMK to use your matrix.c instead of default; relates directly to matrix.c
CUSTOM_MATRIX = yes

# Add the source file explicitly
SRC += matrix.c
