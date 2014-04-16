#include "clock.h"

uint8_t getDisplay(struct Clock *clockIn)
{
	//return (255 - (1<<(8-(getTime(clockIn)/255))));
	return getTime(clockIn);
}

uint8_t getTime(struct Clock *clockIn)
{
	return clockIn->alarmTime-clockIn->currentTime;
}