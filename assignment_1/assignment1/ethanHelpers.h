/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: ethanHelpers.h       *
*********************************************
*/
// Draw bitmap used from drawing objects.
void DrawBitmap(int left, int top, int width, int height, char bitmap[], bool space_is_transparent);

// Giant if statment for charcodes to see if a cheat key has been entered
void CheatCodes(int ch);

// Set Paused to true at the start of the simulation
void SetPausedToTrue();

// Switchs between paused been true and false.
// If PAUSED = true, it will change it to false.
// If PAUSED = false, it will change it to true.
void Pause();

// Returns the bool value of PAUSED
bool ReturnPaused();

/* Time related functions \/ */

// Sets Start time and returns the value
double GetstartTime();

// How much time has passed scince reset
double TimeSinceReset();

// Returns the start time of the simiulation
double ReturnStartTime();

// Return the number of minutes the simiulation has been running for.
int ReturnTimeMinutes();

// Return the number of seconds the simiulation has been running for.
int ReturnTimeSeconds();

// Gets the user input for how do they want the simiulation to run for.
double SetTimeOut();

// Timeout bool (return a true or false) based on if the program has run for more then the allowed time
bool TimeOut();

// Gets the user input for how do they want the delay to be
void SetDelayAtStart();

// Sets the delay between each loop at the start of the program
void SetDelay();

// Returns the value of DELAY
int ReturnDelay();
/* Time related functions /\ */
