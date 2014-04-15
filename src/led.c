#define __12f675
#include <pic12f675.h>
#include "led.h"

void ledUpdate(unsigned char leds, unsigned char tick)
{
	if(BIT(leds, tick%8))
	{
		switch(tick%8)
		{
			case 0:
			{
				TRISIO = T_D01;
				GPIO = D0;
				break;
			}
			case 1:
			{
				TRISIO = T_D01;
				GPIO = D1;
				break;
			}
			case 2:
			{
				TRISIO = T_D23;
				GPIO = D2;
				break;
			}
			case 3:
			{
				TRISIO = T_D23;
				GPIO = D3;
				break;
			}
			case 4:
			{
				TRISIO = T_D45;
				GPIO = D4;
				break;
			}
			case 5:
			{
				TRISIO = T_D45;
				GPIO = D5;
				break;
			}
			case 6:
			{
				TRISIO = T_D67;
				GPIO = D6;
				break;
			}
			case 7:
			{
				TRISIO = T_D67;
				GPIO = D7;
				break;
			}
		}
	}
	else
	{
		TRISIO = 0;
		GPIO = 0;
	}
}