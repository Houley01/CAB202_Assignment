/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: vacuum.h             *
*********************************************
*/
#pragma once
#include <stdbool.h>

// Draw the Vacuum cleanner at a given X and Y coordinates
void DrawVacuum();

// ****************************************************************

// *********************** Direction ******************************

// Randomly generate an angle when the vacuum cleaner runs into a obstacle like charger or walls
int PickAngle();
// Calculate the X direction with the angle using MATH equation COS
double VacuumDirectionXCalc(int angle);
// Calculate the Y direction with the angle using MATH equation SIN
double VacuumDirectionYCalc(int angle);
// Master Function which hides all the MATHS functions when the vacuum cleanner hits the wall. The function call PickAnglem VacuumDirectionYCalc And VacuumDirectionXCalc with setting the vacuum Direction and vacuumDirectionX, vacuumDirectionY
void PickANewDirection();
// Returns a user friendly output to the display so that user can see degree on which the vacuum cleanner is traveling
int GetVacuumDirection();
// Return the value of vacuumDirection before it gets displayed in the status bar.
double GetVacuumDirectionPreScreen();
// Set the vacuum Direction when the user use the cheat MoveVacuumToXYZ();
void SetVacuumDirection(int value);
// Calculate the X Direction based on the angle give when the user use the cheat MoveVacuumToXYZ(); to move the X Y and direction
void SetVacuumDirectionX();
// Calculate the Y Direction based on the angle give when the user use the cheat MoveVacuumToXYZ(); to move the X Y and direction
void SetVacuumDirectionY();

// ****************************************************************

// ************************* Vacuum *******************************

// Setup the Vacuum variables when the program first runs
void SetupVacuum();
// Checks if the new location for the vacuum cleaner will collide with a wall or charger.
void UpdatedVacuum();
// Return the X location of the vacuum cleaner
double GetVacuumX();
// Set the X coordinate of the vacuum cleaner
void SetVacuumX(double value);
// Return the Y location of the vacuum cleaner
double GetVacuumY();
// Set the Y coordinate of the vacuum cleaner
void SetVacuumY(double value);
// Return the value of what Vacuum cleaner Width equal too.
int GetVacuumWidth();
// Return the value of what Vacuum cleaner Height equal too.
int GetVacuumheight();

// ****************************************************************

// ************************* Cheats *******************************

// CHEATS: Set a custom x y and direction.
void MoveVacuumToXYZ();
// CHEATS: Push the vacuum cleaner upwards OR LEFT OR DOWNWARDS OR RIGHT by 1 pixel
void ControlVacuum(int ch);
// CHEAT: Set the current load of rubbish on board of the vacuum cleanner
void SetWeight();

// ****************************************************************

// ************************* Weight *******************************
// Load Carrying Capacity

// Clear the current load of rubbish on board of the vacuum cleanner
void ResetWeight();
// Add weight to the current load of rubbish on board of the vacuum cleanner
void AddWeight(int w);
// Return the the current load of rubbish on board of the vacuum cleanner
int ReturnWeight();
// Checks to see if the current load of rubbish on board of the vacuum cleanner is greater then 45 if so return to charger to recharge and empty current load.
void CheckWeigthLevel();