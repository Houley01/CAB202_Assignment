#include <stdio.h>

void echo_char()
{
    int single_keyboard_input;
    printf("Please enter a single character:");
    single_keyboard_input = getchar();

    printf("\nYou entered the character '");
    putchar(single_keyboard_input);
    printf("'.\n");
    return;
}

int main()
{
    echo_char();
    return 0;
}
