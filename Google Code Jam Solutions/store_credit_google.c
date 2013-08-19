/*******************************************************************************
* Problem
*
* You receive a credit C at a local store and would like to buy two items. You first walk through the store and create a list L of all available items. From this list you would like to buy two items that add up to the entire value of the credit. The solution you provide will consist of the two integers indicating the positions of the items in your list (smaller number first).
*
* Input
*
* The first line of input gives the number of cases, N. N test cases follow. For each test case there will be:
*
* One line containing the value C, the amount of credit you have at the store.
* One line containing the value I, the number of items in the store.
* One line containing a space separated list of I integers. Each integer P indicates the price of an item in the store.
* Each test case will have exactly one solution.
* Output
*
* For each test case, output one line containing "Case #x: " followed by the indices of the two items whose price adds up to the store credit. The lower index should be output first.
*
* Limits
*
* 5 ≤ C ≤ 1000
* 1 ≤ P ≤ 1000
*
* Small dataset
*
* N = 10
* 3 ≤ I ≤ 100
*
* Large dataset
*
* N = 50
* 3 ≤ I ≤ 2000
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
    // return if arguments is < 3
    if(argc != 3)
        return 3;
    
    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // open file for writing
    FILE* wfile = fopen(argv[2], "w");
    if(file == NULL)
    {
        printf("Failed to open file");
        return 2;
    }

    // move cursor to beginning of file   
    fseek(file, 0, SEEK_SET);
    
    int f = 0;    
    
    // read first line of file
    fscanf (file, "%d", &f);
    
    for(int i = 0, test_cases = f; i < test_cases; i++)
    {            
        int credit = 0;
        fscanf(file, "%d", &credit); // read in credit
        
        int items = 0;
        fscanf(file, "%d", &items); // read in # of items
        
        int price[items];
        for(int j = 0; j < items; j++)
            fscanf(file, "%d", &price[j]); // read in the prices
        
        int first = 0; 
        int second = 0;        
        int found = false;   
        
        for(int k = 0; k < items; k++)
        {   
            int *curr = NULL; // pointer to current location
            curr = &price[k];
            
            for(int l = k+1; l < items; l++)
            {
                int *next = NULL; // pointer to next location
                next = &price[l];
                
                if((*curr + *next) == credit)
                {
                    first = k;
                    second = l;
                    found = !found;
                    break;
                }
            }
            
            // break out of loop when found
            if(found == true)
                break;
        }
        
        printf("Case #%d: %d %d\n", i+1, first+1, second+1);
        fprintf (wfile, "Case #%d: %d %d\n", i+1, first+1, second+1);
    }
    
    // close file
    fclose(file);
    fclose(wfile);
    return 0;
}
