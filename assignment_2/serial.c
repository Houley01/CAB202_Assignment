/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: serial.c             *
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
// #include "main.h"
#include "screen.h"
#include "controls.h"
#include "serial.h"
#include "animation.h"
#include "gameInformation.h"

// *****************************

void SerialSetup()
{
    // Set Timer 0 to overflow approx 122 times per second.
    TCCR0B |= 4;
    TIMSK0 = 1;

    // Enable interrupts.
    sei();
}

void usb_serial_send(char *message)
{
    // Cast to avoid "error: pointer targets in passing argument 1
    //	of 'usb_serial_write' differ in signedness"
    usb_serial_write((uint8_t *)message, strlen(message));
}

void send_formatted(char *buffer, int buffer_size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, buffer_size, format, args);
    usb_serial_write((uint8_t *)buffer, strlen(buffer));
}

char buffer[81];

int CheckForSerialInput()
{
    int16_t charCode = usb_serial_getchar();
    return charCode;
}
