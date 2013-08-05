/*******************************************************************************
*
*
* Challenge Description:
* Credits: This problem appeared in the Facebook Hacker Cup 2013 Hackathon.
*
* When John was a little kid he didn't have much to do. There was no internet, 
* no Facebook, and no programs to hack on. So he did the only thing he could... 
* he evaluated the beauty of strings in a quest to discover the most beautiful 
* string in the world.
* Given a string s, little Johnny defined the beauty of the string as the sum of 
* the beauty of the letters in it.The beauty of each letter is an integer 
* between 1 and 26, inclusive, and no two letters have the same beauty. 
* Johnny doesn't care about whether letters are uppercase or lowercase, so that 
* doesn't affect the beauty of a letter. (Uppercase 'F' is exactly as beautiful 
* as lowercase 'f', for example.)
*
* You're a student writing a report on the youth of this famous hacker. You 
* found the string that Johnny considered most beautiful. What is the maximum
* possible beauty of this string?
*
*
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define LETTERS 26

// merge sort
void sort(int array[], int size)
{
    if(size < 2)
        return;
       
    int middle = floor(size / 2);
        
    int left[middle], right[size-middle];
    
    for(int i = 0; i < middle; i++)
        left[i] = array[i];
    for(int i = middle; i < size; i++)
        right[i - middle] = array[i];
        
    sort(left, middle);
    sort(right, (size - middle));
    
        
    int l_length = middle, r_length = size - middle;
    int *l = left, *r = right, *a = array;
    
    while(l_length > 0 || r_length > 0)
    {
        if(l_length > 0 && r_length > 0)
        {
            if(*l <= *r)
            {
                *a = *l;
                a++;
                l++;
                l_length--;
            }
            else 
            {
                *a = *r;
                a++;
                r++;
                r_length--;
            }
        }
        else if(r_length > 0)
        {
            *a = *r;
            a++;
            r++;
            r_length--;
        }
        else if(l_length > 0)
        {
            *a = *l;
            a++;
            l++;
            l_length--;            
        }
    }
}

int main(int argc, char* argv[])
{
    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // move cursor to end of file to 
    // determine file size
    fseek(file, 0, SEEK_END);
    int sz = ftell(file);
     
    char* str = malloc(sizeof(int)*sz);
    if(str == NULL)
    {
        printf("Failed to allocate memory");
        return 2;
    }

    // move cursor to beginning of file   
    fseek(file, 0, SEEK_SET);

    // initialize alphabet frequency array    
    int frequency[LETTERS] = {0};    
    
    while(1)
    {
        fgets(str, INT_MAX, file);
        if(feof(file))
            break;
        
        // count the frequency of each letter
        for(int i=0; i < strlen(str); i++)
        {
            if((str[i]>= 'A' && str[i] <= 'Z') || (str[i]>= 'a' && str[i] <= 'z'))
            {
                int letter;
                if(str[i]>= 'A' && str[i] <= 'Z')
                    letter = (str[i] ^ ('A' & 'Z')) - 1;
                else 
                    letter = (str[i] ^ ('a' & 'z')) - 1;
                    
                frequency[letter]++;
            }
        }
        
        int sum = 0;
        // sort array according to frequency
        sort(frequency, LETTERS);
        
        // calculate the beauty
        for(int i = 0; i < LETTERS; i++)
            sum += frequency[i] * (i+1);
        
        printf("%d\n", sum);
        
        // reset frequency
        memset (frequency, 0, sizeof(frequency));
    }
        
    // close file
    fclose(file);
    free(str);
    return 0;
}
