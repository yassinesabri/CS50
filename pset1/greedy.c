#include <stdio.h>
#include <math.h>
#include <cs50.h>

 int main(void)
 {
     float money;
     int cents,coins,remind;
     
     do
     {
         printf("0 hai! How much change is owed?\n");
         money = GetFloat();
     } while (money <= 0);

     cents= round(money*100);

     coins = cents / 25;
     remind = cents % 25;
     coins += remind / 10;
     remind %= 10;
     coins += remind / 5;
     remind %= 5;
     coins += remind/1;

     printf("%d\n",coins);

 }
