/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: starFighter.h        *
*********************************************
*/
void DrawStarFighter();
void SetupStarFighter();
void ChangeStarFighterDirection(char userInput);
void UpdatedStarFighter();
int ReturnStarFighterDirection();
int ReturnStarFighterX();
int ReturnStarFighterY();
void UpdatedAim();
void SetupBullet();
void DrawBullet();
int ReturnAim();
int NumberOfBullets();
void FirePlasmaGun();
void UpdatedBullet();
double ReturnBulletLocationX(int i);
double ReturnBulletLocationY(int i);
void SetBulletLocationX(int i, int set);
void SetBulletLocationY(int i, int set);
// static uint8_t starFighterPixelMapAim0[];