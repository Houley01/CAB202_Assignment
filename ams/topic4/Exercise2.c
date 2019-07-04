#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Insert your solution here.
int get_opaque_coords(int left, int top, int width, int height, char bitmap[], int x[], int y[])
{
    int num = 0;

    for (int j = 0; j <= (height - 1); j++)
    {
        for (int i = 0; i <= (width - 1); i++)
        {
            if (bitmap[i + j * width] != ' ')
            {
                x[num] = (left + i);
                y[num] = (top + j);
                num++;
            }
        }
    }
    return num;
}

char *box =
    "xxxxxxx"
    "x     x"
    "xxxxxxx";

char *cross =
    "y   y"
    " y y "
    "  y  "
    " y y "
    "y   y";

char *zed =
    "zzzzz"
    "   z "
    "  z  "
    " z   "
    "zzzzz";

void print_points(char *label, int left, int top, int x[], int y[], int num_points)
{
    printf("Occupied screen points in %s, drawn at (%d,%d):\n", label, left, top);

    for (int i = 0; i < num_points; i++)
    {
        printf("\t%d\t%d\n", x[i], y[i]);
    }

    printf("\n");
}

#define MAX_ITEMS (100)

int main(void)
{
    // Guarantee that we can hold the pixels of the box
    assert(strlen(box) <= MAX_ITEMS);
    assert(7 * 3 <= MAX_ITEMS);

    // Guarantee that we can hold the pixels of the cross
    assert(strlen(cross) <= MAX_ITEMS);
    assert(5 * 5 <= MAX_ITEMS);

    // Guarantee that we can hold the pixels of the zed
    assert(strlen(zed) <= MAX_ITEMS);
    assert(5 * 5 <= MAX_ITEMS);

    // Reserve storage for results.
    int occupied_x[MAX_ITEMS];
    int occupied_y[MAX_ITEMS];
    int num_points;

    // Set up shapes andget results.
    srand(time(NULL));

    int left, top;

    left = rand() % 100;
    top = rand() % 100;

    num_points = get_opaque_coords(left, top, 7, 3, box, occupied_x, occupied_y);
    print_points("box", left, top, occupied_x, occupied_y, num_points);

    left = rand() % 100;
    top = rand() % 100;

    num_points = get_opaque_coords(left, top, 5, 5, cross, occupied_x, occupied_y);
    print_points("cross", left, top, occupied_x, occupied_y, num_points);

    left = rand() % 100;
    top = rand() % 100;

    num_points = get_opaque_coords(left, top, 5, 5, zed, occupied_x, occupied_y);
    print_points("zed", left, top, occupied_x, occupied_y, num_points);

    return 0;
}