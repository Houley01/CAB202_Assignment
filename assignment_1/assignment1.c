#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

// var's
double start_time;
// Vacuum varibles
int vacuumHeight = 9, vacuumWidth = 9;
char *vacuum =
    "    @    "
    "  @@@@@  "
    " @@@@@@@ "
    "@@@@@@@@@"
    "@@@VAC@@@"
    "@@@@@@@@@"
    " @@@@@@@ "
    "  @@@@@  "
    "    @    ";
// int static MaxCarryCapacity = 65;
#define speed 0.2
double vacuumX, vacuumY, vacuumDirectionX, vacuumDirectionY, vacuumDirection;
int currentLoad = 0;

int chargingStationHeight = 3, chargingStationWidth = 9;
char *chargingStation =
    "#########"
    "#CHARGER#"
    "#########";

char *dust = ".";
int dustHeight = 1, dustWidth = 1;
int numberOfDust = 1;
#define maxdust 1000
int dustPlacementX[maxdust], dustPlacementY[maxdust];

char *slime =
    "  ~  "
    " ~~~ "
    "~ S ~"
    " ~~~ "
    "  ~  ";
int slimeHeight = 5, slimeWidth = 5;
int numberOfSlime = 1;
#define maxslime 10
int slimePlacementX[maxslime], slimePlacementY[maxslime];

char *trash =
    "     &     "
    "    &T&    "
    "   & R &   "
    "  &  A  &  "
    " &   s   &"
    "&&&&&&&&&&&";
int TrashHeight = 6, TrashWidth = 11;
int numberOfTrash = 1;
#define maxtrash 5
int trashPlacementX[maxtrash], trashPlacementY[maxtrash];

bool SIMULATION = false, IsVacuumStation = true;
// Insert other functions here, or include header files

char *RobotsDirection()
{
    return "Direction: 359";
}

char *RobotsBatteryLevel()
{
    return "Battery: 100%";
}

int TimeSinceReset()
{
    int timeCounter = get_current_time() - start_time;

    return timeCounter;
}

char *RobotsCurrentLoad()
{
    return "Current Load: 25g";
}

char *RubishCount()
{
    return "Rubish (D, S, T): 5, 6, 2";
}

void DrawInfoBox() // 25 function
{
    int width, height;
    get_screen_size(&width, &height);
    int borderOutLine_horizontal, borderOutLine_vertical, borderOutLine_intersection;
    borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
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

    draw_char((cellSize * 3), 0, borderOutLine_intersection); // Right side of row 1 cell 2
    draw_char((cellSize * 3), 2, borderOutLine_intersection); // Right side of row 2 cell 2
    draw_char((cellSize * 3), 4, borderOutLine_intersection); // Right side of row 3 cell 2
}

void PlaceInformationInInfoBox() // 9 functions
{
    int width, height;
    get_screen_size(&width, &height);
    double cellSize = (width / 3);
    // Row 1, cell 1 n10353950
    draw_string((cellSize / 2) - 5, 1, "n10353950");
    // Row 1, cell 2 Robots Direction 0 to 359
    draw_string(((cellSize / 2) + cellSize) - 7, 1, RobotsDirection());
    // Row 1, cell 3 Battery Life Left
    draw_string((cellSize / 2) + (cellSize * 2) - 7, 1, RobotsBatteryLevel());
    // Row 2, cell 1 Time since last reset
    draw_int((cellSize / 2) - 6, 3, TimeSinceReset());
    // Row 2, cell 2 Weight of current load as %
    draw_string(((cellSize / 2) + cellSize) - 9, 3, RobotsCurrentLoad());
    // Row 2, cell 3 Rubbish Available as int:  Dust, Slime, Trash
    draw_string((cellSize / 2) + (cellSize * 2) - 13, 3, RubishCount());
}

void DrawBoards()
{
    int width, height;
    get_screen_size(&width, &height);
    // GetWhatRoom();
    int borderOutLine_horizontal, borderOutLine_vertical, borderOutLine_intersection;
    borderOutLine_horizontal = '-', borderOutLine_vertical = '|', borderOutLine_intersection = '+';
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
}

void SetupVacuum()
{
    // if (MaxCarryCapacity < 45)
    int width, height;
    get_screen_size(&width, &height);

    // vacuumX = 1 + rand() % (width - 2);
    // vacuumY = 1 + rand() % (height - 2);
    vacuumX = (width / 2) - 5;
    vacuumY = (height / 2) - 5;

    const double step = speed;
    vacuumDirection = 90;
    vacuumDirectionX = step * cos(vacuumDirection);
    vacuumDirectionY = step * sin(vacuumDirection);
}

void DrawVacuum()
{
    DrawBitmap(vacuumX, vacuumY, vacuumWidth, vacuumHeight, vacuum, true);
}

void UpdateVacuum()
{

    int new_x = round(vacuumX + vacuumDirectionX);
    int new_y = round(vacuumY + vacuumDirectionY);

    bool bounced = false;

    if (new_x == 1 || new_x == screen_width() - vacuumWidth)
    {
        // Check to see if it has hit horzontal wall
        // vacuumDirectionX = -vacuumDirectionX;

        bounced = true;
    }

    if (new_y == 5 || new_y == screen_height() - 2 - vacuumHeight)
    {
        // vacuumDirectionY = -vacuumDirectionY;
        // Check to see if it has hit horzontal wall
        bounced = true;
    }

    if (!bounced) // if !false (true)
    {
        vacuumX += vacuumDirectionX;
        vacuumY += vacuumDirectionY;
    }
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
    draw_string((width / 2) - 13, (height / 2) + 3, "Student Name: Ethan Houley");
    draw_string((width / 2) - 12, (height / 2) + 4, "Student number: n10353950");

    show_screen();
    wait_char(); // Wait for key to be pressed before closing
    exit(1);
}

void CheatCodes(int ch)
{
    if (ch == 'b') // Return to charger
    {
        // ReturnToCharger();
    }
    else if (ch == 'd') // Drops dust ( Small Rubbish)
    {
        // DropDust();
    }
    else if (ch == 's') // Drop slime (Medium Rubish)
    {
        // DropSlime();
    }
    else if (ch == 't') // Drop trash (Large Rubish)
    {
        // DropTrash();
    }

    else if (ch == 'm') /* change milliseconds delay bettween loops */
    {
    }

    else if (ch == 'o') // Change the time allow for the program runs for
    {
    }

    else if (ch == 'p') // start or stop the robot moving
    {
        // TurnOnOrOffRObot();
    }

    else if (ch == 'q') // Quit simulation
    {
        Quit();
    }

    else if (ch == 'v') // Move Robot to x and y location
    {
        // MoveRobotTo();
    }
    else if (ch == 't') // Change Current load of rubish
    {
        // ChangeCurrentLoadOfRubish();
    }
    else if (ch == 't') // Change Current load of rubish
    {
        // ChangeCurrentLoadOfRubish();
    }
    else if (ch == 'y') // Set new battery Level
    {
        // ChangeBatteryLevel();
    }
    else if (ch == 'r') // Set new battery Level
    {
        // reset();
    }
    else if (ch == '?') // Set new battery Level
    {
        HelpScreen();
    }
}

void DrawAll()
{
    clear_screen();
    DrawBoards();
    DrawInfoBox();
    PlaceInformationInInfoBox();
    DrawVacuum();
    show_screen();
}

void setup()
{
    // Insert setup logic here.
    start_time = get_current_time();
    DrawAll();
    SetupVacuum();
}

void reset()
{
    setup();
}

void loop()
{
    int cheatCodeChar = get_char();
    CheatCodes(cheatCodeChar);
    UpdateVacuum();
    DrawAll();
}

int main()
{
    // milliseconds sleep between calls to loop.
    int DELAY = 10;

    setup_screen();
    setup();
    show_screen();

    while (!SIMULATION)
    {
        loop();
        timer_pause(DELAY);
    }

    return 0;
}
