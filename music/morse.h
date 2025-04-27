#pragma once
#include "tones.h"
// 140 bpm
#define CTVRT 700  // v ms

// fedora
const uint16_t morse1[] PROGMEM = {
    a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT, a2, CTVRT / 3,  // F
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3,                                           // E
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT / 3, a2, CTVRT / 3,                 // D
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT, a2, CTVRT,                         // O
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT, a2, CTVRT / 3,                 // R
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT,                                // A
    POMLKA, 3 * CTVRT,                                       //
};

// ubuntu
const uint16_t morse2[] PROGMEM = {
    a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT,                 // U
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT / 3,  // B
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT,                 // U
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT / 3,                                // N
    POMLKA, CTVRT,                                           //
    a2, CTVRT,                                               // T
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT,                 // U
    POMLKA, 3 * CTVRT,                                       //
};

// debian
const uint16_t morse3[] PROGMEM = {
    a2, CTVRT, a2, CTVRT / 3, a2, CTVRT / 3,                 // D
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3,                                           // E
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT / 3, a2, CTVRT / 3, a2, CTVRT / 3,  // B
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT / 3,                            // I
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT,                                // A
    POMLKA, CTVRT,                                           //
    a2, CTVRT, a2, CTVRT / 3,                                // N
    POMLKA, 3 * CTVRT,                                       //
};