#include <stdio.h>
#include <stdlib.h>

//  Declare an array called val with capacity for 26 elements
//  of the default signed integer type.
int val[26];
int x, y, z;
void fibonacci(void)
{
    scanf("%d %d", &x, &y);
    // printf("X:%d\n Y:%d\n", x, y);
    val[0] = x;
    val[1] = y;
    //  Insert your solution here.
    for (int i = 2; i < 26; i++)
    {
        z = x + y;
        val[i] = z;
        x = y;
        y = z;
    }
}

int main(void)
{
    fibonacci();

    // Display contents of array val.
    for (int i = 0; i < 26; i++)
    {
        printf("%d\n", val[i]);
    }

    return 0;
}
