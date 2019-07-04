#include <stdio.h>

void echo_char_code()
{
    int user_input_char_value;
    printf("Please enter a char value:");
    user_input_char_value = getchar();
    printf("\nThe character code of '%c' is %i.\n", user_input_char_value, user_input_char_value); // Print to screen the letter and its chacter Code

    return;
}
int main()
{
    echo_char_code();
    return 0;
}
