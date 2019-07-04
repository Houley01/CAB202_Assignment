/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: collision.c          *
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
#include "spaceObjects.h"
// Bounding Box check to see if objects a is are overlaping object b
bool BoundingBox(
    double x0, double y0, int w0, int h0,
    double x1, double y1, int w1, int h1)
{
    int left0 = round(x0) - w0 / 2, right0 = left0 + w0 - 1;
    int left1 = round(x1) - w1 / 2, right1 = left1 + w1 - 1;

    int top0 = round(y0) - h0 / 2, bottom0 = top0 + h0 - 1;
    int top1 = round(y1) - h1 / 2, bottom1 = top1 + h1 - 1;

    if (right1 < left0 || right0 < left1)
    {
        return false;
    }
    if (bottom1 < top0 || bottom0 < top1)
    {
        return false;
    }

    return true;
}

// Pixel Level Collision checks to see if any pixel that is a 1 is overlaping with another pixel that is also 1
bool PixelCollision(int x0, int y0, int w0, int h0, uint8_t pixel0[], int x1, int y1, int w1, int h1, uint8_t pixel1[])
{
    for (int x = 0; x < (x0 + w0); x++) // X axie
    {
        for (int y = 0; y < (y0 + h0); y++) // y axie
        {

            if (x >= x0 && x < (x0 + w0) && y >= y0 && y < (y0 + h0) && pixel0[(x - x0) + (y - y0) * w0] != 0 &&
                x >= x1 && x < (x1 + w1) && y >= y1 && y < (y1 + h1) && pixel1[(x - x1) + (y - y1) * w1] != 0)
            {
                return true;
            }
        }
    }
    return false;
}