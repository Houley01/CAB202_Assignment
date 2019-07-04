#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <lcd.h>
#include <macros.h>
#include "lcd_model.h"

void setup(void)
{
    set_clock_speed(CPU_8MHz);

    //	(a) Enable input from the Left, Right, Up, and Down switches
    //	of the joystick.

    //	(b) Initialise the LCD display using the default contrast setting.

    //	(c) Use one of the functions declared in "graphics.h" to display
    //	your student number, "n10353950", using the background colour,
    //	positioning the left edge of the text at 19 and the nominal top
    //	of the text at 13.

    //	(d) Use one of the functions declared in "graphics.h" to copy
    //	the contents of the screen buffer to the LCD.
}

void process(void)
{
    //  (e) Determine if the Up joystick switch is closed.
    //	If it is, set the LCD display to enter normal video mode.

    //  (f) OTHERWISE, determine if the Down joystick switch
    //	is closed. If it is, set the LCD display to switch to inverse video mode.

    //  (g) OTHERWISE, determine if the Left joystick switch
    //	is closed. If it is, set the LCD display to turn off all pixels.

    //  (h) OTHERWISE, determine if the Right joystick switch
    //	is closed. If it is, set the LCD display to turn on all pixels.

    //	If none of the joystick switches are closed, do nothing.
    //	(Hint: do not insert any more instructions.)
}

int main(void)
{
    setup();

    for (;;)
    {
        process();
        _delay_ms(100);
    }

    return 0;
}
