#ifndef CK_LED
#define CK_LED

#include <stdint.h>
#include <pic14regs.h>
#include "util.h"

// TRIS settings for different LEDs
#define TDNA 1
#define TD01 0b11001111
#define TD23 0b11101011
#define TD45 0b11011011
#define TD67 0b11111001

// GPIO settings for different LEDs
#define DNA 0
#define D0 0b00010000
#define D1 0b00100000
#define D2 0b00010000
#define D3 0b00000100
#define D4 0b00100000
#define D5 0b00000100
#define D6 0b00000100
#define D7 0b00000010

void ledUpdate(uint8_t leds, uint8_t tick);
// 0-8 to light up a row of led
#define GETPROGRESS(val) ((1<<((uint8_t)val))-1);

#endif//CK_LED