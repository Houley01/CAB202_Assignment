/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: trash.h              *
*********************************************
*/

// Fill the arry is make sure no rubbish is shown on screen.
void FillRubishArray();
// check if anything will be overlapping when rubbish is spawned
bool CheckToSeeIfTheSpaceIsClear(int x0, int y0, int width, int height, char object[]);
// Find a place to place rubish.
void FindASpot(int i, int XAxie[], int YAxie[], int width, int height, char Object[]);
// Master Function which gets called in main. The master function loops through Array for each rubbish catorgory and setup the location before being drawn.
void SetupRubish();
// Master Function which gets called in main to loop through and draws all rubbish.
void DrawAllRubish();
// Master Function which gets called in main which ask the user how much rubbish the user would like to have on screen.
void AskTheUserQuestionAboutRubish();

// ****************************************************************

// ************************* Trash ********************************

// Ask the user how much TRASH they would like in the simiulation.
void HowMuchTrash();
// Draw Trash one pieces of slime at x[i] y[i] depending on what i equals
void DrawTrash(int i);
// Goes through a for loop to try and find any empty spot for TRASH to be placed
void TrashSetup();
// Returns the number of Trash being displayed on screen
int ReturnNumberOfTrashOnScreen();
// Removes one piece of Trash from the counter.
void RemoveOneTrash();
// Adds one piece of Trash from the counter.
void AddOneTrash();
//  Return the value of what Max Trash equal too.
int ReturnMaxTrash();
// Return the value of what Trash Width equal too.
int ReturnTrashWidth();
// Return the value of what Trash Height equal too.
int ReturnTrashHeight();
// Return the value of what Trash Placement X array[i].
int ReturnTrashX(int i);
// Return the value of what Trash Placement Y array[i].
int ReturnTrashY(int i);
// Set the value for Trash Placement X array[i] = xAxis.
void SetTrashX(int i, int xAxis);
// Set the value for Trash Placement Y array[i] = YAxis.
void SetTrashY(int i, int yAxis);

// ****************************************************************

// ************************* SLIME *********************************

// Ask the user how much SLIME they would like in the simiulation.
void HowMuchSlime();
// Draw Slime one pieces of slime at x[i] y[i] depending on what i equals
void DrawSlime(int i);
// Goes through a for loop to try and find any empty spot for Slime to be placed
void SlimeSetup();
// Returns the number of Slime being displayed on screen
int ReturnNumberOfSlimeOnScreen();
// Removes one piece of Slime from the counter.
void RemoveOneSlime();
// Add one piece of Slime from the counter.
void AddOneSlime();
//  Return the value of what Max Slime equal too.
int ReturnMaxSlime();
// Return the value of what Slime Width equal too.
int ReturnSlimeWidth();
// Return the value of what Slime Height equal too.
int ReturnSlimeHeight();
// Return the value of what Slime Placement X array[i].
int ReturnSlimeX(int i);
// Return the value of what Slime Placement Y array[i].
int ReturnSlimeY(int i);
// Set the value for Slime Placement X array[i] = xAxis.
void SetSlimeX(int i, int xAxis);
// Set the value for Slime Placement Y array[i] = YAxis.
void SetSlimeY(int i, int yAxis);

// ****************************************************************

// ************************* DUST *********************************

// Ask the user how much DUST they would like in the simiulation.
void HowMuchDust();
// Draw Dust one pieces of Dust at x[i] y[i] depending on what i equals
void DrawDust(int i);
// Goes through a for loop to try and find any empty spot for dust to be placed
void DustSetup();
// Returns the number of Dust being displayed on screen
int ReturnNumberOfDustOnScreen();
// Removes one piece of Dust from the counter.
void RemoveOneDust();
// Adds one piece of Dust from the counter.
void AddOneDust();
//  Return the value of what Max Dust equal too.
int ReturnMaxDust();
// Return the value of what Dust Width equal too.
int ReturnDustWidth();
// Return the value of what Dust Height equal too.
int ReturnDustHeight();
// Return the value of what Dust Placement X array[i].
int ReturnDustX(int i);
// Return the value of what Dust Placement Y array[i].
int ReturnDustY(int i);
// Set the value for Dust Placement X array[i] = xAxis.
void SetDustX(int i, int xAxis);
// Set the value for Dust Placement Y array[i] = YAxis.
void SetDustY(int i, int yAxis);

// ******************************************************************

bool CheckForWalls(int xLocation, int yLocation, int width, int height);
//
bool IfStatementForDropingRubbish(int numberOfItems, int maxNumberOfObjects, int xAxisArray[], int yAxisArray[], int objectWidth, int objectHeight);
// Cheats for dropping rubbish Items
void DropRubish(char key);