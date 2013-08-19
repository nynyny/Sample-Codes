/*********************************************************
Problem
You are given two vectors v1=(x1,x2,...,xn) and v2=(y1,y2,...,yn). 
The scalar product of these vectors is a single number, calculated 
as x1y1+x2y2+...+xnyn. Suppose you are allowed to permute the 
coordinates of each vector as you wish. Choose two permutations 
such that the scalar product of your two new vectors is the
smallest possible, and output that minimum scalar product.

Input
The first line of the input file contains integer number
T - the number of test cases. For each test case, the first 
line contains integer number n. The next two lines contain n
integers each, giving the coordinates of v1 and v2 respectively.

Output
For each test case, output a line

Case #X: Y
where X is the test case number, starting from 1, and Y is 
the minimum scalar product of all permutations of the 
two given vectors.

Limits
Small dataset
T = 1000
1 ≤ n ≤ 8
-1000 ≤ xi, yi ≤ 1000

Large dataset
T = 10
100 ≤ n ≤ 800
-100000 ≤ xi, yi ≤ 100000

Sample

Input               Output 
2                   Case #1: -25
3                   Case #2: 6
1 3 -5
-2 4 1
5
1 2 3 4 5
1 0 1 0 1

*********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc, char* argv[])
{
    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file for reading");
        return 1;
    }
    
    // open file for writing
    FILE* out = fopen(argv[2], "w");
    if(out == NULL)
    {
        printf("Failed to open file for writing");
        return 2;
    }
    
    // read first line of file
    int test_cases = 0;    
    fscanf (file, "%d\n", &test_cases);
    
    for(int t = 0; t < test_cases; t++)
    {
        int integers = 0;
        fscanf(file, "%d", &integers); // read in integer number
            
        long long v1[integers];
        for(int j = 0; j < integers; j++)
            fscanf(file, "%lld", &v1[j]); // read in first vector
        
        // sort v1 from smallest to largest
        for(int i = 0; i < integers; i++)
        {
            long long *c_ptr = &v1[i];
            for(int j = i + 1; j < integers; j++)
            {
                long long *n_ptr = &v1[j];
                if(*n_ptr < *c_ptr)
                {
                    long long temp = *n_ptr;
                    *n_ptr = *c_ptr;
                    *c_ptr = temp;
                }
            }
        }
        
        long long v2[integers];
        for(int j = 0; j < integers; j++)
            fscanf(file, "%lld", &v2[j]); // read in second vector        
        
        // sort v2 from largest to smallest
        for(int i = 0; i < integers; i++)
        {
            long long *c_ptr = &v2[i];
            for(int j = i + 1; j < integers; j++)
            {
                long long *n_ptr = &v2[j];
                if(*n_ptr > *c_ptr)
                {
                    long long temp = *n_ptr;
                    *n_ptr = *c_ptr;
                    *c_ptr = temp;
                }
            }
        }
        
        // determine the sum
        long long sum = 0;
        for(int i = 0; i < integers; i++)
            sum += (v1[i] * v2[i]);
        
        // write to out file
        printf("Case #%d: %lld\n", (t+1), sum);
        fprintf(out, "Case #%d: %lld\n", (t+1), sum);
    }
    
    // close read and write files
    fclose(out);
    fclose(file);    
    return 0;
}
