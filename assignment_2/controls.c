/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: controls.c           *
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
#include "gameInformation.h"
#include "animation.h"
#include "screen.h"
#include "starFighter.h"
#include "spaceObjects.h"

// Joystick controls
void SetupFiveWayJoystick()
{
    CLEAR_BIT(DDRD, 1); // Switch C (UP): Fire plasma Gun
    CLEAR_BIT(DDRB, 1); // Switch B (LEFT): Move Left
    CLEAR_BIT(DDRD, 0); // Switch D (Right): Move Right
    CLEAR_BIT(DDRB, 7); // Switch A (DOWN): Move
    CLEAR_BIT(DDRB, 0); // Switch Center: Pause
}

void SetupTactileSwitch()
{
    // Tactlie Buttons
    CLEAR_BIT(DDRF, 6); // Switch 1
    CLEAR_BIT(DDRF, 5); // Switch 2
}

void setLEDs()
{
    SET_BIT(DDRB, 2);
    SET_BIT(DDRB, 3);
}

#define BIT(x) (1 << (x))
// Enable the reading of the thumbwheel
void SetupPWM()
{
    TC4H = 1023 >> 8;
    OCR4C = 1023 & 0xff;
    TCCR4A = BIT(COM4A1) | BIT(PWM4A);
    SET_BIT(DDRC, 7);
    TCCR4B = BIT(CS42) | BIT(CS41) | BIT(CS40);

    TCCR4D = 0;
}

// Calls all the functions to enable inputs and
// output on the teensy PewPew
void EnableTeensyInput()
{
    SetupFiveWayJoystick();
    SetupTactileSwitch();
    setLEDs();
    SetupPWM();
}

// Checks to see what inputs has been give to the teensy
// input from TeensyPewPew or through serial.
void KeyboardInput(int charCode)
{
    // If 'a' or 'd' are pased then change the direction
    ChangeStarFighterDirection(charCode);

    if (charCode == 'w' || BIT_IS_SET(PIND, 1)) // Fire Plasma Bolts
    {
        FirePlasmaGun();
    }
    if (charCode == 's' || BIT_IS_SET(PINB, 7)) // Show status
    {
        StatusDisplay();
    }
    if (charCode == 'r' || BIT_IS_SET(PINF, 6)) // Start Game Or Restart
    {
        SetFalseRunanimation();
        SwitchGameOverState();
        GameStatusSerial();
        SetupGameInformation();
    }
    if (charCode == 'p' || BIT_IS_SET(PINB, 0)) // Change Pause stats
    {
        SwitchPauseState();
        SetGameStartMessageTrue();
    }
    if (charCode == 'q' || BIT_IS_SET(PINF, 5)) // Quit
    {
        Quit();
    }
    if (charCode == 't') // Aim The Plasma Gun
    {
        // Have not attemped
    }
    if (charCode == 'm') // Set the speed of the game
    {
        // Have not attemped
    }
    if (charCode == 'l') // Set Number of Lifes
    {
        // Have not attemped
        // CheatCustomLife(userInput)
    }
    if (charCode == 'g') // Set Game Score
    {
        // Have not attemped
        // CheatCustomScore(userInput)
    }
    if (charCode == '?') // Print controls to PC
    {
        HelpScreen();
    }
    if (charCode == 'h') // Move the starfighter to X
    {
        // Have not attemped
    }
    if (charCode == 'j') // Place An Asteriod
    {
        // Have not attemped
    }
    if (charCode == 'k') // Place A Boulder
    {
        // Have not attemped
    }
    if (charCode == 'i') // Place A Fragment
    {
        // Have not attemped
    }
}