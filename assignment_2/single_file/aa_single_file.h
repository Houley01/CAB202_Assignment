//
double ReturnSin(int angle);
double ReturnCos(int angle);
void draw_formatted(int x, int y, char *buffer, const char *format, ...);
//
void SetupTimer();
double ReturnCycleCountTime();
int ReturnSeconds();
int ReturnMinutes();
void ResetGameTime();
//
void SetupFiveWayJoystick();
void SetupTactileSwitch();
void setLEDs();
void SetupPWM();
void EnableTeensyInput();
void KeyboardInput(int charCode);
//
void Animation();
bool ReturnRunAnimationBool();
void SetFalseRunanimation();
//
bool BoundingBox(
    double x0, double y0, int w0, int h0,
    double x1, double y1, int w1, int h1);
bool PixelCollision(int x0, int y0, int w0, int h0, uint8_t pixel0[], int x1, int y1, int w1, int h1, uint8_t pixel1[]);
//
int ReturnScore();
void AddToScore(int addPoints);
void CheatCustomScore(int userInput);
//
int ReturnLife();
void MinusOneFromLife();
void CheatCustomLife(int userInput);
//
bool ReturnPause();
void SwitchPauseState();
//
bool ReturnGameOver();
void SwitchGameOverState();
//
bool ReturnGameStartMessage();
void SetGameStartMessageTrue();
void SetupGameInformation();
//
double ReturnSpeed();
//
void ChangeBacklightLCD(int reading);
void SetupTheLCD();
//
void Quit();
void HelpScreen();
void GameStatusSerial();
void StatusDisplay();
void GameOver();
//
void SerialSetup();
void usb_serial_send(char *message);
void send_formatted(char *buffer, int buffer_size, const char *format, ...);
int CheckForSerialInput();
//
void DrawStarFighter();
void SetupStarFighter();
void ChangeStarFighterDirection(char userInput);
void UpdatedStarFighter();
int ReturnStarFighterDirection();
int ReturnStarFighterX();
int ReturnStarFighterY();
//
void UpdatedAim();
int ReturnAim();
void SetupBullet();
void DrawBullet();
int NumberOfBullets();
void FirePlasmaGun();
void UpdatedBullet();
double ReturnBulletLocationX(int i);
double ReturnBulletLocationY(int i);
void SetBulletLocationX(int i, int set);
void SetBulletLocationY(int i, int set);
//
void DrawAsteroid(int i);
int ReturnAsteroidLocationX(int i);
int ReturnAsteroidLocationY(int i);
int ReturnNumOfAsteroids();
//
void DrawBoulder(int i);
int ReturnNumOfBoulders();
int ReturnBoulderLocationX(int i);
int ReturnBoulderLocationY(int i);
//
void DrawFragment(int i);
int ReturnNumOfFragments();
int ReturnFragmentLocationX(int i);
int ReturnFragmentLocationY(int i);
//
void PlaceAsteroid();
void UpdateAsteroid();
void SetupSpaceObjects();
void DrawSpaceObjects();
//
void SpawnBoulder(int asteriodNumber);
void SpawnFragment(int BoulderNumber);
void SpawnChild(char firstLetter, int objectNumber);
//
void WarrningLights();
//
void CheckforSheild();
void CheckForBullet();
void CheckCollision();
//
void CheckWaveIsDone();
//
void DrawDeflectorShield();
void DrawAll();
