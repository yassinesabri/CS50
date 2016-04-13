#include<stdio.h>
#include<cs50.h>

int main(void)
{
   char c=GetChar();
   printf("%c\n",c);
   c= ((c - 'A' + 2)% 26)+ 'A';
   printf("%c\n",c); 
}
