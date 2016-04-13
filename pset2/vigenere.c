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
   
   string key = argv[1];
    
   int k=strlen(key); //get the lenght of the key
   //check if the key contain only char
   for (int i=0;i < k;i++)
   {
        if ( !isalpha(key[i]))
        {
            printf("1");
            return 1;
        }
   }
   
   
   
   
   int index[k];
   
   //convert the ascii value of the key letters to their alphabet index
   for (int i=0;i < k;i++) 
   {
        if (isupper(key[i]))
            index[i] = key[i] - 'A';
        if (islower(key[i]))
            index[i] = key[i] - 'a';
   }
   
    string data = GetString(); //take the data from the user
   
   for (int i=0,j=0,lenght=strlen(data);i < lenght;i++)
   {
        if (j>= k)
            j=0;

        if (isalpha(data[i]))
        {
            // minus 'A' (or 'a') to get the alphabet index and plus 'A' (or 'a') after to get back to ASCII value
            
            if(isupper(data[i]))
            data[i] = ((data[i] - 'A' + index[j])% 26)+ 'A'; 
            
            if(islower(data[i]))
            data[i] = ((data[i] - 'a' + index[j])% 26)+ 'a';
            
            j++; // the "j" will increment only if data[i] is an alphabet
        }
        
            
   }
   
   printf("%s\n",data);
return 0;
   
}
