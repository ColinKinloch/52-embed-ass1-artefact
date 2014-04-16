#include <pic14regs.h>
#include <stdint.h>
#include "button.h"
#include "led.h"

static __code uint16_t __at (_CONFIG) configword = _CP_OFF & _BOREN_ON & _MCLRE_OFF & _PWRTE_ON & _WDT_OFF & _FOSC_INTRCIO;

Button but;
uint32_t n = 0;
uint8_t temp;
uint8_t i = 0;
#define IMAX 9
uint8_t led = 0b10101010;


static void timer_isr(void) __interrupt (0)
{
	if(TMR0IF && TMR0IE) // Timer0 overflow interrupt
	{
		if(n & 1)
		 led = 0b11110000;
		else
		 led = 0b00001111;
		
		TMR0IF = 0; // reset
	}
	else if(TMR1IF && TMR1IE) // Timer1 overflow interrupt
	{
		if(!BUTP(but))
		{
			if(n & 1)
			 led = 0b01011010;
			else
			 led = 0b10100101;
		}
		n++;
		
		TMR1IF = 0; // Timer overflow reset
	}
	else if(ADIF && ADIE) // ADC ready
	{
		TRISIO = 0;
		GPIO = 0;
		led = ADRESH; // Final 8 bits of 10 bit result
		
		ADIF = 0; // reset
	}
	else // This is an error case
	{
		led = 0b11111111;
	}
	
	
	// Debug: Interrupt flag clear all for
	/*
	GPIF = 0; // Port Change
	TMR0IF = 0; // Timer0
	TMR1IF = 0; // Timer1
	CMIF = 0; // Comparator
	ADIF = 0; // ADC
	EEIF = 0; // EEPROM r/w
	*/
}

void main(void)
{
	// Analogue select register
	ANS0 = 1;
	ANS1 = 0;
	ANS2 = 0;
	
	// ADC Config (ADCON0bits)
	ADON = 1; // Analogue to Digital on
	CHS0 = 0; // Channel select for pin: [00=AN0=Potentiometer]
	CHS1 = 0;
	VCFG = 0; // Voltage
	ADFM = 0; // Justification [0=Left, 1=Right]
	
	// Timer0 Config
	PSA = 0; // Attach prescaler to [0=Timer0, 1=WDT]
	PS0 = 0; // Set prescaler
	PS1 = 0;
	PS2 = 0;
	
	//Timer1 Config
	TMR1ON = 1; // Timer1 enable
	TMR1CS = 0; // Clock source [0=Internal, 1=External]
	NOT_T1SYNC = 0; // Sync external clock
	T1OSCEN = 0; // LP oscillator enabled (only if INTOSC without CLKOUT oscillator is active)
	T1CKPS0 = 1; // Set prescaler
	T1CKPS1 = 1;
	TMR1GE = 1; // Gate enable
	
	GIE = 1; // Global interrupt enable
	PEIE = 1; // Peripheral interrupt enable
	
	TMR0IE = 1; // Timer0 interrupt enable
	TMR1IE = 1; // Timer1 interrupt enable
	ADIE = 1; // ADC interrupt enable
	
	CMCON = 0b00000000;
	
	while(1)
	{
		butUpdate(&but, !GP3);
		
		if(BUTJR(but))
		 GO = 1; // Start ADC
		
		ledUpdate(led, i);
		i++;
	}
}