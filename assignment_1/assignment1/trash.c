/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: trash.c              *
*********************************************
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>

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

// Dust varibles
char *dust = ".";
#define dustHeight 1
#define dustWidth 1
int numberOfDust = 1;
#define maxdust 1000
int dustPlacementX[maxdust], dustPlacementY[maxdust];

// slime variables
char *slime =
    "  ~  "
    " ~~~ "
    "~~S~~"
    " ~~~ "
    "  ~  ";
#define slimeHeight 5
#define slimeWidth 5
int numberOfSlime = 1;
#define maxslime 10
int slimePlacementX[maxslime], slimePlacementY[maxslime];

// Trash varibales
char *trash =
    "     &     "
    "    &T&    "
    "   &_R_&   "
    "  &__A__&  "
    " &___s___& "
    "&&&&&&&&&&&";
#define trashHeight 6
#define trashWidth 11
int numberOfTrash = 1;
#define maxtrash 5
int trashPlacementX[maxtrash], trashPlacementY[maxtrash];

// Fill the arry is make sure no rubbish is shown on screen.
void FillRubishArray()
{
    // loop through all items in array and give them a negitive value.
    for (int i = 0; i < maxtrash; i++)
    {
        trashPlacementX[i] = -5 - trashWidth * i;
        trashPlacementY[i] = -5 - trashHeight * i;
    }
    for (int i = 0; i < maxslime; i++)
    {
        /* code */
        slimePlacementX[i] = -5 - slimeWidth * i;
        slimePlacementY[i] = -10 - slimeHeight * i;
    }
    for (int i = 0; i < maxdust; i++)
    {
        /* code */
        dustPlacementX[i] = -5 - dustWidth * i;
        dustPlacementY[i] = -15 - dustHeight * i;
    }
}

// Would of liked to of had function which would call the array from vacuum.c
char *Vac =
    "   @@@   "
    "  @@@@@  "
    " @@@@@@@ "
    "@@@@@@@@@"
    "@@@VAC@@@"
    "@@@@@@@@@"
    " @@@@@@@ "
    "  @@@@@  "
    "   @@@   ";

// Would of liked to of had function which would call the array from charger.c
char *Chager =
    "#########"
    "#CHARGER#"
    "#########";

// check if anything will be overlapping when rubbish is spawned
bool CheckToSeeIfTheSpaceIsClear(int x0, int y0, int width, int height, char object[])
{
    // Test to see if the rubish is touching the vacuum cleaner at the start
    if (pixel_collision(x0, y0, width, height, object,
                        ((screen_width() / 2) - 5), ((screen_height() / 2) - 5), GetVacuumWidth(), GetVacuumheight(), Vac) == true)
    {
        return false;
    }

    // Test to see if the rubish is touching the charger at the start
    if (pixel_collision(x0, y0, width, height, object,
                        GetChargerX(), GetChargerY(), GetChargerWidth(), GetChargerHeight(), Chager) == true)
    {
        return false;
    }

    // Loops through and checks the array for any trash would be touching the item being place
    for (int i = 0; i < numberOfTrash; i++)
    {
        if (pixel_collision(x0, y0, width, height, object,
                            trashPlacementX[i], trashPlacementY[i], trashWidth, trashHeight, trash) == true)
        {
            return false;
        }
    }

    // Loops through and checks the array for any slime would be touching the item being place
    for (int i = 0; i < numberOfSlime; i++)
    {
        if (pixel_collision(x0, y0, width, height, object,
                            slimePlacementX[i], slimePlacementY[i], slimeWidth, slimeHeight, slime) == true)
        {
            return false;
        }
    }

    // Loops through and checks the array for any dust would be touching the item being place
    for (int i = 0; i < numberOfDust; i++)
    {
        if (pixel_collision(x0, y0, width, height, object,
                            dustPlacementX[i], dustPlacementY[i], dustWidth, dustHeight, dust) == true)
        {
            return false;
        }
    }
    //  If all the above statements are false then return true, allowing the object to be places on screen.
    return true;
}

// Find a place to place rubish.
void FindASpot(int i, int XAxie[], int YAxie[], int width, int height, char Object[])
{
    int screenWidth, screenHeight, testPlacementX, testPlacementY;
    get_screen_size(&screenWidth, &screenHeight);
    testPlacementX = rand() % (screenWidth - 1 - width);
    testPlacementY = (rand() % (screenHeight - 2 - height));

    // Checks the Top board and push down if it is less then 5
    for (int i = 0; testPlacementY < 5; i++)
    {
        testPlacementY++;
    }
    // If an object is placed at X:0 it will be pushed 1 spot to the right
    if (testPlacementX == 0)
    {
        testPlacementX = 1;
    }
    // If BOOL CheckToSeeIfTheSpaceIsClear Return false it will restart the function for the single object
    if (CheckToSeeIfTheSpaceIsClear(testPlacementX, testPlacementY, width, height, Object) == false)
    {
        FindASpot(i, XAxie, YAxie, width, height, Object);
    }
    // If BOOL CheckToSeeIfTheSpaceIsClear Return True it will set the x and y coordinates for the object
    if (CheckToSeeIfTheSpaceIsClear(testPlacementX, testPlacementY, width, height, Object) == true)
    {
        XAxie[i] = testPlacementX;
        YAxie[i] = testPlacementY;
    }
}

// **************************** Master Function ****************************

// Master Function which gets called in main. The master function loops through Array for each rubbish catorgory and setup the location before being drawn.
void SetupRubish()
{
    TrashSetup();
    SlimeSetup();
    DustSetup();
}

// Master Function which gets called in main to loop through and draws all rubbish.
void DrawAllRubish()
{
    for (int i = 0; i < maxtrash; i++)
    {
        DrawTrash(i);
    }
    for (int i = 0; i < maxslime; i++)
    {
        DrawSlime(i);
    }
    for (int i = 0; i < maxdust; i++)
    {
        DrawDust(i);
    }
}

// Master Function which gets called in main which ask the user how much rubbish the user would like to have on screen.
void AskTheUserQuestionAboutRubish()
{
    HowMuchDust();
    HowMuchSlime();
    HowMuchTrash();
}
// ****************************************************************

// ************************* TRASH *********************************
// Ask the user how much TRASH they would like in the simiulation.
void HowMuchTrash()
{
    int tempNumberOfTrash = get_int("How much trash do you want?");
    // Check to see if the user has entered a number bellow the max number of trash, if not number of trash is set to 0
    if (tempNumberOfTrash > maxtrash)
    {
        numberOfTrash = 0;
    }
    else
    {
        numberOfTrash = tempNumberOfTrash;
    }
}

// Draw Trash one pieces of slime at x[i] y[i] depending on what i equals
void DrawTrash(int i)
{
    DrawBitmap(trashPlacementX[i], trashPlacementY[i], trashWidth, trashHeight, trash, true);
}

// Goes through a for loop to try and find any empty spot for TRASH to be placed
void TrashSetup()
{
    for (int i = 0; i < numberOfTrash; i++)
    {
        FindASpot(i, trashPlacementX, trashPlacementY, trashWidth, trashHeight, trash);
    }
}

// Returns the number of Trash being displayed on screen
int ReturnNumberOfTrashOnScreen()
{
    return numberOfTrash;
}

// Removes one piece of Trash from the counter.
void RemoveOneTrash()
{
    numberOfTrash--;
}

// Adds one piece of Trash from the counter.
void AddOneTrash()
{
    numberOfTrash++;
}

//  Return the value of what Max Trash equal too.
int ReturnMaxTrash()
{
    return maxtrash;
}

// Return the value of what Trash Width equal too.
int ReturnTrashWidth()
{
    return trashWidth;
}

// Return the value of what Trash Height equal too.
int ReturnTrashHeight()
{
    return trashHeight;
}

// Return the value of what Trash Placement X array[i].
int ReturnTrashX(int i)
{
    return trashPlacementX[i];
}

// Return the value of what Trash Placement Y array[i].
int ReturnTrashY(int i)
{
    return trashPlacementY[i];
}

// Set the value for Trash Placement X array[i] = xAxis.
void SetTrashX(int i, int xAxis)
{
    trashPlacementX[i] = xAxis;
}

// Set the value for Trash Placement Y array[i] = YAxis.
void SetTrashY(int i, int yAxis)
{
    trashPlacementY[i] = yAxis;
}

// ****************************************************************

// ************************* SLIME *********************************

// Ask the user how much SLIME they would like in the simiulation.
void HowMuchSlime()
{
    int tempNumberOfSlime = get_int("How much slime do you want?");
    // Check to see if the user has entered a number bellow the max number of slime, if not number of slime is set to 0
    if (tempNumberOfSlime > maxslime)
    {
        numberOfSlime = 0;
    }
    else
    {
        numberOfSlime = tempNumberOfSlime;
    }
}

// Draw Slime one pieces of slime at x[i] y[i] depending on what i equals
void DrawSlime(int i)
{
    DrawBitmap(slimePlacementX[i], slimePlacementY[i], slimeWidth, slimeHeight, slime, true);
}

// Goes through a for loop to try and find any empty spot for Slime to be placed
void SlimeSetup()
{
    for (int i = 0; i < numberOfSlime; i++)
    {
        FindASpot(i, slimePlacementX, slimePlacementY, slimeWidth, slimeHeight, slime);
    }
}

// Returns the number of Slime being displayed on screen
int ReturnNumberOfSlimeOnScreen()
{
    return numberOfSlime;
}

// Removes one piece of Slime from the counter.
void RemoveOneSlime()
{
    numberOfSlime--;
}

// Add one piece of Slime from the counter.
void AddOneSlime()
{
    numberOfSlime++;
}

//  Return the value of what Max Slime equal too.
int ReturnMaxSlime()
{
    return maxslime;
}

// Return the value of what Slime Width equal too.
int ReturnSlimeWidth()
{
    return slimeWidth;
}

// Return the value of what Slime Height equal too.
int ReturnSlimeHeight()
{
    return slimeHeight;
}

// Return the value of what Slime Placement X array[i].
int ReturnSlimeX(int i)
{
    return slimePlacementX[i];
}

// Return the value of what Slime Placement Y array[i].
int ReturnSlimeY(int i)
{
    return slimePlacementY[i];
}

// Set the value for Slime Placement X array[i] = xAxis.
void SetSlimeX(int i, int xAxis)
{
    slimePlacementX[i] = xAxis;
}

// Set the value for Slime Placement Y array[i] = YAxis.
void SetSlimeY(int i, int yAxis)
{
    slimePlacementY[i] = yAxis;
}

// ****************************************************************

// ************************* DUST *********************************

// Ask the user how much DUST they would like in the simiulation.
void HowMuchDust()
{

    int tempNumberOfDust = get_int("How much dust do you want?");
    // Check to see if the user has entered a number bellow the max number of dust, if not number of dust is set to 0
    if (tempNumberOfDust > maxdust)
    {
        numberOfDust = 0;
    }
    else
    {
        numberOfDust = tempNumberOfDust;
    }
}

// Draw Dust one pieces of Dust at x[i] y[i] depending on what i equals
void DrawDust(int i)
{
    DrawBitmap(dustPlacementX[i], dustPlacementY[i], dustWidth, dustHeight, dust, true);
}

// Goes through a for loop to try and find any empty spot for dust to be placed
void DustSetup()
{
    for (int i = 0; i < numberOfDust; i++)
    {
        FindASpot(i, dustPlacementX, dustPlacementY, dustWidth, dustHeight, dust);
    }
}

// Returns the number of Dust being displayed on screen
int ReturnNumberOfDustOnScreen()
{
    return numberOfDust;
}

// Removes one piece of Dust from the counter.
void RemoveOneDust()
{
    numberOfDust--;
}

// Adds one piece of Dust from the counter.
void AddOneDust()
{
    numberOfDust++;
}

//  Return the value of what Max Dust equal too.
int ReturnMaxDust()
{
    return maxdust;
}

// Return the value of what Dust Width equal too.
int ReturnDustWidth()
{
    return dustWidth;
}

// Return the value of what Dust Height equal too.
int ReturnDustHeight()
{
    return dustHeight;
}

// Return the value of what Dust Placement X array[i].
int ReturnDustX(int i)
{
    return dustPlacementX[i];
}

// Return the value of what Dust Placement Y array[i].
int ReturnDustY(int i)
{
    return dustPlacementY[i];
}

// Set the value for Dust Placement X array[i] = xAxis.
void SetDustX(int i, int xAxis)
{
    dustPlacementX[i] = xAxis;
}

// Set the value for Dust Placement Y array[i] = YAxis.
void SetDustY(int i, int yAxis)
{
    dustPlacementY[i] = yAxis;
}

// ******************************************************************

bool CheckForWalls(int xLocation, int yLocation, int width, int height)
{
    if (yLocation <= 4)
    {
        return false;
    }
    if (yLocation >= (screen_height() - 2 - height))
    {
        return false;
    }
    if (xLocation == 0)
    {
        return false;
    }
    if (xLocation >= (screen_width() - width))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool IfStatementForDropingRubbish(int numberOfItems, int maxNumberOfObjects, int xAxisArray[], int yAxisArray[], int objectWidth, int objectHeight)
{
    int xLocation, yLocation;
    if (numberOfItems < maxNumberOfObjects)
    {
        int freeLocation = 0;
        xLocation = get_int("What location would you like to dorp the rubbish on X Axis?");
        yLocation = get_int("What location would you like to dorp the rubbish on Y Axis?");
        if (CheckForWalls(xLocation, yLocation, objectWidth, objectHeight))
        {
            for (int i = 0; i < maxNumberOfObjects; i++)
            {
                // Go through the array and end the loop after finding a
                // an X and Y coordinate from the array.
                if (xAxisArray[i] < 0 && yAxisArray[i] < 0)
                {

                    freeLocation = i;
                    break;
                }
            }
            xAxisArray[freeLocation] = xLocation;
            yAxisArray[freeLocation] = yLocation;
            return true;
        }
        else
        {
            // Let the user know they have put the dust outside of the screen
            draw_formatted(screen_width() / 2 - 52, screen_height() - 2, "Sorry, but you have entered a value for the 'X' OR 'Y' value which is not allowed in the the screen area.");
            draw_formatted(screen_width() / 2 - 20, screen_height() - 1, "Press any key to continue the simulation.");
            show_screen();
            wait_char();
            return false;
        }
        // Display a message say max dust on screen.
    }
    else
    {
        draw_formatted(screen_width() / 2 - 35, screen_height() - 2, "Sorry, but you have placed the rubbish outside of the allowed on the screen.");
        draw_formatted(screen_width() / 2 - 20, screen_height() - 1, "Press any key to continue the simulation.");
        show_screen();
        wait_char();
        return false;
    }
}

// Cheats for dropping rubbish Items
void DropRubish(char key)
{
    // Checks to see if the char equal to 'd' or 'D'
    if (key == 'd' || key == 'D')
    {
        // Checks to see if the Dust there is any dust aviable to drop, or if the dust is inside area
        if (IfStatementForDropingRubbish(numberOfDust, maxdust, dustPlacementX, dustPlacementY, dustWidth, dustHeight) == true)
        {
            AddOneDust();
        }
    }
    // Checks to see if the char equal to 's' or 'S'
    else if (key == 's' || key == 'S')
    {
        // Checks to see if the Slime there is any dust aviable to drop, or if the dust is inside area
        if (IfStatementForDropingRubbish(numberOfSlime, maxslime, slimePlacementX, slimePlacementY, slimeWidth, slimeHeight) == true)
        {
            AddOneSlime();
        }
    }
    // Checks to see if the char equal to 't' or 'T'
    else if (key == 't' || key == 'T')
    {
        // Checks to see if the Trash there is any dust aviable to drop, or if the dust is inside area
        if (IfStatementForDropingRubbish(numberOfTrash, maxtrash, trashPlacementX, trashPlacementY, trashWidth, trashHeight) == true)
        {
            AddOneTrash();
        }
    }
}