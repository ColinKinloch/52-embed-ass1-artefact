#include <pic14regs.h>
#include <stdint.h>
#include "button.h"
#include "led.h"
#include "clock.h"

static __code uint16_t __at (_CONFIG) configword = 
   _CP_OFF // Code protection disable
 & _BOREN_ON // Brown out
 & _MCLRE_OFF
 & _PWRTE_ON
 & _WDT_OFF
 & _FOSC_INTRCIO;

Clock clk;
Button but;
uint8_t i = 0;
uint8_t i1 = 0;
#define IMAX 8
uint8_t led = 0b10101010;

void butUpdate()
{
	if(!GP3)
	 but.current = 1;
	else
	 but.current = 0;
	
	if((but.last & 1)&&(but.current == 1))
	 but.current = 3;
	else if(!(but.last & 1)&&(but.current == 0))
	 but.current = 2;
	
	but.last = but.current;
}

static void isr(void) __interrupt (0)
{
	if(TMR0IF && TMR0IE) // Timer0 overflow interrupt
	{
		butUpdate();
		
		if(BUTP(but)&&!GO)
		 GO = 1; // Start ADC
		
		ledUpdate(led, i);
		
		i++;
		if(i>IMAX)
		 i=0;
		
		TMR0IF = 0; // Timer overflow reset
	}
	else if(TMR1IF && TMR1IE) // Timer1 overflow interrupt
	{
		if(GETTIME(clk)>0)
		{
			led = GETDISPLAY(clk);
			clk.currentTime++;
		}
		else
		{
			if(i1 & 1)
			
			 led = 0b01011010;
			else
			 led = 0b10100101;
		}
		
		i1++;
		TMR1IF = 0; // Timer overflow reset
	}
	else if(ADIF && ADIE) // ADC ready
	{
		clk.alarmTime = ADRESH;
		led = GETPROGRESS(ADRESH/(255/8)); // Final 8 bits of 10 bit result
		clk.currentTime = 0;
		
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
	// Interrupt settings
	GIE = 1; // Global interrupt enable
	PEIE = 1; // Peripheral interrupt enable
	TMR0IE = 1; // Timer0 interrupt enable
	GPIE = 0; // GPIO interrupt enable
	TMR1IE = 1; // Timer1 interrupt enable
	ADIE = 1; // ADC interrupt enable
	
	// Comparator control (CMCON)
	CMCON = 0x00000000;
	
	if(ADIE)
	{
		// ADC Config (ADCON0)
		ADON = 1; // Analogue to Digital on
		CHS0 = 0; // Channel select for pin: [00=AN0=Potentiometer]
		CHS1 = 0;
		VCFG = 0; // Voltage
		ADFM = 0; // Justification [0=Left, 1=Right]
		//Analogue select (ANSEL)
		ANS0 = 1; // Analogue select register
		ANS1 = 0;
		ANS2 = 0;
		ADCS0 = 1; // ADC clock select
		ADCS1 = 0;
		ADCS2 = 0;
	}
	
	if(TMR0IE)
	{
		// Timer0 Config
		T0CS = 0; // Clock source [0=Instruction clock, 1=GP2/T0CKI]
		PSA = 0; // Attach prescaler to [0=Timer0, 1=WDT]
		PS0 = 0; // Set prescaler
		PS1 = 0;
		PS2 = 0;
	}
	
	if(TMR1IE)
	{
		//Timer1 Config
		TMR1ON = 1; // Timer1 enable
		TMR1CS = 0; // Clock source [0=Internal, 1=External]
		NOT_T1SYNC = 0; // Sync external clock
		T1OSCEN = 0; // LP oscillator enabled (only if INTOSC without CLKOUT oscillator is active)
		T1CKPS0 = 1; // Set prescaler
		T1CKPS1 = 1;
		TMR1GE = 1; // Gate enable
	}
	
	while(1);
}