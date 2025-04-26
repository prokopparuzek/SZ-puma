#pragma once
#include "tones.h"
// 140 bpm
#define CTVRT 428  // v ms

// fedora
const uint16_t morse1[] PROGMEM = {
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT, a2, CTVRT / 2,  // F
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2,                                           // E
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2,                 // D
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT, a2, CTVRT,                         // O
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT, a2, CTVRT / 2,                 // R
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT,                                // A
    POMLKA, CTVRT,                                           //
};

// ubuntu
const uint16_t morse2[] PROGMEM = {
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT / 2,  // B
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT / 2,                                // N
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT,                                               // T
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT,                 // U
    POMLKA, CTVRT,                                           //
};

// debian
const uint16_t morse3[] PROGMEM = {
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2,                 // D
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2,                                           // E
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT / 2, a2, CTVRT / 2, a2, CTVRT / 2,  // B
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT / 2,                            // I
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT / 2, a2, CTVRT,                                // A
    POMLKA, CTVRT / 2,                                       //
    a2, CTVRT, a2, CTVRT / 2,                                // N
    POMLKA, CTVRT,                                           //
};