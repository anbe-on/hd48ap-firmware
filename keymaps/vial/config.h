#pragma once

// Prevent multiple inclusion of this config during compilation
#define VIAL_KEYBOARD_UID {0x99, 0xD9, 0xB4, 0x54, 0x2F, 0x22, 0x8F, 0x66} // Unique 8-byte identifier so Vial can detect this keyboard

#define VIAL_UNLOCK_COMBO_ROWS {0, 0} // Unlock combo row positions (row 0 for both keys)
#define VIAL_UNLOCK_COMBO_COLS {0, 1} // Unlock combo col positions (col 0 + col 1 on row 0 must be pressed together)
