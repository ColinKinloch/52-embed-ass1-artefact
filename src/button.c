#include "button.h"

void butUpdate(struct Button *but, unsigned char input)
{
	if(input)
	{
		but->current = 1;
	}
	else
	{
		but->current = 0;
	}
	
	if((but->last & 1)&&(but->current == 1))
	{
		but->current = 3;
	}
	else if(!(but->last & 1)&&(but->current == 0))
	{
		but->current = 2;
	}
	
	but->last = but->current;
	
}