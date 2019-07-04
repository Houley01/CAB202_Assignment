/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: spaceObjects.c       *
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
#include "starFighter.h"
#include "helpers.h"
#include "collision.h"

// ********* Possible Point *********
#define scorePointAseroid 1
#define scorePointBoulder 2
#define scorePointFragement 4

// ********* Asteroid *********

#define asteroid_size 7
#define max_asteroid 3
double asteroidLocation[max_asteroid][3];

static uint8_t asteroidPixelMap[7] =
    {
        0b0001000, // 1
        0b0011100, // 2
        0b0111110, // 3
        0b1111111, // 4
        0b0111110, // 5
        0b0011100, // 6
        0b0001000  // 7
};

// DrawAsteroid: Goes though bit array to draw the asteroid at
// given X and Y coordinates
void DrawAsteroid(int i)
{
    for (int row = 0; row < 7; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(asteroidPixelMap[row], (column)) == 1)
            {
                draw_pixel(asteroidLocation[i][0] + column, asteroidLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

int ReturnAsteroidLocationX(int i)
{
    return asteroidLocation[i][0];
}

int ReturnAsteroidLocationY(int i)
{
    return asteroidLocation[i][1];
}

// ReturnNumOfAsteroids: Counts the number of astroids are on the
// screen, or about to move on to the screen.
int ReturnNumOfAsteroids()
{
    int count = 0;
    for (int i = 0; i < max_asteroid; i++)
    {
        if (asteroidLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_asteroid - count;
}

// ********* Boulder *********
#define boulder_size 5
#define max_boulder 6
// Max number of boulder is 6
int boulderLocation[max_boulder][3];

int boulderPixelMap[5] = {
    0b0001000,  // 1
    0b0011100,  // 2
    0b0111110,  // 3
    0b0011100,  // 4
    0b0001000}; // 5

// DrawBoulder: Goes though bit array to draw the boulder at
// given X and Y coordinates
void DrawBoulder(int i)
{
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(boulderPixelMap[row], (column)) == 1)
            {
                draw_pixel(boulderLocation[i][0] + column, boulderLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

// ReturnNumOfBoulders: Counts the number of boulder are on the screen,
// or about to move on to the screen.
int ReturnNumOfBoulders()
{
    int count = 0;
    for (int i = 0; i < max_boulder; i++)
    {
        if (boulderLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_boulder - count;
}

int ReturnBoulderLocationX(int i)
{
    return boulderLocation[i][0];
}

int ReturnBoulderLocationY(int i)
{
    return boulderLocation[i][1];
}

// ********* Fragment *********
// Max number of fragment is 12
#define fragment_size 3
#define max_fragments 12

int fragmentLocation[max_fragments][2];

int fragmentPixelMap[3] =
    {
        0b0001000,
        0b0011100,
        0b0001000};

// DrawBoulder: Goes though bit array to draw the fragment at
// given X and Y coordinates
void DrawFragment(int i)
{
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(fragmentPixelMap[row], (column)) == 1)
            {
                draw_pixel(fragmentLocation[i][0] + column, fragmentLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

// ReturnNumOfFragments: Counts the number of fragments are on the screen, or about to move on to the screen.
int ReturnNumOfFragments()
{
    int count = 0;
    for (int i = 0; i < max_fragments; i++)
    {
        if (fragmentLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_fragments - count;
}

int ReturnFragmentLocationX(int i)
{
    return fragmentLocation[i][0];
}

int ReturnFragmentLocationY(int i)
{
    return fragmentLocation[i][1];
}

// ********* Placement *********
// PlaceAsteroid: Place 3 asteroids at a random x postion on lcd when a new wave is coming.
void PlaceAsteroid()
{
    for (int i = 0; i < 3; i++)
    {
        asteroidLocation[i][0] = rand() % (LCD_X - 1 - asteroid_size);
        asteroidLocation[i][1] = -10;
    }
}

// ********* Master Call *********
// UpdateAsteroid: Updates the current positon of the space object to move down the screen.
void UpdateAsteroid()
{
    for (int i = 0; i < 3; i++)
    {
        asteroidLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        asteroidLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
    for (int i = 0; i < max_boulder; i++)
    {
        boulderLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        boulderLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
    for (int i = 0; i < max_fragments; i++)
    {
        fragmentLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        fragmentLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
}

// SetupSpaceObjects: places all the objects of the screen when the game is first started.
void SetupSpaceObjects()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        asteroidLocation[i][0] = -LCD_X;
        asteroidLocation[i][1] = -LCD_Y;
        asteroidLocation[i][2] = 0;
    }
    for (int i = 0; i < max_boulder; i++)
    {
        boulderLocation[i][0] = -LCD_X;
        boulderLocation[i][1] = -LCD_Y;
        boulderLocation[i][2] = 0;
    }
    for (int i = 0; i < max_fragments; i++)
    {
        fragmentLocation[i][0] = -LCD_X;
        fragmentLocation[i][1] = -LCD_Y;
        fragmentLocation[i][2] = 0;
    }
}
// DrawSpaceObjects: loops through each of the space objects and draws them to the Teensy PewPew
void DrawSpaceObjects()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        DrawAsteroid(i);
    }
    for (int i = 0; i < max_boulder; i++)
    {
        DrawBoulder(i);
    }
    for (int i = 0; i < max_fragments; i++)
    {
        DrawFragment(i);
    }
}

// ********* Spilting of SpaceObjects *********

// void SpawnChild(int x, int y, int angle, int object)
// {
//     int findChild = 0;
//     if (object == 0)
//     {
//         // find 2 free child
//         for (int boulder = 0; boulder < max_boulder; boulder++)
//         {
//             if (boulderLocation[boulder][0] < 0)
//             {
//                 if (findChild == 0)
//                 {
//                     boulderLocation[boulder][0] = x - boulder_size;
//                     boulderLocation[boulder][1] = y;
//                     boulderLocation[boulder][2] = ((angle + 30) + 360) % 360;
//                     findChild++;
//                 }
//                 else if (findChild == 1)
//                 {
//                     boulderLocation[boulder][0] = x + boulder_size;
//                     boulderLocation[boulder][1] = y;
//                     boulderLocation[boulder][2] = ((angle - 30) + 360) % 360;
//                     break;
//                 }
//             }
//         }
//     }
//     if (object == 1)
//     {
//         // find 2 free child
//         for (int fragment = 0; fragment < max_fragments; fragment++)
//         {
//             if (fragmentLocation[fragment][0] < 0)
//             {
//                 if (findChild == 0)
//                 {
//                     fragmentLocation[fragment][0] = x - 5;
//                     fragmentLocation[fragment][1] = y;
//                     fragmentLocation[fragment][2] = ((angle + 30) + 360) % 360;
//                     findChild++;
//                     // break;
//                 }
//                 else if (findChild == 1)
//                 {
//                     fragmentLocation[fragment][0] = x + 5;
//                     fragmentLocation[fragment][1] = y;
//                     fragmentLocation[fragment][2] = ((angle - 30) + 360) % 360;
//                     break;
//                 }
//             }
//         }
//     }
// }

void SpawnBoulder(int asteriodNumber)
{
    if (asteriodNumber == 0)
    {
        /* Set the angle */
        // boulder 0
        boulderLocation[0][0] = asteroidLocation[0][0];
        boulderLocation[0][1] = asteroidLocation[0][1];
        // boulder 1
        boulderLocation[1][0] = asteroidLocation[0][0];
        boulderLocation[1][1] = asteroidLocation[0][1];
    }
    else if (asteriodNumber == 1)
    {
        // boulder 2
        boulderLocation[2][0] = asteroidLocation[1][0];
        boulderLocation[2][1] = asteroidLocation[1][1];
        // boulder 3
        boulderLocation[3][0] = asteroidLocation[1][0];
        boulderLocation[3][1] = asteroidLocation[1][1];
    }
    else if (asteriodNumber == 2)
    {
        // boulder 4
        boulderLocation[4][0] = asteroidLocation[2][0];
        boulderLocation[4][1] = asteroidLocation[2][1];
        // boulder 5
        boulderLocation[5][0] = asteroidLocation[2][0];
        boulderLocation[5][1] = asteroidLocation[2][1];
    }
}

void SpawnFragment(int BoulderNumber)
{
    if (BoulderNumber == 0)
    {
        /* Set the angle */
        // fragment 0
        fragmentLocation[0][0] = boulderLocation[0][0];
        fragmentLocation[0][1] = boulderLocation[0][1];
        // fragment 1
        fragmentLocation[1][0] = boulderLocation[0][0];
        fragmentLocation[1][1] = boulderLocation[0][1];
    }
    else if (BoulderNumber == 1)
    {
        // fragment 2
        fragmentLocation[2][0] = boulderLocation[2][0];
        fragmentLocation[2][1] = boulderLocation[2][1];
        // fragment 3
        fragmentLocation[3][0] = boulderLocation[1][0];
        fragmentLocation[3][1] = boulderLocation[1][1];
    }
    else if (BoulderNumber == 2)
    {
        // fragment 4
        fragmentLocation[4][0] = boulderLocation[1][0];
        fragmentLocation[4][1] = boulderLocation[1][1];
        // fragment 5
        fragmentLocation[5][0] = boulderLocation[2][0];
        fragmentLocation[5][1] = boulderLocation[2][1];
    }
    else if (BoulderNumber == 3)
    {
        // fragment 6
        fragmentLocation[6][0] = boulderLocation[1][0];
        fragmentLocation[6][1] = boulderLocation[1][1];
        // fragment 7
        fragmentLocation[7][0] = boulderLocation[2][0];
        fragmentLocation[7][1] = boulderLocation[2][1];
    }
    else if (BoulderNumber == 4)
    {
        // fragment 8
        fragmentLocation[8][0] = boulderLocation[4][0];
        fragmentLocation[8][1] = boulderLocation[4][1];
        // fragment 9
        fragmentLocation[9][0] = boulderLocation[4][0];
        fragmentLocation[9][1] = boulderLocation[4][1];
    }
    else if (BoulderNumber == 5)
    {
        // fragment 10
        fragmentLocation[10][0] = boulderLocation[5][0];
        fragmentLocation[10][1] = boulderLocation[5][1];
        // fragment 11
        fragmentLocation[11][0] = boulderLocation[5][0];
        fragmentLocation[11][1] = boulderLocation[5][1];
    }
}

void SpawnChild(char firstLetter, int objectNumber)
{
    if (firstLetter == 'a')
    {
        SpawnBoulder(objectNumber);
    }
    else if (firstLetter == 'b')
    {
        SpawnFragment(objectNumber);
    }
}

// ********* Warrning Lights  *********
// WarrningLights: Alerts the user that a new wave is coming and which side will have
// more astroids come down.
void WarrningLights()
{
    int countLeft = 0, countRight = 0;
    for (int i = 0; i < max_asteroid; i++)
    {
        // Round the location down to the nearest int and check if it Less than the LCD_X / 2
        if (floor(ReturnAsteroidLocationX(i) + (asteroid_size / 2)) < (LCD_X / 2))
        {
            countLeft++;
        }
        // Round the location down to the nearest int and check if it great than the LCD_X / 2
        else if (floor(ReturnAsteroidLocationX(i) + (asteroid_size / 2)) > (LCD_X / 2))
        {
            countRight++;
        }
    }
    if (countLeft > countRight)
    {
        SET_BIT(PORTB, 2);
        CLEAR_BIT(PORTB, 2);
    }
    else if (countRight > countLeft)
    {
        SET_BIT(PORTB, 3);
    }
    _delay_ms(100);
    CLEAR_BIT(PORTB, 2);
    CLEAR_BIT(PORTB, 3);
}

// ********* Checking Collison *********

// CheckforSheild: Loop thought space object and check if any spaceobjects are touching the sheild.
// if space obect is touching remove 1 life
void CheckforSheild()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        if ((floor(asteroidLocation[i][0]) >= 0 && floor(asteroidLocation[i][0]) <= LCD_X) && floor(asteroidLocation[i][1] + asteroid_size - 1) >= 39)
        {
            asteroidLocation[i][0] = -10;
            asteroidLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
    for (int i = 0; i < max_boulder; i++)
    {
        if ((floor(boulderLocation[i][0]) >= 0 && floor(boulderLocation[i][0]) <= LCD_X) && floor(boulderLocation[i][1] + boulder_size - 1) >= 39)
        {
            boulderLocation[i][0] = -10;
            boulderLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
    for (int i = 0; i < max_asteroid; i++)
    {
        if ((floor(fragmentLocation[i][0]) >= 0 && floor(fragmentLocation[i][0]) <= LCD_X) && floor(fragmentLocation[i][1] + fragment_size - 1) >= 39)
        {
            fragmentLocation[i][0] = -10;
            fragmentLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
}

uint8_t bullet[2] = {
    0b0011000,
    0b0011000};

// CheckForBullet: Loop thought space object and check if any of space objects are touching a bullet.
// and if space obect is touching a bullet add points to the score
void CheckForBullet()
{
    // Loop through 25 times
    for (int bulletArray = 0; bulletArray < 25; bulletArray++)
    {
        // Only check if the bullet is on the screen.
        if (floor(ReturnBulletLocationY(bulletArray)) > 0 &&
            floor(ReturnBulletLocationX(bulletArray)) > 0 &&
            floor(ReturnBulletLocationX(bulletArray)) < LCD_X)
        {
            for (int asteroid = 0; asteroid < max_asteroid; asteroid++)
            {
                // If the bullet is in the same box area as asteroid then check if the pixels are over laping
                if (BoundingBox(ReturnAsteroidLocationX(asteroid), ReturnAsteroidLocationY(asteroid), asteroid_size, asteroid_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the asteroid and add points to the score.
                    if (PixelCollision(ReturnAsteroidLocationX(asteroid), ReturnAsteroidLocationY(asteroid), asteroid_size, asteroid_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        // Replace the Asteroid with 2 Boulder
                        // SpawnChild(asteroidLocation[asteroid][0], asteroidLocation[asteroid][1], asteroidLocation[asteroid][2], 0);
                        SpawnChild('a', asteroid);
                        asteroidLocation[asteroid][0] = -10;
                        asteroidLocation[asteroid][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointAseroid);
                    }
                }
            }
            for (int boulder = 0; boulder < max_boulder; boulder++)
            {
                // If the bullet is in the same box area as boulder then check if the pixels are over laping
                if (BoundingBox(ReturnBoulderLocationX(boulder), ReturnBoulderLocationY(boulder), boulder_size, boulder_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the boulder and add points to the score.
                    if (PixelCollision(ReturnBoulderLocationX(boulder), ReturnBoulderLocationY(boulder), boulder_size, boulder_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        // Replace the Boulder with 2 Fragment
                        // SpawnChild(boulderLocation[boulder][0], boulderLocation[boulder][1], boulderLocation[boulder][2], 1);
                        SpawnChild('b', boulder);
                        boulderLocation[boulder][0] = -10;
                        boulderLocation[boulder][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointBoulder);
                    }
                }
            }
            for (int fragment = 0; fragment < max_fragments; fragment++)
            {
                // If the bullet is in the same box area as fragnent then check if the pixels are over laping
                if (BoundingBox(ReturnFragmentLocationX(fragment), ReturnFragmentLocationY(fragment), fragment_size, fragment_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the boulder and add points to the score.
                    if (PixelCollision(ReturnFragmentLocationX(fragment), ReturnFragmentLocationY(fragment), fragment_size, fragment_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        fragmentLocation[fragment][0] = -10;
                        fragmentLocation[fragment][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointFragement);
                    }
                }
            }
        }
    }
}

// CheckCollision: Master function to call any functions which have anything
// to do with collision dections
void CheckCollision()
{
    CheckforSheild();
    CheckForBullet();
}

// Spawn a new wave if all space objects are off the screen.
void CheckWaveIsDone()
{
    if (
        ReturnNumOfAsteroids() == 0 &&
        ReturnNumOfBoulders() == 0 &&
        ReturnNumOfFragments() == 0)
    {
        PlaceAsteroid();
        WarrningLights();
    }
}