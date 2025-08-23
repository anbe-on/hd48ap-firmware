#include "matrix.h"
#include "quantum.h"
#include "debounce.h"
#include "wait.h"

// Pin definitions for your ATmega32U4
// Based on your pinout: 0=RX, 1=TX, 2=SDA, 3=SCL, 4=D4, etc.
#define PIN_RX   0   // Pin 0
#define PIN_TX   1   // Pin 1
#define PIN_SDA  2   // Pin 2 (OLED)
#define PIN_SCL  3   // Pin 3 (OLED)
#define PIN_D4   4   // Pin 4 (encoder)
#define PIN_D5   5   // Pin 5 (encoder)
#define PIN_D6   6   // Pin 6
#define PIN_D7   7   // Pin 7
#define PIN_D8   8   // Pin 8
#define PIN_D9   9   // Pin 9
#define PIN_D10  10  // Pin 10
#define PIN_D14  14  // Pin 14
#define PIN_D15  15  // Pin 15
#define PIN_D16  16  // Pin 16
#define PIN_A0   18  // Pin 18 (A0)
#define PIN_A1   19  // Pin 19 (A1)
#define PIN_A2   20  // Pin 20 (A2)
#define PIN_A3   21  // Pin 21 (A3)

// Physical matrix mapping - each key uses two pins
typedef struct {
    uint8_t row_pin;
    uint8_t col_pin;
} key_pin_t;

// Your exact physical matrix mapping (4 rows x 12 cols = 48 keys)
static const key_pin_t key_pins[4][12] = {
    // Physical Row 1: A3+0, A3+1, A2+0, A2+1, A1+0, A1+1, A0+0, A0+1, 15+0, 15+1, 14+0, 14+1
    {{PIN_A3, PIN_RX}, {PIN_A3, PIN_TX}, {PIN_A2, PIN_RX}, {PIN_A2, PIN_TX}, {PIN_A1, PIN_RX}, {PIN_A1, PIN_TX},
     {PIN_A0, PIN_RX}, {PIN_A0, PIN_TX}, {PIN_D15, PIN_RX}, {PIN_D15, PIN_TX}, {PIN_D14, PIN_RX}, {PIN_D14, PIN_TX}},

    // Physical Row 2: A3+6, A3+7, A2+6, A2+7, A1+6, A1+7, A0+6, A0+7, 15+6, 15+7, 14+6, 14+7
    {{PIN_A3, PIN_D6}, {PIN_A3, PIN_D7}, {PIN_A2, PIN_D6}, {PIN_A2, PIN_D7}, {PIN_A1, PIN_D6}, {PIN_A1, PIN_D7},
     {PIN_A0, PIN_D6}, {PIN_A0, PIN_D7}, {PIN_D15, PIN_D6}, {PIN_D15, PIN_D7}, {PIN_D14, PIN_D6}, {PIN_D14, PIN_D7}},

    // Physical Row 3: A3+16, A3+10, A2+16, A2+10, A1+16, A1+10, A0+16, A0+10, 15+16, 15+10, 14+16, 14+10
    {{PIN_A3, PIN_D16}, {PIN_A3, PIN_D10}, {PIN_A2, PIN_D16}, {PIN_A2, PIN_D10}, {PIN_A1, PIN_D16}, {PIN_A1, PIN_D10},
     {PIN_A0, PIN_D16}, {PIN_A0, PIN_D10}, {PIN_D15, PIN_D16}, {PIN_D15, PIN_D10}, {PIN_D14, PIN_D16}, {PIN_D14, PIN_D10}},

    // Physical Row 4: A3+9, A3+8, A2+9, A2+8, A1+9, A1+8, A0+9, A0+8, 15+9, 15+8, 14+9, 14+8
    {{PIN_A3, PIN_D9}, {PIN_A3, PIN_D8}, {PIN_A2, PIN_D9}, {PIN_A2, PIN_D8}, {PIN_A1, PIN_D9}, {PIN_A1, PIN_D8},
     {PIN_A0, PIN_D9}, {PIN_A0, PIN_D8}, {PIN_D15, PIN_D9}, {PIN_D15, PIN_D8}, {PIN_D14, PIN_D9}, {PIN_D14, PIN_D8}}
};

static matrix_row_t raw_matrix[MATRIX_ROWS];
static matrix_row_t matrix[MATRIX_ROWS];

// Convert physical position to QMK matrix position
static inline void physical_to_matrix(uint8_t phys_row, uint8_t phys_col, uint8_t *matrix_row, uint8_t *matrix_col) {
    // Map 4x12 physical to 8x6 matrix
    *matrix_row = (phys_row * 2) + (phys_col / 6);
    *matrix_col = phys_col % 6;
}

// Read a single key
static inline bool read_key(uint8_t row_pin, uint8_t col_pin) {
    // Skip reserved pins
    if (row_pin == PIN_SDA || row_pin == PIN_SCL ||
        col_pin == PIN_SDA || col_pin == PIN_SCL ||
        row_pin == PIN_D4 || row_pin == PIN_D5 ||
        col_pin == PIN_D4 || col_pin == PIN_D5) {
        return false;
    }

    // Set row pin as output low
    setPinOutput(row_pin);
    writePinLow(row_pin);
    wait_us(10); // Small delay for signal stabilization

    // Set column pin as input with pullup and read
    setPinInputHigh(col_pin);
    bool pressed = !readPin(col_pin);

    // Reset pins to input with pullup
    setPinInputHigh(row_pin);

    return pressed;
}

void matrix_init_custom(void) {
    // Initialize all matrix pins as input with pullup
    uint8_t all_pins[] = {PIN_RX, PIN_TX, PIN_D6, PIN_D7, PIN_D8, PIN_D9, PIN_D10,
                         PIN_D14, PIN_D15, PIN_D16, PIN_A0, PIN_A1, PIN_A2, PIN_A3};

    for (uint8_t i = 0; i < sizeof(all_pins); i++) {
        setPinInputHigh(all_pins[i]);
    }

    // Initialize matrix arrays
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    // Clear the raw matrix
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
    }

    // Scan all physical keys
    for (uint8_t phys_row = 0; phys_row < 4; phys_row++) {
        for (uint8_t phys_col = 0; phys_col < 12; phys_col++) {
            key_pin_t key = key_pins[phys_row][phys_col];
            bool pressed = read_key(key.row_pin, key.col_pin);

            if (pressed) {
                uint8_t matrix_row, matrix_col;
                physical_to_matrix(phys_row, phys_col, &matrix_row, &matrix_col);
                raw_matrix[matrix_row] |= (1UL << matrix_col);
            }
        }
    }

    // Apply debouncing
    debounce(raw_matrix, current_matrix, MATRIX_ROWS, changed);

    // Check for changes
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != current_matrix[i]) {
            matrix[i] = current_matrix[i];
            changed = true;
        }
    }

    return changed;
}

uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}
