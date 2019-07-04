#include <stdlib.h>
#include <cab202_graphics.h>

void fill_rect(int leftmost, int upper, int rightmost, int lower, char display_char) {
    int vertical_diffents = 0;
    // int horizontal_diffents = 0;

        if ((rightmost - leftmost) + 1 < 1 || (lower - upper) + 1 < 1)
    {
        return;
    }
    // horizontal_diffents = rightmost - leftmost;
    vertical_diffents = lower - upper ;
    for(int i = 0; i <= vertical_diffents; i++)
    {
        draw_line(leftmost, upper + i, rightmost, upper + i, display_char);
    }
    
}

    int main(void)
{
    int l, t, r, b;
    char c;

    printf("Please enter the horizontal location of the left edge of the rectangle: ");
    scanf("%d", &l);

    printf("Please enter the vertical location of the top edge of the rectangle: ");
    scanf("%d", &t);

    printf("Please enter the horizontal location of the right edge of the rectangle: ");
    scanf("%d", &r);

    printf("Please enter the vertical location of the bottom edge of the rectangle: ");
    scanf("%d", &b);

    printf("Please enter the character used to draw the rectangle? ");
    scanf(" %c", &c);

    setup_screen();
    fill_rect(l, t, r, b, c);
    show_screen();
    wait_char();

    return 0;
}