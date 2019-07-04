/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: charger.h            *
*********************************************
*/
// Set the x axis for the charging station based on the screen width
void SetCharingStationX();

// Draws the Charging Station
void DrawCharger();

// Sets the return to charger to false
void SetReturnTOChargerFalse();

// Return back to the charging station after calculating the quickest route
void ReturnToCharger();

// Returns the true or false value
bool BoolReturnToChager();

// Sets timeDocked to -1
void SetupTimeDocked();

// Set Varible TimeDocked to the currentTime when being called.
void SetTimeDocked();

// Returns the value for TimeDocked
int GetTimeDocked();

// Workout how many seconds have passed sinces TimeDocked was set
int ReturnTimeDocked();

// Return the locaction of postion X axis
int GetChargerX();

// Return the locaction of postion Y axis
int GetChargerY();

// Return the width of the charger
int GetChargerWidth();

// Return the height of the charger
int GetChargerHeight();