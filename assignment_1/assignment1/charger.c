/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: charger.h            *
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

int TimeDocked = -1;
bool returnToCharger = false;
int chargingStationHeight = 3, chargingStationWidth = 9;
int chargingStationX, chargingStationY = 5;

// Set the x axis for the charging station based on the screen width
void SetCharingStationX()
{
    chargingStationX = ((screen_width() / 2) - 5);
}

char *chargingStation =
    "#########"
    "#CHARGER#"
    "#########";

// Draws the Charging Station
void DrawCharger()
{
    DrawBitmap(chargingStationX, chargingStationY, chargingStationWidth, chargingStationHeight, chargingStation, true);
}

// Sets the return to charger to false
void SetReturnTOChargerFalse()
{
    returnToCharger = false;
}

// Return back to the charging station after calculating the quickest route
void ReturnToCharger()
{
    // Sets the ReturnToCharger to True
    returnToCharger = true;
    // Set the Vacuum Direction by using math of TAN((y1 - y0)/(x1 - x0))
    // e.g. TAN((chargerY - VacuumY)/(ChargerX - VacuumX))
    // After TAN equaction is done TIME (*) that by 180 then Dived by M_PI
    SetVacuumDirection(atan2(6 - GetVacuumY(), (screen_width() / 2 - (GetChargerWidth() / 2) - 1) - GetVacuumX()) * 180 / M_PI);

    // Calculate the next vacuum X Direction
    SetVacuumDirectionX();
    // Calculate the next vacuum Y Direction
    SetVacuumDirectionY();
}

// Returns the true or false value
bool BoolReturnToChager()
{
    return returnToCharger;
}

// Sets timeDocked to -1
void SetupTimeDocked()
{
    TimeDocked = -1;
}

// Set Varible TimeDocked to the currentTime when being called
void SetTimeDocked()
{
    TimeDocked = get_current_time();
}

// Returns the value for TimeDocked
int GetTimeDocked()
{
    return TimeDocked;
}

// Workout how many seconds have passed sinces TimeDocked was set
int ReturnTimeDocked()
{
    int timeDockSeconds;
    timeDockSeconds = get_current_time() - TimeDocked;
    return timeDockSeconds;
}

// Return the locaction of postion X axis
int GetChargerX()
{
    return chargingStationX;
}

// Return the locaction of postion Y axis
int GetChargerY()
{
    return chargingStationY;
}

// Return the width of the charger
int GetChargerWidth()
{
    return chargingStationWidth;
}

// Return the height of the charger
int GetChargerHeight()
{
    return chargingStationHeight;
}