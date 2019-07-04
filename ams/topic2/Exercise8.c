#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

//  Declare Global variables here.
double term[31];
double term_mean, term_min = 999, term_max, term_sum;
int term_count;
void array_stats()
{
    term_count = 0;
    term_max = 0;
    term_min = 999;
    term_sum = 0;
    // term_mean = 0.1, term_min = 0.1, term_max = 0.1;
    while ((term_count < 31) && (1 == scanf("%lf", &term[term_count])))
    {
        if (term_min > term[term_count])
        {
            term_min = term[term_count];
        }
        if (term_max < term[term_count])
        {
            term_max = term[term_count];
        }
        term_count++;
    }

    for (int i = 0; i < term_count; i++)
    {
        term_sum = term_sum + term[i];
    }
    term_mean = term_sum / term_count;

    if (term_count == 0) // checks if any number data was entered if not set the varibles to 0
    {
        term_max = 0;
        term_min = 0;
        term_mean = 0;
    }
}

int main()
{
    // Simulate the test setup process.
    srand(time(NULL));
    for (int i = 0; i < 31; i++)
    {
        term[i] = rand();
    }
    term_count = rand();
    term_mean = rand();
    term_min = rand();
    term_max = rand();

    // Call submitted code.
    array_stats();

    // Display contents of array term.
    for (int i = 0; i < term_count; i++)
    {
        printf("%f ", term[i]);
    }

    printf("\n");
    printf("Item count: %d\n", term_count);
    printf("Item mean : %f\n", term_mean);
    printf("Item min  : %f\n", term_min);
    printf("Item max  : %f\n", term_max);

    return 0;
}
