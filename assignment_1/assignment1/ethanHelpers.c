/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: ethanHelpers.c       *
*********************************************
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

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

// Draw bitmap used from drawing objects.
void DrawBitmap(int left, int top, int width, int height, char bitmap[], bool space_is_transparent)
{
    for (int j = 0; j <= (height - 1); j++)
    {
        for (int i = 0; i <= (width - 1); i++)
        {
            if (bitmap[i + j * width] != ' ')
            {
                draw_char(left + i, top + j, bitmap[i + j * width]);
            }
            else if (space_is_transparent == false)
            {
                draw_char(left + i, top + j, ' ');
            }
        }
    }
}

/* Time related functions and vaibles  \/ */
double start_time;
int TIMEOUT = INT_MAX;
int DELAY = 50;

// Sets Start time and returns the value
double GetstartTime()
{
    start_time = get_current_time();
    return start_time;
}

// How much time has passed scince reset
double TimeSinceReset()
{
    double timeCounter = get_current_time() - start_time;
    return timeCounter;
}

// Returns the start time of the simiulation
double ReturnStartTime()
{
    return start_time;
}

// Return the number of minutes the simiulation has been running for.
int ReturnTimeMinutes()
{
    return TimeSinceReset() / 60;
}
// Return the number of seconds the simiulation has been running for.
int ReturnTimeSeconds()
{
    return fmod(TimeSinceReset(), 60.00);
}

// Gets the user input for how do they want the simiulation to run for.
double SetTimeOut()
{
    TIMEOUT = get_int("Set the time out in seconds:");
    return TIMEOUT;
}

// Timeout bool (return a true or false) based on if the program has run for more then the allowed time
bool TimeOut()
{
    if (get_current_time() - ReturnStartTime() >= TIMEOUT)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Sets the delay between each loop at the start of the program
void SetDelayAtStart()
{
    DELAY = 50;
}

// Gets the user input for how do they want the delay to be
void SetDelay()
{
    int tempDELAY = 0;
    tempDELAY = get_int("How long do you want the New Delay to be in milliseconds (NO LESS THEN 1 MILLISECONDS)?");
    if (tempDELAY <= 0)
    {
        DELAY = 1;
    }
    else
    {
        DELAY = tempDELAY;
    }
}

// Returns the value of DELAY
int ReturnDelay()
{
    return DELAY;
}

// Switch between robot being paused and not paused.
bool PAUSED = true;
// Switchs between paused been true and false.
// If PAUSED = true, it will change it to false.
// If PAUSED = false, it will change it to true.
void Pause()
{
    PAUSED = !PAUSED;
}

// Set Paused to true at the start of the simulation
void SetPausedToTrue()
{
    PAUSED = true;
    SetTimeDocked();
}

// Returns the bool value of PAUSED
bool ReturnPaused()
{
    return PAUSED;
}

// Giant if statment for charcodes to see if a cheat key has been entered
void CheatCodes(int ch)
{
    if (ch == 'b') // Return to charger
    {
        ReturnToCharger();
    }
    else if (ch == 'd' || ch == 'D' || ch == 's' || ch == 'S' || ch == 't' || ch == 'T') // Drops dust ( Small Rubbish)
    {
        DropRubish(ch);
    }
    else if (ch == 'm') /* change milliseconds delay bettween loops */
    {
        SetDelay();
    }

    else if (ch == 'o') // Change the time allow for the program runs for
    {
        SetTimeOut();
    }

    else if (ch == 'p') // start or stop the robot moving
    {
        Pause();
    }

    else if (ch == 'q') // Quit simulation
    {
        Quit();
    }

    else if (ch == 'v') // Move Robot to x and y location
    {
        MoveVacuumToXYZ();
    }
    else if (ch == 'j' || ch == 'J' || ch == 'l' || ch == 'L' || ch == 'k' || ch == 'K' || ch == 'i' || ch == 'I')
    {
        ControlVacuum(ch);
    }
    else if (ch == 'w') // Change Current load of rubish on the vacuum
    {
        SetWeight();
    }
    else if (ch == 'y') // Set new battery Level
    {
        ChangeBatteryLevel();
    }
    else if (ch == '?') // Set new battery Level
    {
        HelpScreen();
    }
} // End of cheat buttons