/**
 * helpers.c
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
    if(n <= 0){
        return false;
    }
    
    int end = n - 1, start = 0;
    
    while(start < end){
        if(value > values[(start + end) / 2]){
            start = (start + end) / 2 + 1;
        }
        else if(value  < values[(start + end)/2]){
            end = (start + end) / 2;
        }
        else return true;
    }
    
    if(values[start] == value){
        return true;
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    if(n > 0){
        int arr[65536] = {0} ;
        for(int iter = 0 ; iter  < n; iter ++){
            arr[values[iter]] += 1 ;
        }
        
        for(int iter = 0, index = 0; iter < n; index++){
            while(arr[index]){
                values[iter] = index;
                iter++ ;
                arr[index]--;
            }
            
        }
    }
    return;
}
