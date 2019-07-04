#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <lcd.h>
#include "lcd_model.h"

void setup(void)
{
    set_clock_speed(CPU_8MHz);

    //	(a) Enable input from the joystick-left switch and joystick-right switch.
    CLEAR_BIT(DDRB, 1); // Switch B (LEFT)
    CLEAR_BIT(DDRD, 0); // Switch D (Right)

    //	(b) Initialise the LCD display using the default contrast setting.
    lcd_init(LCD_DEFAULT_CONTRAST);

    //	(c) Use one of the functions declared in "graphics.h" to display
    //	your student number, "n10353950", using the foreground colour,
    //	positioning the left edge of the text at 19 and the nominal top
    //	of the text at 13.
    draw_string(19, 13, "n10353950", FG_COLOUR);

    //	(d) Use one of the functions declared in "graphics.h" to copy the contents
    //	of the screen buffer to the LCD.
    show_screen();
}

//	(e) Declare a global variable of type int named Contrast and
//	initialise it to the default LCD contrast.
int Contrast = 127;
void process(void)
{
    //	(f) Test pin corresponding to joystick-right switch. If closed,
    //	decrement Contrast by 9. If the result is less than zero,
    //	set Contrast to the maximum permitted LCD contrast value.
    if (BIT_IS_SET(PIND, 0))
    {
        Contrast = Contrast - 9;
        if (Contrast < 0)
        {
            Contrast = 127;
        }
    }

    //	(g) Test pin corresponding to joystick-left switch. If closed,
    //	increment Contrast by 9. If the result is greater
    //	then the maximum permitted LCD contrast value, set Contrast
    //	to zero.
    if (BIT_IS_SET(PINB, 1))
    {
        Contrast = Contrast + 9;
        if (Contrast > 127)
        {
            Contrast = 0;
        }
    }
    //	(h) Send a sequence of commands to the LCD to enable extended
    //	instructions, set contrast to the current value of Contrast,
    //	and finally retore the LCD to basic instruction mode.
    lcd_write(LCD_C, 0x21);            // Enable LCD extended command set
    lcd_write(LCD_C, 0x80 | Contrast); // Set LCD Vop (Contrast)

    lcd_write(LCD_C, 0x0C); // LCD in normal mode.
    lcd_write(LCD_C, 0x20); // Enable LCD basic command set
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
