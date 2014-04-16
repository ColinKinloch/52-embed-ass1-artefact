#include "led.h"

void ledUpdate(uint8_t leds, uint8_t tick)
{
	if(BIT(leds, tick))
	{
		switch(tick)
		{
			case 0:
			{
				TRISIO = TD01;
				GPIO = D0;
				break;
			}
			case 1:
			{
				TRISIO = TD01;
				GPIO = D1;
				break;
			}
			case 2:
			{
				TRISIO = TD23;
				GPIO = D2;
				break;
			}
			case 3:
			{
				TRISIO = TD23;
				GPIO = D3;
				break;
			}
			case 4:
			{
				TRISIO = TD45;
				GPIO = D4;
				break;
			}
			case 5:
			{
				TRISIO = TD45;
				GPIO = D5;
				break;
			}
			case 6:
			{
				TRISIO = TD67;
				GPIO = D6;
				break;
			}
			case 7:
			{
				TRISIO = TD67;
				GPIO = D7;
				break;
			}
		}
	}
	else
	{
		TRISIO = TDNA;
		GPIO = DNA;
	}
}