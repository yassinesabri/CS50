#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<ctype.h>

int main(int argc,string argv[])
{
   if (argc != 2 ) //check the number of arguments
    {
        printf("1\n"); // write "1" as an error
        return 1;
    }
   
   string num = argv[1]; 
   int key = atoi(num); //convert the key to int
   
   
   string data = GetString(); //take the data from the user
   
   for (int i=0,lenght=strlen(data);i < lenght;i++)
   {
        // minus 'A' (or 'a') to get the alphabet index and plus 'A' (or 'a') after to get back to ASCII value
        if(isupper(data[i]) && isalpha(data[i]))
            data[i] = ((data[i] - 'A' + key)% 26)+ 'A'; 
            
        if(islower(data[i]) && isalpha(data[i]))
            data[i] = ((data[i] - 'a' + key)% 26)+ 'a';
            
   }
   
   printf("%s\n",data);
   
   
}
