#include <stdio.h>

void flag_multiples(void)
{
    //  Enter a counter controlled loop which starts at 46 and
    //  advances by increments of 1 up to and including 3732
    //  Send the current value of the counter to standard output as a
    //  decimal formatted integer.
    for(int count = 46; 3733 > count; count++)
    {
        if (count%7==0) {
            printf("%d <===\n", count);
        } else{
            printf("%d\n",count);
        }
        
    }
    
    //  If the current value of the counter is divisible by 7 then
    //  highlight the current line by sending the pattern " <==" to
    //  standard output.

    //  Send a linefeed to standard output.

    //  End loop.
}

int main(void)
{
    flag_multiples();
    return 0;
}
