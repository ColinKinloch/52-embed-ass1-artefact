#ifndef CK_LED
#define CK_LED

#define T_D01 0b11001111
#define T_D23 0b11101011
#define T_D45 0b11011011
#define T_D67 0b11111001

#define D0 0b00010000
#define D1 0b00100000
#define D2 0b00010000
#define D3 0b00000100
#define D4 0b00100000
#define D5 0b00000100
#define D6 0b00000100
#define D7 0b00000010

#define BIT(var,i) ((var & (1 << i)) >> i)

void ledUpdate(unsigned char leds, unsigned char tick);

#endif//CK_LED