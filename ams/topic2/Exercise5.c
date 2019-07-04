#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  Declare an array called sample with capacity for 82 elements
//  of the default signed integer type.
int sample[82];

void roll_dice(void)
{
    //  Seed the random number generator with the value 896972.
    srand(896972);
    //  Generate 82 random values between 1 and 12 inclusive. To do
    //  this, use a counter-controlled loop which will visit every element of
    //  sample. The counter should start at zero, and the loop should continue
    //  while the counter is less than 82.
    for (int i = 0; i < 82; i++)
    {
        sample[i] = rand() % 12 + 1;
    }

    //  Generate a random value between 1 and 12 inclusive. Store this
    //  value in the current element of sample - that is, the element
    //  indexed by the loop counter.

    //  End the loop.
}

int main(void)
{
    roll_dice();

    // Display contents of array sample.
    for (int i = 0; i < 82; i++)
    {
        if (i > 0)
        {
            printf(",");
        }
        printf("%d", sample[i]);
    }

    printf("\n");

    return 0;
}
