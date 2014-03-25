#include <pic12f675.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG) configword = _CP_OFF & _BOREN_ON & _MCLRE_OFF & _PWRTE_ON & _WDT_OFF & _FOSC_INTRCIO;

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

uint8_t buttOn;

void main(void)
{
	while(1)
	{
		
	}
}