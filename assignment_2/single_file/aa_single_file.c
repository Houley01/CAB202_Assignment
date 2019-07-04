// ********* Standard Libaray *********
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// ********* CAB202 Libaray *********
#include <cpu_speed.h>
#include <graphics.h>
#include <macros.h>
#include "lcd.h"
#include "lcd_model.h"
#include "usb_serial.h"
#include "cab202_adc.h"
// ********* H file *********
#include "aa_single_file.h"
// Helpers

// Return the calculation of sin( angle given * PI / 180)
double ReturnSin(int angle)
{
    return sin(angle * M_PI / 180);
}

// Return the calculation of Cos( angle given * PI / 180)
double ReturnCos(int angle)
{
    return cos(angle * M_PI / 180);
}

// Drawing a string which is able to have different types of string included
void draw_formatted(int x, int y, char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 80, format, args);
    draw_string(x, y, buffer, FG_COLOUR);
}

// Time
#define FREQ 8000000.0
#define PRESCALE 256.0
#define TIMER_SCALE 256.0

double interval = 0;
uint32_t cycleCount;

ISR(TIMER0_OVF_vect)
{
    interval += TIMER_SCALE * PRESCALE / FREQ;
}

ISR(TIMER3_OVF_vect)
{
    cycleCount++;
}

void SetupTimer()
{
    // Timer 3
    TCCR3A = 0;
    TCCR3B = 2;
    TIMSK3 = 1;
}

double ReturnCycleCountTime()
{
    return (cycleCount * 65536.0 + TCNT3) * 8.0 / FREQ;
}

int ReturnSeconds()
{
    return fmod(ReturnCycleCountTime(), 60.0);
}

int ReturnMinutes()
{
    return floor(ReturnCycleCountTime() / 60);
}

void ResetGameTime()
{
    cycleCount = 0;
}

// Controls
// Joystick controls
void SetupFiveWayJoystick()
{
    CLEAR_BIT(DDRD, 1); // Switch C (UP): Fire plasma Gun
    CLEAR_BIT(DDRB, 1); // Switch B (LEFT): Move Left
    CLEAR_BIT(DDRD, 0); // Switch D (Right): Move Right
    CLEAR_BIT(DDRB, 7); // Switch A (DOWN): Move
    CLEAR_BIT(DDRB, 0); // Switch Center: Pause
}

void SetupTactileSwitch()
{
    // Tactlie Buttons
    CLEAR_BIT(DDRF, 6); // Switch 1
    CLEAR_BIT(DDRF, 5); // Switch 2
}

void setLEDs()
{
    SET_BIT(DDRB, 2);
    SET_BIT(DDRB, 3);
}

#define BIT(x) (1 << (x))
// Enable the reading of the thumbwheel
void SetupPWM()
{
    TC4H = 1023 >> 8;
    OCR4C = 1023 & 0xff;
    TCCR4A = BIT(COM4A1) | BIT(PWM4A);
    SET_BIT(DDRC, 7);
    TCCR4B = BIT(CS42) | BIT(CS41) | BIT(CS40);

    TCCR4D = 0;
}

void EnableTeensyInput()
{
    SetupFiveWayJoystick();
    SetupTactileSwitch();
    setLEDs();
    SetupPWM();
}

// Checks to see what inputs has been give to the teensy
// input from TeensyPewPew or through serial.
void KeyboardInput(int charCode)
{
    // If 'a' or 'd' are pased then change the direction
    ChangeStarFighterDirection(charCode);

    if (charCode == 'w' || BIT_IS_SET(PIND, 1)) // Fire Plasma Bolts
    {
        FirePlasmaGun();
    }
    if (charCode == 's' || BIT_IS_SET(PINB, 7)) // Show status
    {
        StatusDisplay();
    }
    if (charCode == 'r' || BIT_IS_SET(PINF, 6)) // Start Game Or Restart
    {
        SetFalseRunanimation();
        SwitchGameOverState();
        GameStatusSerial();
        SetupGameInformation();
    }
    if (charCode == 'p' || BIT_IS_SET(PINB, 0)) // Change Pause stats
    {
        SwitchPauseState();
        SetGameStartMessageTrue();
    }
    if (charCode == 'q' || BIT_IS_SET(PINF, 5)) // Quit
    {
        Quit();
    }
    if (charCode == 't') // Aim The Plasma Gun
    {
        // Have not attemped
    }
    if (charCode == 'm') // Set the speed of the game
    {
        // Have not attemped
    }
    if (charCode == 'l') // Set Number of Lifes
    {
        // Have not attemped
        // CheatCustomLife(userInput)
    }
    if (charCode == 'g') // Set Game Score
    {
        // Have not attemped
        // CheatCustomScore(userInput)
    }
    if (charCode == '?') // Print controls to PC
    {
        HelpScreen();
    }
    if (charCode == 'h') // Move the starfighter to X
    {
        // Have not attemped
    }
    if (charCode == 'j') // Place An Asteriod
    {
        // Have not attemped
    }
    if (charCode == 'k') // Place A Boulder
    {
        // Have not attemped
    }
    if (charCode == 'i') // Place A Fragment
    {
        // Have not attemped
    }
}

// Animation
bool RUNANIMATION = true;
void Animation()
{
    int TextAsteroidXAxis = LCD_X + 5, TextApocalypseXAxis = -65, TextSNumberXAxis = 30 + LCD_X;
    while (((RUNANIMATION == true)) && !BIT_IS_SET(PINF, 6))
    {
        KeyboardInput(usb_serial_getchar());
        clear_screen();
        draw_string(TextAsteroidXAxis, (LCD_Y / 2) - 9, "Asteroid", FG_COLOUR);
        draw_string(TextApocalypseXAxis, (LCD_Y / 2), "Apocalypse", FG_COLOUR);
        draw_string(TextSNumberXAxis, LCD_Y - 9, "n10353950", FG_COLOUR);

        TextAsteroidXAxis--;
        TextApocalypseXAxis++;
        TextSNumberXAxis--;

        // Checks to see if variable is greater then or equal to x
        if (TextAsteroidXAxis <= 22)
        {
            TextAsteroidXAxis = 22;
        }
        if (TextApocalypseXAxis >= 17)
        {
            TextApocalypseXAxis = 17;
        }
        if (TextSNumberXAxis <= 20)
        {
            TextSNumberXAxis = 20;
        }
        show_screen();

        // Reads the Pulse from the Potentiometer 0 (POT0)
        long POT0 = adc_read(0);

        ChangeBacklightLCD(1023 - POT0);
        // delay between loops
        _delay_ms(25);
    }
    RUNANIMATION = false;
    clear_screen();
}

bool ReturnRunAnimationBool()
{
    return RUNANIMATION;
}

void SetFalseRunanimation()
{
    RUNANIMATION = false;
}

// Collision Dection
// Bounding Box check to see if objects a is are overlaping object b
bool BoundingBox(
    double x0, double y0, int w0, int h0,
    double x1, double y1, int w1, int h1)
{
    int left0 = round(x0) - w0 / 2, right0 = left0 + w0 - 1;
    int left1 = round(x1) - w1 / 2, right1 = left1 + w1 - 1;

    int top0 = round(y0) - h0 / 2, bottom0 = top0 + h0 - 1;
    int top1 = round(y1) - h1 / 2, bottom1 = top1 + h1 - 1;

    if (right1 < left0 || right0 < left1)
    {
        return false;
    }
    if (bottom1 < top0 || bottom0 < top1)
    {
        return false;
    }

    return true;
}

// Pixel Level Collision checks to see if any pixel that is a 1 is overlaping with another pixel that is also 1
bool PixelCollision(int x0, int y0, int w0, int h0, uint8_t pixel0[], int x1, int y1, int w1, int h1, uint8_t pixel1[])
{
    for (int x = 0; x < (x0 + w0); x++) // X axie
    {
        for (int y = 0; y < (y0 + h0); y++) // y axie
        {

            if (x >= x0 && x < (x0 + w0) && y >= y0 && y < (y0 + h0) && pixel0[(x - x0) + (y - y0) * w0] != 0 &&
                x >= x1 && x < (x1 + w1) && y >= y1 && y < (y1 + h1) && pixel1[(x - x1) + (y - y1) * w1] != 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Game Information
bool PAUSED;
bool GAMEOVER;
bool GameStartMessage;
int Score;
int Life;

// ********* Score *********
int ReturnScore()
{
    return Score;
}

void AddToScore(int addPoints)
{
    Score += addPoints;
}

void CheatCustomScore(int userInput)
{
    Score = userInput;
}

// ********* Life *********

int ReturnLife()
{
    return Life;
}

void MinusOneFromLife()
{
    Life--;
}

void CheatCustomLife(int userInput)
{
    Life = userInput;
}

// ********* Pause *********

bool ReturnPause()
{
    return PAUSED;
}

void SwitchPauseState()
{
    PAUSED = !PAUSED;
}

// ********* Game Over *********

bool ReturnGameOver()
{
    return GAMEOVER;
}

void SwitchGameOverState()
{
    GAMEOVER = !GAMEOVER;
}

// ********* Game Start *********

bool ReturnGameStartMessage()
{
    return GameStartMessage;
}

void SetGameStartMessageTrue()
{
    GameStartMessage = true;
}

// ********* Game Infomation Setup *********

void SetupGameInformation()
{
    PAUSED = true;
    GAMEOVER = false;
    GameStartMessage = false;
    Score = 0;
    Life = 5;
}

// ********* Speed *********

double ReturnSpeed()
{
    return ((1023 - adc_read(1)) / 102.3) * 0.1;
}

// Screen
void ChangeBacklightLCD(int reading)
{
    TC4H = reading >> 8;
    OCR4A = reading & 0xff;
}

// Set the lcd up and set the contrast for the lcd.
void SetupTheLCD()
{
    int Contrast = 20; // This is just so I can see on my screen
    lcd_init(LCD_DEFAULT_CONTRAST);
    lcd_write(LCD_C, 0x21);            // Enable LCD extended command set
    lcd_write(LCD_C, 0x80 | Contrast); // Set LCD Vop (Contrast)
    lcd_write(LCD_C, 0x0C);            // LCD in normal mode.
    lcd_write(LCD_C, 0x20);            // Enable LCD basic command set
}

void Quit()
{
    clear_screen();
    lcd_write(LCD_C, 0x0d); //  Change the screen to inverse video mode
    draw_string((LCD_X / 2 - 20), LCD_Y / 2, "n10353950", BG_COLOUR);
    show_screen();
    while (1)
    {
    }
}

// Send the computer controls to putty/Other serial programs
void HelpScreen()
{
    char *helpInfomation =
        "\r\nControls \r\n 'a' – move spaceship left \r\n 'd' – move spaceship right  \r\n 'w' – fire plasma bolts  \r\n 's' – send /display status  \r\n 'r' – start / reset 'p' – pause  \r\n 'q' – quit 't' – set aim(-60 to 60)  \r\n 'm' – set speed(0 to 10)  \r\n 'l' – set life  \r\n 'g' – set score  \r\n '?' – print controls  \r\n 'h' – spaceship to coord  \r\n 'j' – asteroid to coord  \r\n 'k' – boulder to coord  \r\n 'i' – fragment to coord  \r\n\r\n ";
    usb_serial_send(helpInfomation);
}

char buff[120];

// Send the game information to putty/Other serial programs
// e.g. Time, Number of lifes, score, Number of Asteroids,
// Number of Boulders, Number of Fragements, Number of bullets,
// the angle of the Aim, Speed of the game
void GameStatusSerial()
{
    // sends a message to putty/Other serial programs Leting the user know the game is starting
    if (ReturnGameStartMessage() == false && ReturnGameOver() == false)
    {
        usb_serial_send("\n\rGame Start!\n\r");
        SetGameStartMessageTrue();
    }

    send_formatted(buff, sizeof(buff),
                   "\n\rTime: %02d:%02d\n\rLife: %d\n\rScore: %d\n\rAsteroid: %d\n\rBoulder: %d\n\rFragments: %d\n\rBolts: %d\n\rAim: %d\n\rSpeed: %f\n\n",
                   ReturnMinutes(), ReturnSeconds(), ReturnLife(), ReturnScore(),
                   ReturnNumOfAsteroids(), ReturnNumOfBoulders(), ReturnNumOfFragments(),
                   NumberOfBullets(), ReturnAim(), ReturnSpeed());
}

// When the user press down on the joystick or press 's' on the keyboard the game
// information is sent to the computer. If the game is pause the lcd will change
// to show a small amount of information on the lcd as well as send information to
// the computer
void StatusDisplay()
{
    GameStatusSerial();
    while (ReturnPause() == true)
    {
        clear_screen();
        draw_formatted(1, 0, buff, "Time: %02d:%02d", ReturnMinutes(), ReturnSeconds());
        draw_formatted(1, 10, buff, "Life: %d", ReturnLife());
        draw_formatted(1, 20, buff, "Score: %d", ReturnScore());
        show_screen();
        if (usb_serial_getchar() == 'p' || BIT_IS_SET(PINB, 0))
        {
            SwitchPauseState();
        }
    }
}

// If life is equal to 0 then LCD Screen will change a message will be sent
// to the computer with the current game information.
void GameOver()
{
    if (ReturnLife() <= 0)
    {
        // Change gameover to true
        SwitchGameOverState();
        clear_screen();

        draw_string(1, 10, "Game Over!", FG_COLOUR);
        show_screen();
        // Send a message to computer
        usb_serial_send("\n\rGame Over!\n\r");
        GameStatusSerial();

        // Fadeout the LCD from FULL to 0 over a period of time
        for (int i = 1023; i <= 0; i--)
        {
            ChangeBacklightLCD(i);
            _delay_ms(5);
        }

        // Turn on the LEDS
        SET_BIT(PORTB, 2);
        SET_BIT(PORTB, 3);

        // FadeIn the LCD from 0 to FULL over a period of time
        for (int i = 0; i <= 1023; i++)
        {
            ChangeBacklightLCD(i);
            _delay_ms(5);
        }
        _delay_ms(2000);

        // Turn Off the LEDS
        CLEAR_BIT(PORTB, 2);
        CLEAR_BIT(PORTB, 3);

        // Write to screen
        draw_string(1, 20, "To quit press 'q'", FG_COLOUR);
        draw_string(1, 30, "To reset press 'r'", FG_COLOUR);
        show_screen();

        // wait for the user to input if they want to play again of quit.
        while (ReturnGameOver() == true)
        {
            int testInput = usb_serial_getchar();
            KeyboardInput(testInput);
        }
    }
}
// Serail
void SerialSetup()
{
    // Set Timer 0 to overflow approx 122 times per second.
    TCCR0B |= 4;
    TIMSK0 = 1;

    // Enable interrupts.
    sei();
}

void usb_serial_send(char *message)
{
    // Cast to avoid "error: pointer targets in passing argument 1
    //	of 'usb_serial_write' differ in signedness"
    usb_serial_write((uint8_t *)message, strlen(message));
}

void send_formatted(char *buffer, int buffer_size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, buffer_size, format, args);
    usb_serial_write((uint8_t *)buffer, strlen(buffer));
}

char buffer[81];

int CheckForSerialInput()
{
    int16_t charCode = usb_serial_getchar();
    return charCode;
}

// Star fighter
// ****************************
#define starFighterWidth 9
#define starFighterHeight 7
int starFighterDirection;

// ********* Star Fighter *********

int starFighterX, starFighterY;

static uint8_t starFighterPixelMap[7] = {
    0b0001000, // 1
    0b1001001, // 2
    0b1001001, // 3
    0b1011101, // 4
    0b1111111, // 5
    0b1011101, // 6
    0b1000001, // 7
};

// DrawStarFighter: Goes though bit array to draw the StarFighter at
// given X and Y coordinates
void DrawStarFighter()
{
    for (int row = 0; row < 7; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(starFighterPixelMap[row], (column)) == 1)
            {
                draw_pixel(starFighterX + column, starFighterY + row, FG_COLOUR);
            }
        }
    }
}

// SetupStarFighter: Set the StarFighter at the start of the game
void SetupStarFighter()
{
    starFighterX = LCD_X / 2 - 5;
    starFighterY = LCD_Y - 7;
    starFighterDirection = 0;
}

// ChangeStarFighterDirection: Checks to see if the input from the computer or teensy match a movement.
void ChangeStarFighterDirection(char userInput)
{
    // -1 equal to left, 0 equal to stop, 1 equal to right

    // Checks to see if the starfiger is is not moving then change the direction to move left
    if ((BIT_IS_SET(PINB, 1) || userInput == 'a') && starFighterDirection == 0)
    {
        starFighterDirection = -1;
    }
    // Checks to see if the starfiger is is not moving then change the direction move right
    else if ((BIT_IS_SET(PIND, 0) || userInput == 'd') && starFighterDirection == 0)
    {
        starFighterDirection = 1;
    }
    // If the starfighter is motion stop it
    else if (((BIT_IS_SET(PINB, 1) || userInput == 'a') && starFighterDirection == 1) ||
             ((BIT_IS_SET(PIND, 0) || userInput == 'd') && starFighterDirection == -1))
    {
        starFighterDirection = 0;
    }
    if (starFighterX + 1 >= LCD_X - starFighterWidth)
    {
        starFighterDirection = 0;
        starFighterX--;
    }
    if (starFighterX - 1 <= 0)
    {
        starFighterDirection = 0;
        starFighterX++;
    }
}

// UpdatedStarFighter: Check to see if the starFighterDirection equal to
// a value if so move in the direction
void UpdatedStarFighter()
{
    ChangeStarFighterDirection(0);
    if (starFighterDirection == -1)
    {
        starFighterX--;
    }
    else if (starFighterDirection == 1)
    {
        starFighterX++;
    }
}

int ReturnStarFighterDirection()
{
    return starFighterDirection;
}

int ReturnStarFighterX()
{
    return starFighterX;
}

int ReturnStarFighterY()
{
    return starFighterY;
}

// ********************************

#define max_bullet 20

uint8_t bulletPixelMap[2] = {
    0b0011000,
    0b0011000};

double bulletLocation[max_bullet][3];
long aimReader;

// UpdatedAim: Reads the left thumbwheel and produce and angle for which way
// the bullets fire from -60 to +60
void UpdatedAim()
{
    // 8.525 x 120 = 1023
    aimReader = (adc_read(0) / 8.525);
    if (aimReader >= 61) // Left
    {
        aimReader = aimReader % 61;
    }
    else if (aimReader <= 60) // Right
    {
        aimReader = -60 - (-aimReader % 61);
    }
}

int ReturnAim()
{
    return aimReader;
}

// SetupBullet: sets the bullets up so that all the bullets are off screen
// at the start of the game
void SetupBullet()
{
    for (int row = 0; row < max_bullet; row++)
    {
        for (int i = 0; i < 3; i++)
        {
            bulletLocation[row][i] = -10;
        }
    }
}

// DrawBullet: Loop though array and draw the bullets to the lcd
void DrawBullet()
{
    for (int i = 0; i < max_bullet; i++)
    {
        for (int row = 0; row < 2; row++)
        {
            for (int column = 0; column < 7; column++)
            {
                if (BIT_VALUE(bulletPixelMap[row], (column)) == 1)
                {
                    draw_pixel(bulletLocation[i][0] + column, bulletLocation[i][1] + row, FG_COLOUR);
                }
            }
        }
    }
}

// NumberOfBullets: Return the number of bullets are on screen.
int NumberOfBullets()
{
    int NumberOfBullets = 0;
    for (int i = 0; i < max_bullet; i++)
    {
        if (bulletLocation[i][1] <= 0)
        {
            NumberOfBullets++;
        }
    }
    return NumberOfBullets = max_bullet - NumberOfBullets;
}

// FirePlasmaGun: If joystick up or 'w' is press fire a bullet, set the x and y at the starfighter
void FirePlasmaGun()
{
    double lastFired = 0;
    for (int i = 0; i < max_bullet; i++)
    {
        // Go through the array and end the loop after finding a
        // location where the bullet is off screen.

        if ((bulletLocation[i][1] < 0 || bulletLocation[i][0] < 0 || bulletLocation[i][0] > LCD_X) && ReturnCycleCountTime() > lastFired)
        {
            bulletLocation[i][0] = starFighterX;
            bulletLocation[i][1] = starFighterY;
            bulletLocation[i][2] = (360 + aimReader) % 360;
            lastFired = ReturnCycleCountTime() + 100;
            break;
        }
    }
}

// UpdatedBullet: Calculate each movement the bullet makes on screen.
void UpdatedBullet()
{
    for (int i = 0; i < max_bullet; i++)
    {
        // bullet location = bulletLocation - (speed * SIN/COS( angle * PI / 180))
        bulletLocation[i][0] -= 0.8 * ReturnSin(bulletLocation[i][2]); // X
        bulletLocation[i][1] -= 0.8 * ReturnCos(bulletLocation[i][2]); // Y
    }
}

double ReturnBulletLocationX(int i)
{
    return bulletLocation[i][0];
}

double ReturnBulletLocationY(int i)
{
    return bulletLocation[i][1];
}

void SetBulletLocationX(int i, int set)
{
    bulletLocation[i][0] = set;
}

void SetBulletLocationY(int i, int set)
{
    bulletLocation[i][1] = set;
}

// Space Objects

// ********* Possible Point *********
#define scorePointAseroid 1
#define scorePointBoulder 2
#define scorePointFragement 4

// ********* Asteroid *********

#define asteroid_size 7
#define max_asteroid 3
double asteroidLocation[max_asteroid][3];

static uint8_t asteroidPixelMap[7] =
    {
        0b0001000, // 1
        0b0011100, // 2
        0b0111110, // 3
        0b1111111, // 4
        0b0111110, // 5
        0b0011100, // 6
        0b0001000  // 7
};

// DrawAsteroid: Goes though bit array to draw the asteroid at
// given X and Y coordinates
void DrawAsteroid(int i)
{
    for (int row = 0; row < 7; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(asteroidPixelMap[row], (column)) == 1)
            {
                draw_pixel(asteroidLocation[i][0] + column, asteroidLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

int ReturnAsteroidLocationX(int i)
{
    return asteroidLocation[i][0];
}

int ReturnAsteroidLocationY(int i)
{
    return asteroidLocation[i][1];
}

// ReturnNumOfAsteroids: Counts the number of astroids are on the
// screen, or about to move on to the screen.
int ReturnNumOfAsteroids()
{
    int count = 0;
    for (int i = 0; i < max_asteroid; i++)
    {
        if (asteroidLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_asteroid - count;
}

// ********* Boulder *********
#define boulder_size 5
#define max_boulder 6
// Max number of boulder is 6
int boulderLocation[max_boulder][3];

int boulderPixelMap[5] = {
    0b0001000,  // 1
    0b0011100,  // 2
    0b0111110,  // 3
    0b0011100,  // 4
    0b0001000}; // 5

// DrawBoulder: Goes though bit array to draw the boulder at
// given X and Y coordinates
void DrawBoulder(int i)
{
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(boulderPixelMap[row], (column)) == 1)
            {
                draw_pixel(boulderLocation[i][0] + column, boulderLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

// ReturnNumOfBoulders: Counts the number of boulder are on the screen,
// or about to move on to the screen.
int ReturnNumOfBoulders()
{
    int count = 0;
    for (int i = 0; i < max_boulder; i++)
    {
        if (boulderLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_boulder - count;
}

int ReturnBoulderLocationX(int i)
{
    return boulderLocation[i][0];
}

int ReturnBoulderLocationY(int i)
{
    return boulderLocation[i][1];
}

// ********* Fragment *********
// Max number of fragment is 12
#define fragment_size 3
#define max_fragments 12

int fragmentLocation[max_fragments][2];

int fragmentPixelMap[3] =
    {
        0b0001000,
        0b0011100,
        0b0001000};

// DrawBoulder: Goes though bit array to draw the fragment at
// given X and Y coordinates
void DrawFragment(int i)
{
    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 7; column++)
        {
            if (BIT_VALUE(fragmentPixelMap[row], (column)) == 1)
            {
                draw_pixel(fragmentLocation[i][0] + column, fragmentLocation[i][1] + row, FG_COLOUR);
            }
        }
    }
}

// ReturnNumOfFragments: Counts the number of fragments are on the screen, or about to move on to the screen.
int ReturnNumOfFragments()
{
    int count = 0;
    for (int i = 0; i < max_fragments; i++)
    {
        if (fragmentLocation[i][0] < 0)
        {
            count++;
        }
    }
    return max_fragments - count;
}

int ReturnFragmentLocationX(int i)
{
    return fragmentLocation[i][0];
}

int ReturnFragmentLocationY(int i)
{
    return fragmentLocation[i][1];
}

// ********* Placement *********
// PlaceAsteroid: Place 3 asteroids at a random x postion on lcd when a new wave is coming.
void PlaceAsteroid()
{
    for (int i = 0; i < 3; i++)
    {
        asteroidLocation[i][0] = rand() % (LCD_X - 1 - asteroid_size);
        asteroidLocation[i][1] = -10;
    }
}

// ********* Master Call *********
// UpdateAsteroid: Updates the current positon of the space object to move down the screen.
void UpdateAsteroid()
{
    for (int i = 0; i < 3; i++)
    {
        asteroidLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        asteroidLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
    for (int i = 0; i < max_boulder; i++)
    {
        boulderLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        boulderLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
    for (int i = 0; i < max_fragments; i++)
    {
        fragmentLocation[i][0] += ReturnSpeed() * ReturnSin(0); // x
        fragmentLocation[i][1] += ReturnSpeed() * ReturnCos(0); // y
    }
}

// SetupSpaceObjects: places all the objects of the screen when the game is first started.
void SetupSpaceObjects()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        asteroidLocation[i][0] = -LCD_X;
        asteroidLocation[i][1] = -LCD_Y;
        asteroidLocation[i][2] = 0;
    }
    for (int i = 0; i < max_boulder; i++)
    {
        boulderLocation[i][0] = -LCD_X;
        boulderLocation[i][1] = -LCD_Y;
        boulderLocation[i][2] = 0;
    }
    for (int i = 0; i < max_fragments; i++)
    {
        fragmentLocation[i][0] = -LCD_X;
        fragmentLocation[i][1] = -LCD_Y;
        fragmentLocation[i][2] = 0;
    }
}
// DrawSpaceObjects: loops through each of the space objects and draws them to the Teensy PewPew
void DrawSpaceObjects()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        DrawAsteroid(i);
    }
    for (int i = 0; i < max_boulder; i++)
    {
        DrawBoulder(i);
    }
    for (int i = 0; i < max_fragments; i++)
    {
        DrawFragment(i);
    }
}

// ********* Spilting of SpaceObjects *********

// void SpawnChild(int x, int y, int angle, int object)
// {
//     int findChild = 0;
//     if (object == 0)
//     {
//         // find 2 free child
//         for (int boulder = 0; boulder < max_boulder; boulder++)
//         {
//             if (boulderLocation[boulder][0] < 0)
//             {
//                 if (findChild == 0)
//                 {
//                     boulderLocation[boulder][0] = x - boulder_size;
//                     boulderLocation[boulder][1] = y;
//                     boulderLocation[boulder][2] = ((angle + 30) + 360) % 360;
//                     findChild++;
//                 }
//                 else if (findChild == 1)
//                 {
//                     boulderLocation[boulder][0] = x + boulder_size;
//                     boulderLocation[boulder][1] = y;
//                     boulderLocation[boulder][2] = ((angle - 30) + 360) % 360;
//                     break;
//                 }
//             }
//         }
//     }
//     if (object == 1)
//     {
//         // find 2 free child
//         for (int fragment = 0; fragment < max_fragments; fragment++)
//         {
//             if (fragmentLocation[fragment][0] < 0)
//             {
//                 if (findChild == 0)
//                 {
//                     fragmentLocation[fragment][0] = x - 5;
//                     fragmentLocation[fragment][1] = y;
//                     fragmentLocation[fragment][2] = ((angle + 30) + 360) % 360;
//                     findChild++;
//                     // break;
//                 }
//                 else if (findChild == 1)
//                 {
//                     fragmentLocation[fragment][0] = x + 5;
//                     fragmentLocation[fragment][1] = y;
//                     fragmentLocation[fragment][2] = ((angle - 30) + 360) % 360;
//                     break;
//                 }
//             }
//         }
//     }
// }

void SpawnBoulder(int asteriodNumber)
{
    if (asteriodNumber == 0)
    {
        /* Set the angle */
        // boulder 0
        boulderLocation[0][0] = asteroidLocation[0][0];
        boulderLocation[0][1] = asteroidLocation[0][1];
        // boulder 1
        boulderLocation[1][0] = asteroidLocation[0][0];
        boulderLocation[1][1] = asteroidLocation[0][1];
    }
    else if (asteriodNumber == 1)
    {
        // boulder 2
        boulderLocation[2][0] = asteroidLocation[1][0];
        boulderLocation[2][1] = asteroidLocation[1][1];
        // boulder 3
        boulderLocation[3][0] = asteroidLocation[1][0];
        boulderLocation[3][1] = asteroidLocation[1][1];
    }
    else if (asteriodNumber == 2)
    {
        // boulder 4
        boulderLocation[4][0] = asteroidLocation[2][0];
        boulderLocation[4][1] = asteroidLocation[2][1];
        // boulder 5
        boulderLocation[5][0] = asteroidLocation[2][0];
        boulderLocation[5][1] = asteroidLocation[2][1];
    }
}

void SpawnFragment(int BoulderNumber)
{
    if (BoulderNumber == 0)
    {
        /* Set the angle */
        // fragment 0
        fragmentLocation[0][0] = boulderLocation[0][0];
        fragmentLocation[0][1] = boulderLocation[0][1];
        // fragment 1
        fragmentLocation[1][0] = boulderLocation[0][0];
        fragmentLocation[1][1] = boulderLocation[0][1];
    }
    else if (BoulderNumber == 1)
    {
        // fragment 2
        fragmentLocation[2][0] = boulderLocation[2][0];
        fragmentLocation[2][1] = boulderLocation[2][1];
        // fragment 3
        fragmentLocation[3][0] = boulderLocation[1][0];
        fragmentLocation[3][1] = boulderLocation[1][1];
    }
    else if (BoulderNumber == 2)
    {
        // fragment 4
        fragmentLocation[4][0] = boulderLocation[1][0];
        fragmentLocation[4][1] = boulderLocation[1][1];
        // fragment 5
        fragmentLocation[5][0] = boulderLocation[2][0];
        fragmentLocation[5][1] = boulderLocation[2][1];
    }
    else if (BoulderNumber == 3)
    {
        // fragment 6
        fragmentLocation[6][0] = boulderLocation[1][0];
        fragmentLocation[6][1] = boulderLocation[1][1];
        // fragment 7
        fragmentLocation[7][0] = boulderLocation[2][0];
        fragmentLocation[7][1] = boulderLocation[2][1];
    }
    else if (BoulderNumber == 4)
    {
        // fragment 8
        fragmentLocation[8][0] = boulderLocation[4][0];
        fragmentLocation[8][1] = boulderLocation[4][1];
        // fragment 9
        fragmentLocation[9][0] = boulderLocation[4][0];
        fragmentLocation[9][1] = boulderLocation[4][1];
    }
    else if (BoulderNumber == 5)
    {
        // fragment 10
        fragmentLocation[10][0] = boulderLocation[5][0];
        fragmentLocation[10][1] = boulderLocation[5][1];
        // fragment 11
        fragmentLocation[11][0] = boulderLocation[5][0];
        fragmentLocation[11][1] = boulderLocation[5][1];
    }
}

void SpawnChild(char firstLetter, int objectNumber)
{
    if (firstLetter == 'a')
    {
        SpawnBoulder(objectNumber);
    }
    else if (firstLetter == 'b')
    {
        SpawnFragment(objectNumber);
    }
}

// ********* Warrning Lights  *********
// WarrningLights: Alerts the user that a new wave is coming and which side will have
// more astroids come down.
void WarrningLights()
{
    int countLeft = 0, countRight = 0;
    for (int i = 0; i < max_asteroid; i++)
    {
        // Round the location down to the nearest int and check if it Less than the LCD_X / 2
        if (floor(ReturnAsteroidLocationX(i) + (asteroid_size / 2)) < (LCD_X / 2))
        {
            countLeft++;
        }
        // Round the location down to the nearest int and check if it great than the LCD_X / 2
        else if (floor(ReturnAsteroidLocationX(i) + (asteroid_size / 2)) > (LCD_X / 2))
        {
            countRight++;
        }
    }
    if (countLeft > countRight)
    {
        SET_BIT(PORTB, 2);
        CLEAR_BIT(PORTB, 2);
    }
    else if (countRight > countLeft)
    {
        SET_BIT(PORTB, 3);
    }
    _delay_ms(100);
    CLEAR_BIT(PORTB, 2);
    CLEAR_BIT(PORTB, 3);
}

// ********* Checking Collison *********

// CheckforSheild: Loop thought space object and check if any spaceobjects are touching the sheild.
// if space obect is touching remove 1 life
void CheckforSheild()
{
    for (int i = 0; i < max_asteroid; i++)
    {
        if ((floor(asteroidLocation[i][0]) >= 0 && floor(asteroidLocation[i][0]) <= LCD_X) && floor(asteroidLocation[i][1] + asteroid_size - 1) >= 39)
        {
            asteroidLocation[i][0] = -10;
            asteroidLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
    for (int i = 0; i < max_boulder; i++)
    {
        if ((floor(boulderLocation[i][0]) >= 0 && floor(boulderLocation[i][0]) <= LCD_X) && floor(boulderLocation[i][1] + boulder_size - 1) >= 39)
        {
            boulderLocation[i][0] = -10;
            boulderLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
    for (int i = 0; i < max_asteroid; i++)
    {
        if ((floor(fragmentLocation[i][0]) >= 0 && floor(fragmentLocation[i][0]) <= LCD_X) && floor(fragmentLocation[i][1] + fragment_size - 1) >= 39)
        {
            fragmentLocation[i][0] = -10;
            fragmentLocation[i][1] = -10;
            MinusOneFromLife();
        }
    }
}

uint8_t bullet[2] = {
    0b0011000,
    0b0011000};

// CheckForBullet: Loop thought space object and check if any of space objects are touching a bullet.
// and if space obect is touching a bullet add points to the score
void CheckForBullet()
{
    // Loop through 25 times
    for (int bulletArray = 0; bulletArray < 25; bulletArray++)
    {
        // Only check if the bullet is on the screen.
        if (floor(ReturnBulletLocationY(bulletArray)) > 0 &&
            floor(ReturnBulletLocationX(bulletArray)) > 0 &&
            floor(ReturnBulletLocationX(bulletArray)) < LCD_X)
        {
            for (int asteroid = 0; asteroid < max_asteroid; asteroid++)
            {
                // If the bullet is in the same box area as asteroid then check if the pixels are over laping
                if (BoundingBox(ReturnAsteroidLocationX(asteroid), ReturnAsteroidLocationY(asteroid), asteroid_size, asteroid_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the asteroid and add points to the score.
                    if (PixelCollision(ReturnAsteroidLocationX(asteroid), ReturnAsteroidLocationY(asteroid), asteroid_size, asteroid_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        // Replace the Asteroid with 2 Boulder
                        // SpawnChild(asteroidLocation[asteroid][0], asteroidLocation[asteroid][1], asteroidLocation[asteroid][2], 0);
                        SpawnChild('a', asteroid);
                        asteroidLocation[asteroid][0] = -10;
                        asteroidLocation[asteroid][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointAseroid);
                    }
                }
            }
            for (int boulder = 0; boulder < max_boulder; boulder++)
            {
                // If the bullet is in the same box area as boulder then check if the pixels are over laping
                if (BoundingBox(ReturnBoulderLocationX(boulder), ReturnBoulderLocationY(boulder), boulder_size, boulder_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the boulder and add points to the score.
                    if (PixelCollision(ReturnBoulderLocationX(boulder), ReturnBoulderLocationY(boulder), boulder_size, boulder_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        // Replace the Boulder with 2 Fragment
                        // SpawnChild(boulderLocation[boulder][0], boulderLocation[boulder][1], boulderLocation[boulder][2], 1);
                        SpawnChild('b', boulder);
                        boulderLocation[boulder][0] = -10;
                        boulderLocation[boulder][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointBoulder);
                    }
                }
            }
            for (int fragment = 0; fragment < max_fragments; fragment++)
            {
                // If the bullet is in the same box area as fragnent then check if the pixels are over laping
                if (BoundingBox(ReturnFragmentLocationX(fragment), ReturnFragmentLocationY(fragment), fragment_size, fragment_size,
                                ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2))
                {
                    // If the bullet is pixels are overlaping then remove the boulder and add points to the score.
                    if (PixelCollision(ReturnFragmentLocationX(fragment), ReturnFragmentLocationY(fragment), fragment_size, fragment_size, asteroidPixelMap,
                                       ReturnBulletLocationX(bulletArray), ReturnBulletLocationY(bulletArray), 7, 2, bullet))
                    {
                        fragmentLocation[fragment][0] = -10;
                        fragmentLocation[fragment][1] = -10;
                        SetBulletLocationX(bulletArray, -10);
                        SetBulletLocationY(bulletArray, -10);
                        AddToScore(scorePointFragement);
                    }
                }
            }
        }
    }
}

// CheckCollision: Master function to call any functions which have anything
// to do with collision dections
void CheckCollision()
{
    CheckforSheild();
    CheckForBullet();
}

// Spawn a new wave if all space objects are off the screen.
void CheckWaveIsDone()
{
    if (
        ReturnNumOfAsteroids() == 0 &&
        ReturnNumOfBoulders() == 0 &&
        ReturnNumOfFragments() == 0)
    {
        PlaceAsteroid();
        WarrningLights();
    }
}

//  Main
// ********* Deflector Shield *********

void DrawDeflectorShield()
{
    for (int i = 0; i < LCD_X + 1; i += 2)
    {
        draw_pixel(i, 39, FG_COLOUR);
    }
}

// DrawAll: function that is used to draw all the objects to
// the screen that are updated regular.
void DrawAll()
{
    clear_screen();
    DrawSpaceObjects();
    DrawDeflectorShield();
    DrawBullet();
    DrawStarFighter();
    show_screen();
}

// OnceOffSetup: Only need to be setup once, if the function is called
// twice it wipes any sets that have been done before.
void OnceOffSetup()
{
    set_clock_speed(CPU_8MHz);
    SetupTimer();
    SetupTheLCD();
    SerialSetup();
    usb_init();
    adc_init();
    EnableTeensyInput();
}

// setup: Set up all objects in the game.
void setup(void)
{
    Animation();
    SetupGameInformation();
    SetupSpaceObjects();
    SetupStarFighter();
    SetupBullet();
    PlaceAsteroid();
    ResetGameTime();
}

// loop:
void loop()
{
    int16_t charCode = CheckForSerialInput();
    KeyboardInput(charCode);
    if (BIT_IS_SET(PINF, 6) || charCode == 'r') // Switch 1 (Left Button) Start / Restart Game
    {
        setup();
    }
    if (ReturnPause() == false)
    {
        UpdateAsteroid();
        UpdatedStarFighter();
        UpdatedAim();
        UpdatedBullet();
    }
    CheckCollision();  // calls the function check for collision which checks to see if rubbish is in way.
    CheckWaveIsDone(); // Check to see if the wave in finished
    GameOver();
    DrawAll();
}

int main(void)
{
    srand(ReturnLife() + ReturnScore() + ReturnSeconds());
    if (ReturnRunAnimationBool() == true)
    {
        OnceOffSetup();
    }

    setup();
    while (ReturnGameOver() == false)
    {
        loop();
        _delay_ms(50);
    }
    return 0;
}
