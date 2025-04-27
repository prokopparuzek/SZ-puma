#pragma once
#include "tones.h"
// 140 bpm
#define CTVRT 700  // v ms

// kali
const uint16_t morse1[] PROGMEM = {
    a2, CTVRT, a2, CTVRT / 3, a2, CTVRT,                     // K
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT,                                // A
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT, a2, CTVRT / 3, a2, CTVRT / 3,  // L
    POMLKA, CTVRT,                                           //
    a2, CTVRT / 3, a2, CTVRT / 3,                            // I
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

// mageia
const uint16_t morse3[] PROGMEM = {
    a2, CTVRT, a2, CTVRT,                 // M
    POMLKA, CTVRT,                        //
    a2, CTVRT / 3, a2, CTVRT,             // A
    POMLKA, CTVRT,                        //
    a2, CTVRT, a2, CTVRT, a2, CTVRT / 3,  // G
    POMLKA, CTVRT,                        //
    a2, CTVRT / 3,                        // E
    POMLKA, CTVRT,                        //
    a2, CTVRT / 3, a2, CTVRT / 3,         // I
    POMLKA, CTVRT,                        //
    a2, CTVRT / 3, a2, CTVRT,             // A
    POMLKA, 3 * CTVRT,                    //
};