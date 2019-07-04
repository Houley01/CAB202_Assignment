#include <stdio.h>

void count_chars()
{
    //  Declare an integer variable which will be used to count characters.
    //  Initialise the variable to zero.
    int length_of_text = 0;
    //  Enter a loop which continues indefinitely.
    // Read a single character code from standard input.
    for (size_t count = 0; getchar() != EOF; count++)
    {
        // If the character code is equal to EOF, break out of the loop.
        // printf("YOU made it to the loops"); Error Testing
        length_of_text++;
    }

    // Increment the counter by 1.
    // End the body of the loop.

    // Display the number of characters processed.
    printf("The document contains %d characters.\n", length_of_text);
}

int main()
{
    count_chars();
    return 0;
}
// Hello World !