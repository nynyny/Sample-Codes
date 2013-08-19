/*******************************************************************************
*
*
* Challenge Description:
*
* Given a positive integer, find the sum of its constituent digits.
*
*
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

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

    while(1)
    {
        fgets(str, INT_MAX, file);
        if(feof(file))
            break;
        
        int sum = 0;
        
        // add the individual digits together
        for(int i=0, length = strlen(str) - 1; i < length; i++)
        {
            if(!(str[i] >= 48 && str[i] <= 57))
            {
                printf("Test file contains non-numeric characters\n");
                return 3;
            }
            
            sum += str[i] ^ '0';
        }
        
        printf("%d\n", sum);
    }    
    
    // close file
    fclose(file);
    free(str);
    return 0;
}
