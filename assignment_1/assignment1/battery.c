/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: battery.c            *
*********************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// *********** CAB202 ***********

#include "cab202_timers.h"
#include "cab202_graphics.h"
#include "helpers.h"

// *****************************

// *********** Ethan ***********
#include "battery.h"
#include "charger.h"
#include "collision.h"
#include "ethanHelpers.h"
#include "screenLayout.h"
#include "trash.h"
#include "vacuum.h"

// *****************************

int batteryCharge, timer;

int BatteryLevel()
{
    // if TimeDocked = -1 then the battery discharges based on when the simulation started
    if (GetTimeDocked() == -1)
    {
        batteryCharge = 100 - fmod(TimeSinceReset(), 101);
    }
    // If TimeDocked is not equal to -1 (!= -1) then use the time from when the vacuum cleaner lasted docked.
    if (GetTimeDocked() != -1)
    {
        batteryCharge = 100 - fmod(ReturnTimeDocked(), 101);
    }
    //  if the battery % is less then ZERO (0) then display a message
    if (batteryCharge <= 0)
    {
        BatteryFlatMessageTrue();
    }
    //  if the battery falls below 25% then the vacuum cleanner will try to make its way home
    if (batteryCharge < 25)
    {
        // Return back to the charging station
        ReturnToCharger();
    }
    return batteryCharge;
}

// Tells the program is the battery % has reached 0.
bool boolBatteryFlatMessage = false;

// Set the bool to true
void BatteryFlatMessageTrue()
{
    boolBatteryFlatMessage = true;
}

// Set the bool to false
void BatteryFlatMessageFalse()
{
    boolBatteryFlatMessage = false;
}
// Return the bool saying if the statement is true or false
bool ReturnBatteryFlatMessage()
{
    return boolBatteryFlatMessage;
}

// Currently the battery Level does not change
void ChangeBatteryLevel()
{
    draw_formatted(screen_width() / 2 - 12, screen_height() - 2, "This feature was not done");
    show_screen();
    while (1)
    {
        if (wait_char())
        {
            break;
        }
    }

    get_int("Set the battery level 0 - 100");
}
