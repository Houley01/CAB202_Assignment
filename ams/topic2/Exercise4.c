#include <stdio.h>

void cab_202(void)
{
    for(int count = 46; 3736 > count; count++)
    {
        if (count % 7 == 0 && count % 13 !=0)
        {
            printf("CAB\n");
        }
        else if (count % 13 == 0 && count % 7 != 0)
        {
            printf("202\n");
        }
        else if ((count % 7 == 0) && (count % 13 == 0))
        {
            printf("CAB202\n");
        }
        else
        {
            printf("%d\n", count);
        }
    }
    
}

int main(void)
{
    cab_202();
    return 0;
}