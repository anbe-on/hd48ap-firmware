#include "matrix.h"
#include "quantum.h"
#include <avr/io.h>
#include <util/delay.h>

// Pin array used here for scanning
#define NUM_PINS 14
const uint8_t charlie_pins[NUM_PINS] = {
// the way it does is matches the pin order in the table
//  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13
//  A3, A2, A1, A0, 16, 15, 14, 10, 9,  8,  7,  6,  1,  0
    F4, F5, F6, F7, B2, B1, B3, B6, B5, B4, E6, D7, D2, D3
};

// Pair struct - Simple type for high/low pins
typedef struct {
    uint8_t high;
    uint8_t low;
} pin_pair;

// Matrix pairs - From your table; each [row][col] = {high_pin_index, low_pin_index}
// Relation: Uses config.h's NUM_PINS and charlie_pins[]
const pin_pair matrix_pairs[MATRIX_ROWS][MATRIX_COLS] = {
    // Row 1
    {{0, 13}, {0, 12}, {1, 13}, {1, 12}, {2, 13}, {2, 12}, {3, 13}, {3, 12}, {4, 13}, {4, 12}, {5, 13}, {5, 12}},
    // Row 2
    {{0, 11}, {0, 10}, {1, 11}, {1, 10}, {2, 11}, {2, 10}, {3, 11}, {3, 10}, {4, 11}, {4, 10}, {5, 11}, {5, 10}},
    // Row 3
    {{0, 4},  {0, 7}, {1, 4},  {1, 7}, {2, 4},  {2, 7}, {3, 4},  {3, 7}, {4, 4},  {4, 7}, {5, 4},  {5, 7}},
    // Row 4
    {{0, 8},  {0, 9},  {1, 8},  {1, 9},  {2, 8},  {2, 9},  {3, 8},  {3, 9},  {4, 8},  {4, 9},  {5, 8},  {5, 9}}
};

// Matrix state - Global array to store row states; used by QMK core
static matrix_row_t raw_matrix[MATRIX_ROWS] = {0};
static matrix_row_t matrix[MATRIX_ROWS] = {0};

// Init - Set pins input; called once (relates to QMK startup)
void matrix_init(void) {
    // Set all pins to input with pullup disabled initially
    for (uint8_t i = 0; i < NUM_PINS; i++) {
        setPinInput(charlie_pins[i]);  // Input mode
        writePinLow(charlie_pins[i]);
    }

    // Initialize matrix arrays
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
}

// Scan - Custom Charlieplex scan; loops rows/cols, sets high/low, reads; returns if changed
// Relation: Called every cycle by QMK; updates matrix[] for key detection
uint8_t matrix_scan(void) {
    bool changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t current_row = 0;

        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            pin_pair p = matrix_pairs[row][col];

            // Set all pins to input with no pullup
            for (uint8_t i = 0; i < NUM_PINS; i++) {
                setPinInput(charlie_pins[i]);
                writePinLow(charlie_pins[i]);
            }

            // Set high pin as output high
            setPinOutput(charlie_pins[p.high]);
            writePinHigh(charlie_pins[p.high]);

            // Set low pin as input with pullup
            setPinInputHigh(charlie_pins[p.low]);

            // Small delay for signal to settle
            _delay_us(10);
            // Read the low pin - if it's low, key is pressed
            if (!readPin(charlie_pins[p.low])) {
                current_row |= (1UL << col);
            }
        }

        // Check if this row changed
        if (raw_matrix[row] != current_row) {
            raw_matrix[row] = current_row;
            changed = true;
        }
    }

    // Copy raw matrix to debounced matrix (you can add debouncing here if needed)
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        matrix[row] = raw_matrix[row];
    }

    return changed ? 1 : 0;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix[row];
}

void matrix_print(void) {
    // Optional debug function
}

bool matrix_is_on(uint8_t row, uint8_t col) {
    return (matrix_get_row(row) & ((matrix_row_t)1 << col)) != 0;
}
