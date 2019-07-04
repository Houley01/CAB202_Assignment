/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: main.c               *
*********************************************
*/

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!        NOTE:                                !
!        Depending on which Screen            !
!        Your TeensyPewPew has depends on     !     
!        if you need to comment out           ! 
!        LINE 51 and 54 in screen.c           ! 
!        to see the lcd                       !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
#include "starFighter.h"
#include "spaceObjects.h"
#include "collision.h"
#include "teensyTime.h"
// *****************************

// ********* Deflector Shield *********

void DrawDeflectorShield()
{
    for (int i = 0; i < LCD_X + 1; i += 2)
    {
        draw_pixel(i, 39, FG_COLOUR);
    }
}

// DrawAll: function that is used to draw all the objects to
// the screen that are updated regular.
void DrawAll()
{
    clear_screen();
    DrawSpaceObjects();
    DrawDeflectorShield();
    DrawBullet();
    DrawStarFighter();
    show_screen();
}

// OnceOffSetup: Only need to be setup once, if the function is called
// twice it wipes any sets that have been done before.
void OnceOffSetup()
{
    set_clock_speed(CPU_8MHz);
    SetupTimer();
    SetupTheLCD();
    SerialSetup();
    usb_init();
    adc_init();
    EnableTeensyInput();
}

// setup: Set up all objects in the game.
void setup(void)
{
    Animation();
    SetupGameInformation();
    SetupSpaceObjects();
    SetupStarFighter();
    SetupBullet();
    PlaceAsteroid();
    ResetGameTime();
}

// loop:
void loop()
{
    int16_t charCode = CheckForSerialInput();
    KeyboardInput(charCode);
    if (BIT_IS_SET(PINF, 6) || charCode == 'r') // Switch 1 (Left Button) Start / Restart Game
    {
        setup();
    }
    if (ReturnPause() == false)
    {
        UpdateAsteroid();
        UpdatedStarFighter();
        UpdatedAim();
        UpdatedBullet();
    }
    CheckCollision();  // calls the function check for collision which checks to see if rubbish is in way.
    CheckWaveIsDone(); // Check to see if the wave in finished
    GameOver();
    DrawAll();
}

int main(void)
{
    srand(ReturnLife() + ReturnScore() + ReturnSeconds());
    if (ReturnRunAnimationBool() == true)
    {
        OnceOffSetup();
    }

    setup();
    while (ReturnGameOver() == false)
    {
        loop();
        _delay_ms(50);
    }
    return 0;
}
