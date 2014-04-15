#ifndef CK_BUTTON
#define CK_BUTTON

#define BUTP(but) (but.current & 1) // Check if button is pressed
#define BUTJP(but) (but.current == 1) // Check if button has just been pressed
#define BUTJR(but) (but.current == 0) // Check if button has just been released

typedef struct Button
{
	unsigned char last:2;
	unsigned char current:2;
} Button;

void butUpdate(struct Button *but, unsigned char input);

#endif//CK_BUTTON