/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: collision.h          *
*********************************************
*/
#pragma once

#include <stdbool.h>

// Pixel Level Colision From AMS
bool pixel_collision(int x0, int y0, int w0, int h0, char pixel0[], int x1, int y1, int w1, int h1, char pixel1[]);

// Checks for anything touching the vacuum cleaner anything from; Dust, Slime, Trash, or charging station.
void CheckCollision();

// Returns a true or false value after checking if the vacuum cleaner is touching the charging station.
// CheckForCollisionWithCharger(double Vacuum X postion, double Vacuum Y Postion)
bool CheckForCollisionWithCharger(double vacXAxis, double vacYAxis);

// checks to see if the vacuum cleanere is at the charger and if the if statement equal to true, then it will emtpy the its current load.
void CheckForVacuumAtCharger();

// Return a true value if and only if the Vacuum cleanner is returning to charger is true and that the Vacuum is Touching the charger. Else if one of this statements are false the bool will return false.
bool DockedAtCharger();