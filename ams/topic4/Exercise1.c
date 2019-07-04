#include <cab202_graphics.h>
#include <cab202_timers.h>

//  Insert your solution here.
void draw_pixels(int left, int top, int width, int height, char bitmap[], bool space_is_transparent)
{
    for (int j = 0; j <= (height-1); j++)
    {
        for (int i = 0; i <= (width-1); i++)
        {
            if (bitmap[i+j*width] != ' ') {
                draw_char(left+i, top+j, bitmap[i+j*width]);
            }
            else if(space_is_transparent == false) {
                draw_char(left + i, top + j, ' ');
            }
            
        }
    }

}

char * cross =
"y   y"
" y y "
"  y  "
" y y "
"y   y"
;

char * plus =
"  z  "
"  z  "
"zzzzz"
"  z  "
"  z  "
;

int main(void) {
    setup_screen();
    int x0 = 21, y0 = 8, w0 = 5, h0 = 5;
    int x1 = 31, y1 = 18, w1 = 5, h1 = 5;

    while (true) {
        clear_screen();

        for (int x = 0; x < screen_width(); x++) {
            for (int y = 0; y < screen_height(); y++) {
                draw_char(x, y, '.');
            }
        }

        draw_pixels(x0, y0, w0, h0, cross, false);
        draw_pixels(x1, y1, w1, h1, plus, true);

        show_screen();

        int key = wait_char();

        if (key == '2') {
            y1++;
        }
        else if (key == '8') {
            y1--;
        }
        else if (key == '4') {
            x1--;
        }
        else if (key == '6') {
            x1++;
        }
        else if (key == 's') {
            y0++;
        }
        else if (key == 'w') {
            y0--;
        }
        else if (key == 'a') {
            x0--;
        }
        else if (key == 'd') {
            x0++;
        }
        else if (key == 'q') {
            break;
        }
    }

    return 0;
}