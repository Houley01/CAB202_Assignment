/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: collision.c          *
*********************************************
*/
#include <string.h>

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

// Pixel Level Colision From AMS
bool pixel_collision(int x0, int y0, int w0, int h0, char pixel0[], int x1, int y1, int w1, int h1, char pixel1[])
{
    for (int x = 0; x < (x0 + w0); x++) // X axie
    {
        for (int y = 0; y < (y0 + h0); y++) // y axie
        {

            if (x >= x0 && x < (x0 + w0) && y >= y0 && y < (y0 + h0) && pixel0[(x - x0) + (y - y0) * w0] != ' ' &&
                x >= x1 && x < (x1 + w1) && y >= y1 && y < (y1 + h1) && pixel1[(x - x1) + (y - y1) * w1] != ' ')
            {
                return true;
            }
        }
    }
    return false;
}

// Items that are checked for when seeing if ItemA is touching ItemB
// Vacuum
char *v =
    "   @@@   "
    "  @@@@@  "
    " @@@@@@@ "
    "@@@@@@@@@"
    "@@@VAC@@@"
    "@@@@@@@@@"
    " @@@@@@@ "
    "  @@@@@  "
    "   @@@   ";
// Charging station
char *c =
    "#########"
    "#CHARGER#"
    "#########";

// Dust
char *d = ".";

// Slime
char *s =
    "  ~  "
    " ~~~ "
    "~~S~~"
    " ~~~ "
    "  ~  ";

// Trash
char *t =
    "     &     "
    "    &T&    "
    "   &_R_&   "
    "  &__A__&  "
    " &___s___& "
    "&&&&&&&&&&&";

// Checks for anything touching the vacuum cleaner anything from; Dust, Slime, Trash, or charging station.
void CheckCollision()
{
    // Loop throught the array of trash to see if the the vacuum is touching a peice of trash in the frame
    for (int i = 0; i < ReturnMaxTrash(); i++)
    {
        // if the vacuum is not going back to the charging station
        // And that the vacuum cleaner axis x and  axis y are the same as the one pieces of trash.
        if (BoolReturnToChager() == false && pixel_collision(GetVacuumX(), GetVacuumY(), GetVacuumWidth(), GetVacuumheight(), v, ReturnTrashX(i), ReturnTrashY(i), ReturnTrashWidth(), ReturnTrashWidth(), c))
        {
            // If the if statement is true send the piece of trash off screen and remove one from the counter, And add 20grams of weight to the vacuum.

            // trashPlacementX[i] =  trashPlacementX[i] * (times) -screen_width()
            SetTrashX(i, ReturnTrashX(i) * -screen_width());

            //trashPlacementY[i] =  trashPlacementY[i] * (times) -screen_height()
            SetTrashY(i, ReturnTrashY(i) * -screen_height());

            // Remove one Pieces of trash from the counter
            RemoveOneTrash();
            // Add weight to the current load
            AddWeight(20);
        }
    }

    // Loop throught the array of slime to see if the the vacuum is touching a peice of slime in the frame
    for (int i = 0; i < ReturnMaxSlime(); i++)
    {
        // if the vacuum is not going back to the charging station
        // And that the vacuum cleaner axis x and  axis y are the same as the one pieces of slime.
        if (BoolReturnToChager() == false && pixel_collision(GetVacuumX(), GetVacuumY(), GetVacuumWidth(), GetVacuumheight(), v, ReturnSlimeX(i), ReturnSlimeY(i), ReturnSlimeWidth(), ReturnSlimeWidth(), s))
        {
            // If the if statement is true send the piece of trash off screen and remove one from the counter, And add 5grams of weight to the vacuum.

            //slimePlacementX[i] =  slimePlacementX[i] * (times) -screen_width()
            SetSlimeX(i, ReturnSlimeX(i) * -screen_width());
            //slimePlacementY[i] =  slimePlacementY[i] * (times) -screen_wigth()
            SetSlimeY(i, ReturnSlimeY(i) * -screen_height());
            // Remove one Pieces of slime from the counter
            RemoveOneSlime();
            // Add weight to the current load
            AddWeight(5);
        }
    }

    // Loop throught the array of dust to see if the the vacuum is touching a peice of dust in the frame
    for (int i = 0; i < ReturnMaxDust(); i++)
    {
        if (BoolReturnToChager() == false && pixel_collision(GetVacuumX(), GetVacuumY(), GetVacuumWidth(), GetVacuumheight(), v, ReturnDustX(i), ReturnDustY(i), ReturnDustWidth(), ReturnDustWidth(), d))
        {
            // if the vacuum is not going back to the charging station
            // And that the vacuum cleaner axis x and  axis y are the same as the one pieces of dust.

            //dustPlacementX[i] =  dustPlacementX[i] * (times) -screen_width()
            SetDustX(i, ReturnDustX(i) * -screen_width());

            //dustPlacementY[i] =  dustPlacementY[i] * (times) -screen_height()
            SetDustY(i, ReturnDustY(i) * -screen_height());

            // Remove one Pieces of dust from the counter
            RemoveOneDust();

            // Add weight to the current load
            AddWeight(1);
        }
    }
    // Checks to see if the vacuum cleanere is at the charger
    CheckForVacuumAtCharger();
}

// Returns a true or false value after checking if the vacuum cleaner is touching the charging station.
// CheckForCollisionWithCharger(double Vacuum X postion, double Vacuum Y Postion)
bool CheckForCollisionWithCharger(double vacXAxis, double vacYAxis)
{
    if (pixel_collision(vacXAxis, vacYAxis, GetVacuumWidth(), GetVacuumheight(), v, GetChargerX(), GetChargerY(), GetChargerWidth(), GetChargerHeight() + 1, c))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks to see if the vacuum cleanere is at the charger and if the if statement equal to true, then it will emtpy the its current load.
void CheckForVacuumAtCharger()
{
    if (DockedAtCharger())
    {
        ResetWeight();
        show_screen();
    }
}

// Return a true value if and only if the Vacuum cleanner is returning to charger is true and that the Vacuum is Touching the charger. Else if one of this statements are false the bool will return false.
bool DockedAtCharger()
{
    if (BoolReturnToChager() == true && CheckForCollisionWithCharger(GetVacuumX(), GetVacuumY()))
    {
        return true;
    }
    else
    {
        return false;
    }
}