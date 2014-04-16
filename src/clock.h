#ifndef CK_CLOCK
#define CK_CLOCK

#include <stdint.h>
#include "led.h"

typedef struct Clock
{
	uint8_t currentTime; // Current state of button
	uint8_t alarmTime; // Previous state of button
	uint8_t status:1;
	uint8_t multiplier:3;
} Clock;

// Updates but object 
uint8_t getDisplay(struct Clock *clock);
uint8_t getTime(struct Clock *clock);

#define GETTIME(clock) (clock.alarmTime-clock.currentTime)
//TODO Fix for times under 8 units
#define GETDISPLAY(clock) GETPROGRESS(GETTIME(clock)/(clock.alarmTime/8));

#endif//CK_CLOCK