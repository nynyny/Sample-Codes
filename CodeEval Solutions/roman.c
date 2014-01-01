/*******************************************************************************
*
* Challenge Description:
*
* Many persons are familiar with the Roman numerals for relatively small numbers. 
* The symbols I (capital i), V, X, L, C, D, and M represent the decimal values 
* 1, 5, 10, 50, 100, 500 and 1000 respectively. To represent other values, these symbols, 
* and multiples where necessary, are concatenated, with the smaller-valued symbols written 
* further to the right. For example, the number 3 is represented as III, and the value 73 
* is represented as LXXIII. The exceptions to this rule occur for numbers having units 
* values of 4 or 9, and for tens values of 40 or 90. For these cases, the Roman numeral
* representations are IV (4), IX (9), XL (40), and XC (90). So the Roman numeral 
* representations for 24, 39, 44, 49, and 94 are XXIV, XXXIX, XLIV, XLIX, and XCIV, 
* respectively. 
*
* Write a program to convert a cardinal number to a Roman numeral.
*
* Input sample:
*
* Your program should accept as its first argument a path to a filename. Input example is the following
*
* 159
* 296
* 3992
* Input numbers are in range [1, 3999]
*
*
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define ONE 1
#define TEN 10

// print Roman Numeral
void letters(int i)
{
    switch(i)
    {
        case 1:
            printf("I");
            break;
        case 5:
            printf("V");
            break;            
        case 10:
            printf("X");
            break;            
        case 50:
            printf("L");
            break;            
        case 100:
            printf("C");
            break;            
        case 500:
            printf("D");
            break;            
        case 1000:
            printf("M");
            break;            
        default:
            break;
    }
}

// convert arabic to roman numerals
void convert(int temp, int ones)
{

    // for multiples of 5
    if(temp % 5 == 0)
        letters(temp * ones);
    
    // I
    if(temp % 5 == 1)
    {
        if(temp == 1)
            letters(temp * ones);
        else
        {
            letters(ones * 5);
            letters(ones);
        }
    }
    
    // II & III    
    if(temp % 5 == 2 || temp % 5 == 3)
    {
        if(temp > 3)
            letters(ones * 5);
        
        for(int j = (temp % 5); j >= 1; j--)
            letters(ones);
    }   
    
    //  when number is 4 or 9   
    if(temp % 5 == 4)
    {
        letters(ones);
        if(temp % 10 == 4)
            letters(ones * 5);
        else
            letters(ones * 10);    
    }
}

int main(int argc, char* argv[])
{

    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }
    
    // move cursor to end of file to f
    // determine file size
    fseek(file, 0, SEEK_END);
    int sz = ftell(file);
     
    char* str = malloc(sizeof(int)*sz);
    if(str == NULL)
    {
        printf("Failed to allocate memory\n");
        return 2;
    }

    // move cursor to beginning of file   
    fseek(file, 0, SEEK_SET);  
    
    while(1)
    {      
        // get string from file
        fscanf (file, "%s", str);
        if(feof(file))
            break;

        // get the arabic number
        int arabic_length = strlen(str);        
        int ones = ONE;
        
        // determine the largest place value
        for(int i = arabic_length; i > ONE; i--)
            ones *= TEN;

        // string to integer
        int t = atoi(str);

        for(int j = arabic_length; j > 0; j--)
        {
            // arabic number / place value -- starting from the highest
            int temp = t;
            temp /= ones;
            
            // next place value
            t %= ones;
                        
            // convert arabic to roman numeral
            convert(temp, ones);
            ones /= TEN;
        }
        
        printf("\n");
    }
    
    // close file & free memory
    fclose(file);
    free(str);
    return 0;
}
