/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: GameInformation.h    *
*********************************************
*/
bool ReturnGameInProgress();
int ReturnScore();
void AddToScore(int addPoints);
void CheatCustomScore(int userInput);
int ReturnLife();
void MinusOneFromLife();
void CheatCustomLife(int userInput);
bool ReturnPause();
void SwitchPauseState();
bool ReturnGameOver();
void SwitchGameOverState();
void SetupGameInformation();
double ReturnSpeed();
bool ReturnGameStartMessage();
void SetGameStartMessageTrue();