/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: battery.h            *
*********************************************
*/
// Calculates what the battery % so it can be displayed in the status section.
int BatteryLevel();

// Set the bool to true
void BatteryFlatMessageTrue();

// Set the bool to flase
void BatteryFlatMessageFalse();

// Return the bool saying if the statement is true or false
bool ReturnBatteryFlatMessage();

//  Gets the users input to change the current battery level
void ChangeBatteryLevel();