#ifndef CK_BUTTON
#define CK_BUTTON

#include <stdint.h>

#define BUTP(but) (but.current & 1) // Check if button is currently pressed
#define BUTJP(but) (but.current == 1) // Check if button has just been pressed
#define BUTJR(but) (but.current == 0) // Check if button has just been released

typedef struct Button
{
	uint8_t current:2; // Current state of button
	uint8_t last:2; // Previous state of button
} Button;

// Updates but object 
void butUpdate(struct Button *but, uint8_t input);

#endif//CK_BUTTON