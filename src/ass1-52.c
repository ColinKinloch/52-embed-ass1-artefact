#include <pic14regs.h>
#include <stdint.h>
#include "button.h"
#include "led.h"

static __code uint16_t __at (_CONFIG) configword = _CP_OFF & _BOREN_ON & _MCLRE_OFF & _PWRTE_ON & _WDT_OFF & _FOSC_INTRCIO;

Button but;
long n = 0;
unsigned char i = 0;
unsigned char led = 0;//0b10101010;


static void timer_isr(void) __interrupt (2)
{
	butUpdate(&but, !GP3);
	
	if(BUTJP(but))
	 GO = 1;
	if(ADIF)
	{
		ADIF = 0;
		led = (ADRESH<<8)|ADRESL;
	}
	
	ledUpdate(led, i);
	i++;
	n++;
}

void main(void)
{
	ANSEL = 0b00100001;
	ANS0 = 1;
	ANS1 = 0;
	ANS2 = 0;
	
	ADON = 1;
	ADFM = 1;
	VCFG = 0;
	
	TMR1ON = 1;
	
	CMCON = 0b00000000;
	
	T0IE = 1;
	GIE = 1;
	TMR0 = 0;
	
	while(1)
	{
	}
}