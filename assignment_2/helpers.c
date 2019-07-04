/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: helpers.c            *
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

// Return the calculation of sin( angle given * PI / 180)
double ReturnSin(int angle)
{
    return sin(angle * M_PI / 180);
}

// Return the calculation of Cos( angle given * PI / 180)
double ReturnCos(int angle)
{
    return cos(angle * M_PI / 180);
}

// Drawing a string which is able to have different types of string included
void draw_formatted(int x, int y, char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 80, format, args);
    draw_string(x, y, buffer, FG_COLOUR);
}