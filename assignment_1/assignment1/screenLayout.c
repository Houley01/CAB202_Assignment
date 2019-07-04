/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: screenLayout.c       *
*********************************************
*/
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
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

// note time has been moved to ethanhelper.c

void DrawInfoBox() // 25 function
{
    int width, height;
    get_screen_size(&width, &height);
    int borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
    double cellSize = (width / 3);                                           // getting the width of the screen and divding it in 3
    draw_line(0, 0, width - 1, 0, borderOutLine_horizontal);                 //  Top Side
    draw_line(0, 0, 0, 3, borderOutLine_vertical);                           //  Left Wall
    draw_line(width - 1, 0, width - 1, 3, borderOutLine_vertical);           //  Right Wall
    draw_line(cellSize, 0, cellSize, 4, borderOutLine_vertical);             //  Middle cell Left side
    draw_line((cellSize * 2), 0, (cellSize * 2), 3, borderOutLine_vertical); //  Middle cell Right side
    draw_line(0, 2, width - 1, 2, borderOutLine_horizontal);                 //  Middle line to split cells
    draw_line(0, 4, width - 1, 4, borderOutLine_horizontal);                 //  Bottom Side

    // Draw the plus in
    draw_char(0, 0, borderOutLine_intersection); // Left side row 1 cell 1
    draw_char(0, 2, borderOutLine_intersection); // Left side row 2 cell 1
    draw_char(0, 4, borderOutLine_intersection); // Left side row 2 cell 1 end of the row

    draw_char(cellSize, 0, borderOutLine_intersection); // Left side row 1 cell 2
    draw_char(cellSize, 2, borderOutLine_intersection); // Left side row 2 cell 2
    draw_char(cellSize, 4, borderOutLine_intersection); // Left side row 2 cell 2 end of the row

    draw_char((cellSize * 2), 0, borderOutLine_intersection); // Right side of row 1 cell 2
    draw_char((cellSize * 2), 2, borderOutLine_intersection); // Right side of row 2 cell 2
    draw_char((cellSize * 2), 4, borderOutLine_intersection); // Right side of row 3 cell 2

    draw_char((cellSize * 3), 0, borderOutLine_intersection); // Right side of row 1 cell 3
    draw_char((cellSize * 3), 2, borderOutLine_intersection); // Right side of row 2 cell 3
    draw_char((cellSize * 3), 4, borderOutLine_intersection); // Right side of row 3 cell 3
}

void PlaceInformationInInfoBox() // 9 functions
{
    int width, height;
    get_screen_size(&width, &height);
    double cellSize = (width / 3);
    // Row 1, cell 1 n10353950
    draw_string((cellSize / 2) - 5, 1, "n10353950");
    // Row 1, cell 2 Robots Direction 0 to 359
    draw_formatted(((cellSize / 2) + cellSize) - 12, 1, "Vacuum Direction: %i", GetVacuumDirection());
    // Row 1, cell 3 Battery Life Left
    draw_formatted((cellSize / 2) + (cellSize * 2) - 8, 1, "Battery Level: %i%c", BatteryLevel(), '%');
    // Row 2, cell 1 Time since last reset
    draw_formatted((cellSize / 2) - 6, 3, "Time: %02i:%02i", ReturnTimeMinutes(), ReturnTimeSeconds());
    // Row 2, cell 2 Weight of current load as %
    draw_formatted(((cellSize / 2) + cellSize) - 9, 3, "Current load: %ig", ReturnWeight());
    // Row 2, cell 3 Rubbish Available as int:  Dust, Slime, Trash
    draw_formatted((cellSize / 2) + (cellSize * 2) - 13, 3, "Rubish (D, S, T): %i, %i, %i", ReturnNumberOfDustOnScreen(), ReturnNumberOfSlimeOnScreen(), ReturnNumberOfTrashOnScreen());
}

void DrawBoarder()
{
    int width, height;
    get_screen_size(&width, &height);
    // GetWhatRoom();
    int borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
    // Draw the outline boards
    draw_line(0, 4, width - 1, 4, borderOutLine_horizontal);                   //  Top Side
    draw_line(0, height - 3, width - 1, height - 3, borderOutLine_horizontal); // Bottom Side
    draw_line(0, 4, 0, height - 3, borderOutLine_vertical);                    // Left Side
    draw_line(width - 1, 4, width - 1, height - 3, borderOutLine_vertical);    // Right Side
    // draw inersection characater
    draw_char(0, 4, borderOutLine_intersection);                  // Top Left
    draw_char(width - 1, 4, borderOutLine_intersection);          // Top Right
    draw_char(0, height - 3, borderOutLine_intersection);         // Bottom Left
    draw_char(width - 1, height - 3, borderOutLine_intersection); // Bottom Right
}

void Quit()
{
    int borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
    clear_screen();
    int width, height;
    get_screen_size(&width, &height);
    draw_line(0, 0, width - 1, 0, borderOutLine_horizontal);                   //  Top Side
    draw_line(0, height - 1, width - 1, height - 1, borderOutLine_horizontal); // Bottom Side
    draw_line(0, 0, 0, height - 1, borderOutLine_vertical);                    // Left Side
    draw_line(width - 1, 0, width - 1, height - 1, borderOutLine_vertical);    // Right Side
    // draw inersection characater
    draw_char(0, 0, borderOutLine_intersection);                  // Top Left
    draw_char(width - 1, 0, borderOutLine_intersection);          // Top Right
    draw_char(0, height - 1, borderOutLine_intersection);         // Bottom Left
    draw_char(width - 1, height - 1, borderOutLine_intersection); // Bottom Right
    draw_string((width / 2) - 18, (height / 2), "Thank You for running the simulation.");
    draw_string((width / 2) - 11, (height / 2) + 1, "Press any key to exit.");
    draw_string((width / 2) - 13, (height / 2) + 3, "Student Name: Ethan Houley");
    draw_string((width / 2) - 12, (height / 2) + 4, "Student number: n10353950");

    show_screen();
    wait_char(); // Wait for key to be pressed before closing
    exit(1);
}

void TimeOutScreen()
{
    int borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
    clear_screen();
    int width, height;
    get_screen_size(&width, &height);
    draw_line(0, 0, width - 1, 0, borderOutLine_horizontal);                   //  Top Side
    draw_line(0, height - 1, width - 1, height - 1, borderOutLine_horizontal); // Bottom Side
    draw_line(0, 0, 0, height - 1, borderOutLine_vertical);                    // Left Side
    draw_line(width - 1, 0, width - 1, height - 1, borderOutLine_vertical);    // Right Side
    // draw inersection characater
    draw_char(0, 0, borderOutLine_intersection);                  // Top Left
    draw_char(width - 1, 0, borderOutLine_intersection);          // Top Right
    draw_char(0, height - 1, borderOutLine_intersection);         // Bottom Left
    draw_char(width - 1, height - 1, borderOutLine_intersection); // Bottom Right
    draw_string((width / 2) - 18, (height / 2), "The simulation has run out of time.");
    draw_string((width / 2) - 19, (height / 2) + 1, "To run the similation agian press 'r'.");
    draw_string((width / 2) - 17, (height / 2) + 2, "To quit the similation press 'q'.");
    draw_string((width / 2) - 13, (height / 2) + 5, "Student Name: Ethan Houley");
    draw_string((width / 2) - 12, (height / 2) + 6, "Student number: n10353950");

    show_screen();
    wait_char(); // Wait for key to be pressed before closing
    exit(1);
}

// Help Screen information start
void HelpScreenHeading(double CenterOfScreen)
{
    draw_line(CenterOfScreen - 15, 0, CenterOfScreen + 15, 0, '*');
    draw_char(CenterOfScreen - 15, 1, '*');
    draw_string(CenterOfScreen - 5, 1, "Help Screen");
    draw_char(CenterOfScreen + 15, 1, '*');
    draw_line(CenterOfScreen - 15, 2, CenterOfScreen + 15, 2, '*');
}

void HelpScreenRubishInfo(double CenterOfScreen)
{
    // Rubish Buttons
    draw_line(CenterOfScreen - 15, 4, CenterOfScreen + 15, 4, '*');
    draw_char(CenterOfScreen - 15, 5, '*');
    draw_string(CenterOfScreen - 12, 5, "Information About Rubish");
    draw_char(CenterOfScreen + 15, 5, '*');
    draw_line(CenterOfScreen - 15, 6, CenterOfScreen + 15, 6, '*');
    draw_string(CenterOfScreen - 15, 8, "D - Drop dust at X and Y Location.");
    draw_string(CenterOfScreen - 15, 9, "S - Drop slime at X and Y Location.");
    draw_string(CenterOfScreen - 15, 10, "T - Drop Trash at X and Y Location.");
}

void HelpScreenSimulationSettings(double CenterOfScreen)
{
    draw_line(CenterOfScreen - 15, 12, CenterOfScreen + 15, 12, '*');
    draw_char(CenterOfScreen - 15, 13, '*');
    draw_string(CenterOfScreen - 9, 13, "Simulation Settings");
    draw_char(CenterOfScreen + 15, 13, '*');
    draw_line(CenterOfScreen - 15, 14, CenterOfScreen + 15, 14, '*');
    draw_string(CenterOfScreen - 15, 16, "M  - Change the delay between each loop in millisecond.");
    draw_string(CenterOfScreen - 15, 17, "O (NOT ZERO) - Set the time for how long the simulation runs for.");
    draw_string(CenterOfScreen - 15, 18, "Q - Close the simulation.");
    draw_string(CenterOfScreen - 15, 19, "R - Restart the simulation.");
    draw_string(CenterOfScreen - 15, 20, "? - Displays the Help Screen");
}

void HelpScreenVaccumInfo(double CenterOfScreen)
{

    draw_line(CenterOfScreen - 15, 22, CenterOfScreen + 15, 22, '*');
    draw_char(CenterOfScreen - 15, 23, '*');
    draw_string(CenterOfScreen - 5, 23, "Vacuum Items");
    draw_char(CenterOfScreen + 15, 23, '*');
    draw_line(CenterOfScreen - 15, 24, CenterOfScreen + 15, 24, '*');

    draw_string(CenterOfScreen - 15, 26, "I - Moves the vacuum North (up) one unit.");
    draw_string(CenterOfScreen - 15, 27, "J - Moves the vacuum  West (left) one unit.");
    draw_string(CenterOfScreen - 15, 28, "K - Moves the vacuum South (down) one unit.");
    draw_string(CenterOfScreen - 15, 29, "L - Moves the vacuum East (right) one unit.");

    draw_string(CenterOfScreen - 15, 31, "V - Set the location for the Vacuum. Requires X axis, Y axis and facing what direction.");
    draw_string(CenterOfScreen - 15, 32, "W - Change the current load of rubish the Vacuum has collected.");
    draw_string(CenterOfScreen - 15, 33, "Y - Change the current Battery Level of the Vacuum");
}

void HelpScreen()
{
    Pause();
    clear_screen();
    int width, height;
    get_screen_size(&width, &height);
    double CenterOfScreen = (width / 2);
    // Call functions to draw the Help page Info
    HelpScreenHeading(CenterOfScreen);
    HelpScreenRubishInfo(CenterOfScreen);
    HelpScreenSimulationSettings(CenterOfScreen);

    HelpScreenVaccumInfo(CenterOfScreen);

    draw_string(CenterOfScreen - 15, 45, "Press any key to return the previous screen.");
    show_screen();
    while (get_char() > 0)
    {
    }
    while (!TimeOut() && wait_char() <= 0)
    {
    }
    Pause();
}

void MessageDocked()
{
    draw_formatted(screen_width() / 2 - 4, screen_height() - 2, "Docked");
    show_screen();
}

void BatteryFlatMessage()
{
    Pause();
    draw_formatted(screen_width() / 2, screen_height() / 2, "");
    show_screen();
}