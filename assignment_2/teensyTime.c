/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: teensyTime.c         *
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
#define FREQ 8000000.0
#define PRESCALE 256.0
#define TIMER_SCALE 256.0

double interval = 0;
uint32_t cycleCount;

ISR(TIMER0_OVF_vect)
{
    interval += TIMER_SCALE * PRESCALE / FREQ;
}

ISR(TIMER3_OVF_vect)
{
    cycleCount++;
}

void SetupTimer()
{
    // Timer 3
    TCCR3A = 0;
    TCCR3B = 2;
    TIMSK3 = 1;
}

double ReturnCycleCountTime()
{
    return (cycleCount * 65536.0 + TCNT3) * 8.0 / FREQ;
}

int ReturnSeconds()
{
    return fmod(ReturnCycleCountTime(), 60.0);
}

int ReturnMinutes()
{
    return floor(ReturnCycleCountTime() / 60);
}

void ResetGameTime()
{
    cycleCount = 0;
}