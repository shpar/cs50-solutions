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


// binary search helper function
bool binarySearch(int value, int left, int right, int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    return binarySearch(value, 0, n, values, n);
}

bool binarySearch(int value, int left, int right, int values[], int n)
{
    if (values[(right + left) / 2] == value)
    {
        return true;
    }
    else if (right < left)
    {
        return false;
    }
    else if (values[(right + left) / 2] < value)
    {
        return binarySearch(value, (right + left) / 2 + 1, right, values, n);
    }
    else
    {
        return binarySearch(value, left, (right + left) / 2 - 1, values, n);
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // insertion sort
    int replace = values[0];
    int index = 0;
    for (int i = 0; i < n; i++) 
    {
        replace = values[i];
        index = i;
        for (int j = i; j < n; j++)
        {
            if (values[j] < replace)
            {
                replace = values[j];
                index = j;
            }
        }
        values[index] = values[i];
        values[i] = replace;    
    }
    return;
}