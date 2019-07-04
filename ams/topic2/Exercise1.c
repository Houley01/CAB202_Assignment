#include <stdio.h>

void list_integers(void)
{
    // Display the title message.
    printf("Listing integers between 73 and 376...\n");
    //  Enter a counter-controlled loop which will start at 73 and
    //  continues up to and including 376, advancing by increments of 1.
    for(int count = 73; count < 377; count++)
    {
        printf("%d\n", count);
    }
    
    //  Print the current value of the counter variable.

    // End the loop.
}
int main(void)
{
    list_integers();
    return 0;
}