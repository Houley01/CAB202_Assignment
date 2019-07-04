#include <stdlib.h>
#include <math.h>
#include <cab202_graphics.h>
#include <cab202_timers.h>

//  Declare global variables.
bool game_over = false;
const char bomb = '@';
const char star = '*';
double star_postion[2] = {53, 5};
double speed = 0.35;
double bomb_postion_x, bomb_postion_y, dx, dy;
// Functions
void draw_all()
{
    clear_screen();
    draw_char(round(bomb_postion_x), round(bomb_postion_y), bomb); // Draw bomb
    draw_char(star_postion[0], star_postion[1], star);             // Draw star
    show_screen();
}
void bomb_setup()
{
    double t1, t2, d;
    bomb_postion_x = 9;
    bomb_postion_y = 19;
    t1 = 53 - 9;
    t2 = 5 - 19;
    d = sqrt(t1 * t1 + t2 * t2);
    dx = t1 * speed / d;
    dy = t2 * speed / d;
    draw_all();
}
void bomb_update()
{
    double new_bomb_postion_x, new_bomb_postion_y;
    // printf("dx: %lf\ndy: %lf\n", dx, dy);
    // printf("bomb_postion before updated x:%lf y: %lf \n", bomb_postion_x, bomb_postion_y);
    new_bomb_postion_x = (bomb_postion_x + dx);
    new_bomb_postion_y = (bomb_postion_y + dy);
    // printf("bomb_postion after updated x:%lf y: %lf \n\n", new_bomb_postion_x, new_bomb_postion_y);
    bomb_postion_x = new_bomb_postion_x;
    bomb_postion_y = new_bomb_postion_y;
    // printf("bomb_postion before updated x:%lf y: %lf \n", bomb_postion_x, bomb_postion_y);

    draw_all();
}

void setup(void)
{
    // Insert setup code here.
    bomb_setup();
    draw_all();
}

void loop(void)
{
    // Insert loop code here.
    if (game_over == false)
    {
        if ((round(bomb_postion_x) == 53) && (round(bomb_postion_y) == 5))
        {
            game_over = true;
        }
        else
        {
            bomb_update();
        }
    }
}

int main()
{
    // milliseconds sleep between calls to loop.
    const int DELAY = 10;

    setup_screen();
    setup();
    show_screen();

    while (!game_over)
    {
        loop();
        timer_pause(DELAY);
    }

    return 0;
}