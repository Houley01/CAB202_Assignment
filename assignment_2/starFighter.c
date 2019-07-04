/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: starFighter.c        *
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
#include "helpers.h"
#include "teensyTime.h"

// ****************************
#define starFighterWidth 9
#define starFighterHeight 7
int starFighterDirection;

// ********* Star Fighter *********

int starFighterX, starFighterY;

static uint8_t starFighterPixelMap[7] = {
    0b0001000, // 1
    0b1001001, // 2
    0b1001001, // 3
    0b1011101, // 4
    0b1111111, // 5
    0b1011101, // 6
    0b1000001, // 7
};

// DrawStarFighter: Goes though bit array to draw the StarFighter at
// given X and Y coordinates
void DrawStarFighter()
{
    for (int row = 0; row < 7; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(starFighterPixelMap[row], (column)) == 1)
            {
                draw_pixel(starFighterX + column, starFighterY + row, FG_COLOUR);
            }
        }
    }
}

// SetupStarFighter: Set the StarFighter at the start of the game
void SetupStarFighter()
{
    starFighterX = LCD_X / 2 - 5;
    starFighterY = LCD_Y - 7;
    starFighterDirection = 0;
}

// ChangeStarFighterDirection: Checks to see if the input from the computer or teensy match a movement.
void ChangeStarFighterDirection(char userInput)
{
    // -1 equal to left, 0 equal to stop, 1 equal to right

    // Checks to see if the starfiger is is not moving then change the direction to move left
    if ((BIT_IS_SET(PINB, 1) || userInput == 'a') && starFighterDirection == 0)
    {
        starFighterDirection = -1;
    }
    // Checks to see if the starfiger is is not moving then change the direction move right
    else if ((BIT_IS_SET(PIND, 0) || userInput == 'd') && starFighterDirection == 0)
    {
        starFighterDirection = 1;
    }
    // If the starfighter is motion stop it
    else if (((BIT_IS_SET(PINB, 1) || userInput == 'a') && starFighterDirection == 1) ||
             ((BIT_IS_SET(PIND, 0) || userInput == 'd') && starFighterDirection == -1))
    {
        starFighterDirection = 0;
    }
    if (starFighterX + 1 >= LCD_X - starFighterWidth)
    {
        starFighterDirection = 0;
        starFighterX--;
    }
    if (starFighterX - 1 <= 0)
    {
        starFighterDirection = 0;
        starFighterX++;
    }
}

// UpdatedStarFighter: Check to see if the starFighterDirection equal to
// a value if so move in the direction
void UpdatedStarFighter()
{
    ChangeStarFighterDirection(0);
    if (starFighterDirection == -1)
    {
        starFighterX--;
    }
    else if (starFighterDirection == 1)
    {
        starFighterX++;
    }
}

int ReturnStarFighterDirection()
{
    return starFighterDirection;
}

int ReturnStarFighterX()
{
    return starFighterX;
}

int ReturnStarFighterY()
{
    return starFighterY;
}

// ********************************

#define max_bullet 20

uint8_t bulletPixelMap[2] = {
    0b0011000,
    0b0011000};

double bulletLocation[max_bullet][3];
long aimReader;

// UpdatedAim: Reads the left thumbwheel and produce and angle for which way
// the bullets fire from -60 to +60
void UpdatedAim()
{
    // 8.525 x 120 = 1023
    aimReader = (adc_read(0) / 8.525);
    if (aimReader >= 61) // Left
    {
        aimReader = aimReader % 61;
    }
    else if (aimReader <= 60) // Right
    {
        aimReader = -60 - (-aimReader % 61);
    }
}

int ReturnAim()
{
    return aimReader;
}

// SetupBullet: sets the bullets up so that all the bullets are off screen
// at the start of the game
void SetupBullet()
{
    for (int row = 0; row < max_bullet; row++)
    {
        for (int i = 0; i < 3; i++)
        {
            bulletLocation[row][i] = -10;
        }
    }
}

// DrawBullet: Loop though array and draw the bullets to the lcd
void DrawBullet()
{
    for (int i = 0; i < max_bullet; i++)
    {
        for (int row = 0; row < 2; row++)
        {
            for (int column = 0; column < 7; column++)
            {
                if (BIT_VALUE(bulletPixelMap[row], (column)) == 1)
                {
                    draw_pixel(bulletLocation[i][0] + column, bulletLocation[i][1] + row, FG_COLOUR);
                }
            }
        }
    }
}

// NumberOfBullets: Return the number of bullets are on screen.
int NumberOfBullets()
{
    int NumberOfBullets = 0;
    for (int i = 0; i < max_bullet; i++)
    {
        if (bulletLocation[i][1] <= 0)
        {
            NumberOfBullets++;
        }
    }
    return NumberOfBullets = max_bullet - NumberOfBullets;
}

// FirePlasmaGun: If joystick up or 'w' is press fire a bullet, set the x and y at the starfighter
void FirePlasmaGun()
{
    double lastFired = 0;
    for (int i = 0; i < max_bullet; i++)
    {
        // Go through the array and end the loop after finding a
        // location where the bullet is off screen.

        if ((bulletLocation[i][1] < 0 || bulletLocation[i][0] < 0 || bulletLocation[i][0] > LCD_X) && ReturnCycleCountTime() > lastFired)
        {
            bulletLocation[i][0] = starFighterX;
            bulletLocation[i][1] = starFighterY;
            bulletLocation[i][2] = (360 + aimReader) % 360;
            lastFired = ReturnCycleCountTime() + 100;
            break;
        }
    }
}

// UpdatedBullet: Calculate each movement the bullet makes on screen.
void UpdatedBullet()
{
    for (int i = 0; i < max_bullet; i++)
    {
        // bullet location = bulletLocation - (speed * SIN/COS( angle * PI / 180))
        bulletLocation[i][0] -= 0.8 * ReturnSin(bulletLocation[i][2]); // X
        bulletLocation[i][1] -= 0.8 * ReturnCos(bulletLocation[i][2]); // Y
    }
}

double ReturnBulletLocationX(int i)
{
    return bulletLocation[i][0];
}

double ReturnBulletLocationY(int i)
{
    return bulletLocation[i][1];
}

void SetBulletLocationX(int i, int set)
{
    bulletLocation[i][0] = set;
}

void SetBulletLocationY(int i, int set)
{
    bulletLocation[i][1] = set;
}