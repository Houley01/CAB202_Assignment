/*
*********************************************
*        Student Name: Ethan Houley         *
*      Student Number: n10353950            *
*           File Name: spaceObjects.c       *
*********************************************
*/
void DrawAsteroid();
void DrawBoulder();
void DrawFragment();
void PlaceAsteroid();
void UpdateAsteroid();
int ReturnAsteroidLocationX(int i);
int ReturnAsteroidLocationY(int i);
int ReturnNumOfAsteroids();
int ReturnNumOfBoulders();
int ReturnNumOfFragments();

void SetupSpaceObjects();
void DrawSpaceObjects();
void CheckforSheild();
void CheckForBullet();

void CheckCollision();
void CheckWaveIsDone();