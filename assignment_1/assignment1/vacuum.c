/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: vacuum.c             *
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

#define vacuum_width 9
#define vacuum_height 9
#define vacuum_speed 0.2 // Speed should be set to 0.2 in production
int weight;

static double vacuumX, vacuumY, vacuumDirectionX, vacuumDirectionY, vacuumDirection;

char *vacuum =
    "   @@@   "
    "  @@@@@  "
    " @@@@@@@ "
    "@@@@@@@@@"
    "@@@VAC@@@"
    "@@@@@@@@@"
    " @@@@@@@ "
    "  @@@@@  "
    "   @@@   ";

// Draw the Vacuum cleanner at a given X and Y coordinates
void DrawVacuum()
{
    DrawBitmap(vacuumX, vacuumY, vacuum_width, vacuum_height, vacuum, true);
}

// ****************************************************************

// *********************** Direction ******************************

// Randomly generate an angle when the vacuum cleaner runs into a obstacle like charger or walls
int PickAngle()
{
    int angle;
    angle = (rand() % (60 - 30 + 1)) + 30;
    // Turn Left
    if (angle >= 45)
        angle = -angle;
    else /*Turn Right */
    {
        angle = angle;
    }
    return angle;
}

// Calculate the X direction with the angle using MATH equation COS
double VacuumDirectionXCalc(int angle)
{
    vacuumDirectionX = vacuum_speed * cos(angle * M_PI / 180);
    return vacuumDirectionX;
}

// Calculate the Y direction with the angle using MATH equation SIN
double VacuumDirectionYCalc(int angle)
{
    vacuumDirectionY = vacuum_speed * sin(angle * M_PI / 180);
    return vacuumDirectionY;
}

// master function which hides all the MATHS functions when the vacuum cleanner hits the wall. The function call PickAnglem VacuumDirectionYCalc And VacuumDirectionXCalc with setting the vacuum Direction and vacuumDirectionX, vacuumDirectionY

void PickANewDirection()
{
    int angle = PickAngle();
    vacuumDirection = vacuumDirection + angle;
    vacuumDirectionY = VacuumDirectionYCalc(vacuumDirection);
    vacuumDirectionX = VacuumDirectionXCalc(vacuumDirection);
}

int GetVacuumDirection()
{
    double vacuumDirectionMod;
    vacuumDirection = vacuumDirection + 360;
    vacuumDirectionMod = fmod(vacuumDirection, 360);
    return vacuumDirectionMod;
}

// Return the value of vacuumDirection.
double GetVacuumDirectionPreScreen()
{
    return vacuumDirection;
}

// Set the vacuum Direction when the user use the cheat MoveVacuumToXYZ()
void SetVacuumDirection(int value)
{
    vacuumDirection = value;
}

// Calculate the X Direction based on the angle give when the user use the cheat MoveVacuumToXYZ() to move the X Y and direction
void SetVacuumDirectionX()
{
    vacuumDirectionX = VacuumDirectionXCalc(vacuumDirection); // Call the calculation function for X axis With the sum of 'vacuum_speed * cos(angle * M_PI / 180)'
}

// Calculate the Y Direction based on the angle give when the user use the cheat MoveVacuumToXYZ() to move the X Y and direction
void SetVacuumDirectionY()
{
    vacuumDirectionY = VacuumDirectionYCalc(vacuumDirection); // Call the calculation function for Y axis With the sum of 'vacuum_speed * sin(angle * M_PI / 180)'
}

// ****************************************************************

// ************************* Vacuum *******************************

// Setup the Vacuum variables when the program first runs
void SetupVacuum()
{
    int width, height;
    get_screen_size(&width, &height);
    vacuumX = (width / 2) - 5;
    vacuumY = (height / 2) - 5;
    vacuumDirection = 90;
    vacuumDirectionX = VacuumDirectionXCalc(vacuumDirection);
    vacuumDirectionY = VacuumDirectionYCalc(vacuumDirection);
}

// Checks if the new location for the vacuum cleaner will collide with a wall or charger.
void UpdatedVacuum()
{
    int new_x = round(vacuumX + vacuumDirectionX);
    int new_y = round(vacuumY + vacuumDirectionY);

    bool bounced = false;

    // Check to see if it has hit horzontal wall
    if (new_x == 1 || new_x == screen_width() - GetVacuumWidth())
    {
        PickANewDirection();
        bounced = true;
    }

    // Check to see if it has hit verical wall
    if (new_y <= 5 || new_y == screen_height() - 2 - GetVacuumheight())
    {
        PickANewDirection();
        bounced = true;
    }

    // Bounce off charger if not returning to the charger
    if (CheckForCollisionWithCharger(new_x, new_y) == true && BoolReturnToChager() == false)
    {
        PickANewDirection();
        bounced = true;
    }

    // If returning to charger and docked
    if (DockedAtCharger())
    {
        ResetWeight();
        SetTimeDocked();
        Pause();

        // Check to see if the weight has been emptyed.
        if (ReturnWeight() == 0)
        {
            Pause();
            vacuumY++;
            PickANewDirection();
            SetReturnTOChargerFalse();
            bounced = true;
        }
    }

    if (!bounced) // if bounce is not set to true then do function
    {
        vacuumX += vacuumDirectionX;
        vacuumY += vacuumDirectionY;
    }
}

// Return the X location of the vacuum cleaner
double GetVacuumX()
{
    return vacuumX;
}

// Set the X coordinate of the vacuum cleaner
void SetVacuumX(double value)
{
    vacuumX = value;
}

// Return the Y location of the vacuum cleaner
double GetVacuumY()
{
    return vacuumY;
}

// Set the Y coordinate of the vacuum cleaner
void SetVacuumY(double value)
{
    vacuumY = value;
}

// Return the value of what Vacuum cleaner Width equal too.
int GetVacuumWidth()
{
    return vacuum_width;
}

// Return the value of what Vacuum cleaner Height equal too.
int GetVacuumheight()
{
    return vacuum_height;
}

// ****************************************************************

// ************************* Cheats *******************************

// CHEATS: Set a custom x y and direction.
void MoveVacuumToXYZ()
{
    // int x, y, angle;
    vacuumX = get_int("Where would you like to place the Vacuum on the X axis?");      // Places the Vacuum at X axis
    vacuumY = get_int("Where would you like to place the Vacuum on the Y axis?");      // Places the Vacuum at Y axis
    vacuumDirection = get_int("What angle whould you like the vacuum to face 0-359?"); // Says which direction the device want to face
    vacuumDirectionX = VacuumDirectionXCalc(vacuumDirection);                          // Call the calculation function for X axis With the sum of 'vacuum_speed * cos(angle * M_PI / 180)'
    vacuumDirectionY = VacuumDirectionYCalc(vacuumDirection);                          // Call the calculation function for Y axis With the sum of 'vacuum_speed * sin(angle * M_PI / 180)'
}

// CHEATS: Push the vacuum cleaner upwards OR LEFT OR DOWNWARDS OR RIGHT by 1 pixel
void ControlVacuum(int ch)
{
    // if j move left 1 pixel
    if ((ch == 'j' || ch == 'J') && vacuumX - vacuum_width / 2 > 1 - 4) // Left
    {
        vacuumX--;
    }

    // if l move right 1 pixel
    else if ((ch == 'l' || ch == 'L') && vacuumX + vacuum_width / 2 < screen_width() - 6) // Right
    {
        vacuumX++;
    }

    // if k move down 1 pixel
    else if ((ch == 'k' || ch == 'K') && vacuumY + vacuum_height / 2 < screen_height() - 8) // Down
    {
        vacuumY++;
    }

    // if i move up 1 pixel
    else if ((ch == 'i' || ch == 'I') && vacuumY - vacuum_height / 2 > 1) // Up
    {
        vacuumY--;
    }
}

// CHEAT: Set the current load of rubbish on board of the vacuum cleanner
void SetWeight()
{
    int tempWeight;
    tempWeight = get_int("What would you like the current Load? (0 - 65)");
    if (tempWeight > 65)
    {
        weight = 0;
    }
    else
    {
        weight = tempWeight;
    }
}
// ****************************************************************

// ************************* Weight *******************************
// Load Carrying Capacity

// Clear the current load of rubbish on board of the vacuum cleanner
void ResetWeight()
{
    weight = 0;
}

// Add weight to the current load of rubbish on board of the vacuum cleanner
void AddWeight(int w)
{
    weight += w;
}

// Return the the current load of rubbish on board of the vacuum cleanner
int ReturnWeight()
{
    return weight;
}

// Checks to see if the current load of rubbish on board of the vacuum cleanner is greater then 45 if so return to charger to recharge and empty current load.
void CheckWeigthLevel()
{
    if (ReturnWeight() > 45)
    {
        ReturnToCharger();
    }
}

// ****************************************************************
