/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: screen.c             *
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
#include "spaceObjects.h"
#include "starFighter.h"
#include "teensyTime.h"
#include "helpers.h"

// *****************************

// Change the brightness of the backlight on the LCD
void ChangeBacklightLCD(int reading)
{
    TC4H = reading >> 8;
    OCR4A = reading & 0xff;
}

// Set the lcd up and set the contrast for the lcd.
void SetupTheLCD()
{
    int Contrast = 35; // This is just so I can see on my screen
    lcd_init(LCD_DEFAULT_CONTRAST);
    lcd_write(LCD_C, 0x21);            // Enable LCD extended command set
    lcd_write(LCD_C, 0x80 | Contrast); // Set LCD Vop (Contrast)
    lcd_write(LCD_C, 0x0C);            // LCD in normal mode.
    lcd_write(LCD_C, 0x20);            // Enable LCD basic command set
}

void Quit()
{
    clear_screen();
    lcd_write(LCD_C, 0x0d); //  Change the screen to inverse video mode
    draw_string((LCD_X / 2 - 20), LCD_Y / 2, "n10353950", BG_COLOUR);
    show_screen();
    while (1)
    {
    }
}

// Send the computer controls to putty/Other serial programs
void HelpScreen()
{
    char *helpInfomation =
        "\r\nControls \r\n 'a' – move spaceship left \r\n 'd' – move spaceship right  \r\n 'w' – fire plasma bolts  \r\n 's' – send /display status  \r\n 'r' – start / reset 'p' – pause  \r\n 'q' – quit 't' – set aim(-60 to 60)  \r\n 'm' – set speed(0 to 10)  \r\n 'l' – set life  \r\n 'g' – set score  \r\n '?' – print controls  \r\n 'h' – spaceship to coord  \r\n 'j' – asteroid to coord  \r\n 'k' – boulder to coord  \r\n 'i' – fragment to coord  \r\n\r\n ";
    usb_serial_send(helpInfomation);
}

char buff[120];

// Send the game information to putty/Other serial programs
// e.g. Time, Number of lifes, score, Number of Asteroids,
// Number of Boulders, Number of Fragements, Number of bullets,
// the angle of the Aim, Speed of the game
void GameStatusSerial()
{
    // sends a message to putty/Other serial programs Leting the user know the game is starting
    if (ReturnGameStartMessage() == false && ReturnGameOver() == false)
    {
        usb_serial_send("\n\rGame Start!\n\r");
        SetGameStartMessageTrue();
    }

    send_formatted(buff, sizeof(buff),
                   "\n\rTime: %02d:%02d\n\rLife: %d\n\rScore: %d\n\rAsteroid: %d\n\rBoulder: %d\n\rFragments: %d\n\rBolts: %d\n\rAim: %d\n\rSpeed: %f\n\n",
                   ReturnMinutes(), ReturnSeconds(), ReturnLife(), ReturnScore(),
                   ReturnNumOfAsteroids(), ReturnNumOfBoulders(), ReturnNumOfFragments(),
                   NumberOfBullets(), ReturnAim(), ReturnSpeed());
}

// When the user press down on the joystick or press 's' on the keyboard the game
// information is sent to the computer. If the game is pause the lcd will change
// to show a small amount of information on the lcd as well as send information to
// the computer
void StatusDisplay()
{
    GameStatusSerial();
    while (ReturnPause() == true)
    {
        clear_screen();
        draw_formatted(1, 0, buff, "Time: %02d:%02d", ReturnMinutes(), ReturnSeconds());
        draw_formatted(1, 10, buff, "Life: %d", ReturnLife());
        draw_formatted(1, 20, buff, "Score: %d", ReturnScore());
        show_screen();
        if (usb_serial_getchar() == 'p' || BIT_IS_SET(PINB, 0))
        {
            SwitchPauseState();
        }
    }
}

// If life is equal to 0 then LCD Screen will change a message will be sent
// to the computer with the current game information.
void GameOver()
{
    if (ReturnLife() <= 0)
    {
        // Change gameover to true
        SwitchGameOverState();
        clear_screen();

        draw_string(1, 10, "Game Over!", FG_COLOUR);
        show_screen();
        // Send a message to computer
        usb_serial_send("\n\rGame Over!\n\r");
        GameStatusSerial();

        // Fadeout the LCD from FULL to 0 over a period of time
        for (int i = 1023; i <= 0; i--)
        {
            ChangeBacklightLCD(i);
            _delay_ms(5);
        }

        // Turn on the LEDS
        SET_BIT(PORTB, 2);
        SET_BIT(PORTB, 3);

        // FadeIn the LCD from 0 to FULL over a period of time
        for (int i = 0; i <= 1023; i++)
        {
            ChangeBacklightLCD(i);
            _delay_ms(5);
        }
        _delay_ms(2000);

        // Turn Off the LEDS
        CLEAR_BIT(PORTB, 2);
        CLEAR_BIT(PORTB, 3);

        // Write to screen
        draw_string(1, 20, "To quit press 'q'", FG_COLOUR);
        draw_string(1, 30, "To reset press 'r'", FG_COLOUR);
        show_screen();

        // wait for the user to input if they want to play again of quit.
        while (ReturnGameOver() == true)
        {
            int testInput = usb_serial_getchar();
            KeyboardInput(testInput);
        }
    }
}