/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: GameInformation.c    *
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
#include "animation.h"
#include "serial.h"
#include "teensyTime.h"

// *****************************
bool PAUSED;
bool GAMEOVER;
bool GameStartMessage;
int Score;
int Life;

// ********* Score *********
int ReturnScore()
{
    return Score;
}

void AddToScore(int addPoints)
{
    Score += addPoints;
}

void CheatCustomScore(int userInput)
{
    Score = userInput;
}

// ********* Life *********

int ReturnLife()
{
    return Life;
}

void MinusOneFromLife()
{
    Life--;
}

void CheatCustomLife(int userInput)
{
    Life = userInput;
}

// ********* Pause *********

bool ReturnPause()
{
    return PAUSED;
}

void SwitchPauseState()
{
    PAUSED = !PAUSED;
}

// ********* Game Over *********

bool ReturnGameOver()
{
    return GAMEOVER;
}

void SwitchGameOverState()
{
    GAMEOVER = !GAMEOVER;
}

// ********* Game Start *********

bool ReturnGameStartMessage()
{
    return GameStartMessage;
}

void SetGameStartMessageTrue()
{
    GameStartMessage = true;
}

// ********* Game Infomation Setup *********

void SetupGameInformation()
{
    PAUSED = true;
    GAMEOVER = false;
    GameStartMessage = false;
    Score = 0;
    Life = 5;
}

// ********* Speed *********

double ReturnSpeed()
{
    return ((1023 - adc_read(1)) / 102.3) * 0.1;
}