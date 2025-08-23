#pragma once

#include "quantum.h"

// Layout macro for 12x4 ortholinear (48 keys)
// Mapped to 8x6 matrix for easier QMK handling
#define LAYOUT( \
    K00, K01, K10, K11, K20, K21, K30, K31, K40, K41, K50, K51, \
    K02, K03, K12, K13, K22, K23, K32, K33, K42, K43, K52, K53, \
    K04, K05, K14, K15, K24, K25, K34, K35, K44, K45, K54, K55, \
    K60, K61, K70, K71, K62, K63, K72, K73, K64, K65, K74, K75  \
) { \
    { K00, K01, K02, K03, K04, K05 }, \
    { K10, K11, K12, K13, K14, K15 }, \
    { K20, K21, K22, K23, K24, K25 }, \
    { K30, K31, K32, K33, K34, K35 }, \
    { K40, K41, K42, K43, K44, K45 }, \
    { K50, K51, K52, K53, K54, K55 }, \
    { K60, K61, K62, K63, K64, K65 }, \
    { K70, K71, K72, K73, K74, K75 }  \
}

// Function declarations
void matrix_init_custom(void);
bool matrix_scan_custom(matrix_row_t current_matrix[]);
