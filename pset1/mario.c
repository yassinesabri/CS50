#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height,i = 1,j = 1;
    
    do
    {
        printf("Height : ");
        height=GetInt();
    } while (height < 0 || height > 23);
    
    for (i = 1;i <= height; i++)
    {
        for (j = 1;j <= height-i ; j++)
            printf(" ");
        for (j = 1;j <= i+1 ; j++)
            printf("#");
        printf("\n");   
    }
}

