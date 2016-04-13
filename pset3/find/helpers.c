/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if ( value < 0 )
    return false;
    
    int start = 0;
    int end = n-1;
    
    while (start <= end)
    {
        int med_point = ( start + end ) / 2;
        if (values[med_point] == value)
            return true;
        else if (values[med_point] > value)
            end = med_point-1;
        else
            start = med_point+1;
            
    }
    
   return false;                                                                                                                                     {}
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int temp;
    for (int i = 0; i < n;i++)
    {
        int min_index = i;
        for(int j = i+1;j < n;j++)
        {
            if(values[min_index] > values[j])
            {
                min_index = j;   
            }
        }    
        temp = values[i];
        values[i] = values[min_index];
        values[min_index] = temp;
    }
    return;
}
