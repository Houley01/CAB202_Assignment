/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: main.c               *
*********************************************
*/
#include <math.h>
#include <stdlib.h>
#include <string.h>
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

// Global variables
bool SIMULATION = false;

// function that is used to draw all the objects to the screen.
void draw_all()
{
    clear_screen();
    DrawAllRubish();
    DrawBoarder();
    DrawInfoBox();
    PlaceInformationInInfoBox();
    DrawCharger();
    DrawVacuum();
    show_screen();
}

// Set up all objects in the simulation.

void setup(void)
{
    SetPausedToTrue();
    SetDelayAtStart();
    FillRubishArray();
    ResetWeight();
    SetCharingStationX();
    AskTheUserQuestionAboutRubish();
    GetstartTime();
    SetupRubish();
    SetupVacuum();
    draw_all();
    SetReturnTOChargerFalse();
    BatteryFlatMessageFalse();
    SetupTimeDocked();
}

// Resets the simulation.
void reset()
{
    setup();
}

void loop()
{
    int ch = get_char();
    if (ch == 'r') // Restart the simulation from setup()
    {
        reset();
    }
    else if (ch >= '0')
    {
        CheatCodes(ch);
    }
    else if (!ReturnPaused())
    {
        UpdatedVacuum();
    }
    else if (DockedAtCharger() == true) /* Does not work */
    {
        MessageDocked();
    }
    else if (ReturnBatteryFlatMessage() == true) /* Does not work */
    {
        BatteryFlatMessage();
    }

    CheckCollision();   // calls the function check for collision which checks to see if rubbish is in way.
    CheckWeigthLevel(); // Checks to see if the vacuum cleanner needs to return to the charger

    draw_all();
}

int main(void)
{
    srand(get_current_time()); // used for production, makes every simulation different.
    setup_screen();
    setup();
    while (!SIMULATION && !TimeOut())
    {
        loop();
        timer_pause(ReturnDelay());
    }
    if (TimeOut() == true)
    {
        TimeOutScreen();
    }

    return 0;
}
