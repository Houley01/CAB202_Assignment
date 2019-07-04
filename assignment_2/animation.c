/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: animation.c          *
*********************************************
*/
// ********* Standard Libaray *********
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// ********* CAB202 Libaray *********
#include <cpu_speed.h>
#include <graphics.h>
#include <macros.h>
#include "lcd.h"
#include "lcd_model.h"
#include "usb_serial.h"
#include "cab202_adc.h"
// ********* Custom Libaray *********
#include "screen.h"
#include "serial.h"
#include "controls.h"
#include "animation.h"
#include "gameInformation.h"

// *****************************

bool RUNANIMATION = true;
void Animation()
{
    int TextAsteroidXAxis = LCD_X + 5, TextApocalypseXAxis = -65, TextSNumberXAxis = 30 + LCD_X;
    while (((RUNANIMATION == true)) && !BIT_IS_SET(PINF, 6))
    {
        KeyboardInput(usb_serial_getchar());
        clear_screen();
        draw_string(TextAsteroidXAxis, (LCD_Y / 2) - 9, "Asteroid", FG_COLOUR);
        draw_string(TextApocalypseXAxis, (LCD_Y / 2), "Apocalypse", FG_COLOUR);
        draw_string(TextSNumberXAxis, LCD_Y - 9, "n10353950", FG_COLOUR);

        TextAsteroidXAxis--;
        TextApocalypseXAxis++;
        TextSNumberXAxis--;

        // Checks to see if variable is greater then or equal to x
        if (TextAsteroidXAxis <= 22)
        {
            TextAsteroidXAxis = 22;
        }
        if (TextApocalypseXAxis >= 17)
        {
            TextApocalypseXAxis = 17;
        }
        if (TextSNumberXAxis <= 20)
        {
            TextSNumberXAxis = 20;
        }
        show_screen();

        // Reads the Pulse from the Potentiometer 0 (POT0)
        long POT0 = adc_read(0);

        ChangeBacklightLCD(1023 - POT0);
        // delay between loops
        _delay_ms(25);
    }
    RUNANIMATION = false;
    clear_screen();
}

bool ReturnRunAnimationBool()
{
    return RUNANIMATION;
}

void SetFalseRunanimation()
{
    RUNANIMATION = false;
}