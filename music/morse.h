#pragma once
#include "tones.h"
// 140 bpm
#define CTVRT 428  // v ms

// fedora
const uint16_t morse1[] PROGMEM = {
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT, a2, CTVRT / 2,  // F
    a2, CTVRT / 2,                                           // E
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2,                 // D
    a2, CTVRT, a2, CTVRT, a2, CTVRT,                         // O
    a2, CTVRT / 2, a2, CTVRT, a2, CTVRT / 2,                 // R
    a2, CTVRT / 2, a2, CTVRT,                                // A
};

// ubuntu
const uint16_t morse2[] PROGMEM = {
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT / 2,  // B
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
    a2, CTVRT, a2, CTVRT / 2,                                // N
    a2, CTVRT,                                               // T
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
};

// debian
const uint16_t morse3[] PROGMEM = {
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2,                 // D
    a2, CTVRT / 2,                                           // E
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT / 2,  // B
    a2, CTVRT / 2, a2, CTVRT / 2,                            // I
    a2, CTVRT / 2, a2, CTVRT,                                // A
    a2, CTVRT, a2, CTVRT / 2,                                // N
};