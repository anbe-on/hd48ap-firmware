#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE

// Animation states
typedef enum {
    IDLE,
    PREP,
    TAP
} bongocat_state_t;

// Configuration
#define BONGOCAT_FRAME_DURATION 500
#define BONGOCAT_TAP_DURATION 150
#define BONGOCAT_PREP_DURATION 100

// WPM threshold for triggering animations
#ifndef BONGOCAT_WPM_THRESHOLD
#define BONGOCAT_WPM_THRESHOLD 20
#endif

// Function declarations
void render_bongocat(void);
void bongocat_animation_update(void);

#endif
