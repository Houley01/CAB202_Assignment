/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: screenLayout.h       *
*********************************************
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <cab202_graphics.h>

// Draws the information box
void DrawInfoBox();
void PlaceInformationInInfoBox();
// Write the data to the screen
void DrawBoarder();

// Shows the quit screen
void Quit();
// Calls the display which say the simulation has run out of time.
void TimeOutScreen();

// Help screen information
void HelpScreenHeading(double CenterOfScreen);
void HelpScreenRubishInfo(double CenterOfScreen);
void HelpScreenSimulationSettings(double CenterOfScreen);
void HelpScreenVaccumInfo(double CenterOfScreen);
void HelpScreen();

void MessageDocked();

// void BatteryScreenAlert();
void BatteryFlatMessage();