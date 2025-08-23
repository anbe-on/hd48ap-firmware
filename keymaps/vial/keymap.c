#include QMK_KEYBOARD_H
#include "bongocat.h"

// Screen mode tracking
static screen_mode_t current_screen = SCREEN_BONGOCAT;
static uint32_t last_oled_update = 0;

// Keymap matching your Vial layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
        KC_LGUI, MO(2),   MO(1),   KC_LCTL, KC_LALT, KC_SPC,  KC_SPC,  MO(1),   KC_APP,  MO(3),   KC_LBRC, KC_RBRC
    ),

    [1] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_ESC,  KC_DEL,  KC_BSPC, KC_ENT,  KC_HOME, KC_V,    KC_BSLS, KC_END,  KC_UP,   KC_RGHT, KC_RCTL, KC_LBRC,
        KC_LSFT, KC_PGUP, KC_PGDN, KC_C,    KC_V,    KC_TAB,  KC_LEFT, KC_DOWN, KC_RALT, KC_RSFT, KC_MINS, KC_EQL,
        KC_LGUI, KC_BRID, KC_BRIU, KC_LCTL, KC_LALT, KC_SPC,  KC_SPC,  KC_TRNS, KC_APP,  KC_TRNS, KC_VOLD, KC_VOLU
    ),

    [2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_ESC,  KC_DEL,  KC_BSPC, KC_ENT,  KC_MS_U, KC_V,    KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_BSPC,
        KC_LSFT, KC_PGUP, KC_PGDN, KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, KC_WH_U, KC_WH_D, KC_WH_L, KC_WH_R, KC_ENT,
        KC_LGUI, KC_TRNS, KC_TRNS, KC_LCTL, KC_LALT, KC_SPC,  KC_END,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [3] = LAYOUT(
        KC_TRNS, QK_BOOT, BL_STEP, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL,
        KC_TRNS, KC_TRNS, MU_MOD,  AU_ON,   AU_OFF,  AG_SWAP, AG_NORM, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, MU_ON,   MU_OFF,  KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TG(0),   KC_TRNS, KC_TRNS, TG(0),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// Encoder handling
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Layer-dependent encoder behavior
        switch (get_highest_layer(layer_state)) {
            case 0: // Base layer - Up/Down arrow
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
                break;
            case 1: // Layer 1 - Left/Right arrow
                if (clockwise) {
                    tap_code(KC_LEFT);
                } else {
                    tap_code(KC_RGHT);
                }
                break;
            case 2: // Layer 2 - Mouse scroll
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;
            default: // Layer 3+ - Screen mode switching
                if (clockwise) {
                    current_screen = (current_screen + 1) % SCREEN_MAX;
                } else {
                    current_screen = (current_screen == 0) ? SCREEN_MAX - 1 : current_screen - 1;
                }
                break;
        }
    }
    return true;
}

// OLED Display Functions
#ifdef OLED_ENABLE

void render_system_info(void) {
    oled_write_P(PSTR("HD48AP Keyboard\n"), false);
    oled_write_P(PSTR("Layer: "), false);
    oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
    oled_write_P(PSTR("\nWPM: "), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);

    // LED indicators
    led_t led_state = host_keyboard_led_state();
    oled_write_P(PSTR("\nCaps: "), false);
    oled_write_P(led_state.caps_lock ? PSTR("ON") : PSTR("OFF"), false);
    oled_write_P(PSTR(" Num: "), false);
    oled_write_P(led_state.num_lock ? PSTR("ON") : PSTR("OFF"), false);

    // Screen mode indicator
    oled_write_P(PSTR("\nMode: "), false);
    switch (current_screen) {
        case SCREEN_BONGOCAT:
            oled_write_P(PSTR("BongoCat"), false);
            break;
        case SCREEN_SYSTEM_INFO:
            oled_write_P(PSTR("System"), false);
            break;
    }

    // Memory usage simulation (placeholder)
    oled_write_P(PSTR("\nRAM: 45%"), false);
    oled_write_P(PSTR(" CPU: 23%"), false);

    // Bootloader status
    oled_write_P(PSTR("\nBootloader: "), false);
    oled_write_P(PSTR("Unlocked"), false); // This would need actual detection
}

bool oled_task_user(void) {
    // Throttle OLED updates
    if (timer_elapsed32(last_oled_update) < OLED_UPDATE_INTERVAL) {
        return false;
    }
    last_oled_update = timer_read32();

    oled_clear();

    switch (current_screen) {
        case SCREEN_BONGOCAT:
            render_bongocat();
            break;
        case SCREEN_SYSTEM_INFO:
            render_system_info();
            break;
        default:
            render_system_info();
            break;
    }

    return false;
}

void oled_task_user_init(void) {
    last_oled_update = timer_read32();
}

#endif

// Keyboard initialization
void keyboard_post_init_user(void) {
    #ifdef OLED_ENABLE
    oled_task_user_init();
    #endif
}

// Layer state change
layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}

// Process record for custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}
