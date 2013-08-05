/*******************************************************************************
*
*
* Challenge Description:
* Given a decimal (base 10) number, print out its binary representation.
*
* Input sample:
* File containing positive whole decimal numbers, one per line.
*
*
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define STACK_SIZE 10

// stack container
typedef struct
{
    // dynamic storage for the elements in the stack
    int* strings;
    // the number of elements currently in the stack
    int size;
    // the allocated capacity of the stack
    int capacity;
}
stack;

// global stack
stack s;

//push into stack
bool push(int str)
{
    if(s.size < s.capacity)
    {
        s.strings[s.size++] = str;
        return true;
    }
    
    // double the capacity if size > capacity
    s.capacity <<= 1;
    s.strings = realloc(s.strings, s.capacity * sizeof(int));
    if(s.strings == NULL)
    {
        printf("Realloc Failed");
        return false;
    }
    
    s.strings[s.size++] = str;
    return true;
}

// pop from stack
int pop(void)
{
    if(s.size == 0)
        return -1;
    
    int top = s.strings[s.size-1];
    s.size--;
    
    return top;
}


int main(int argc, char* argv[])
{

    // initialize the stack
    s.size = 0;
    s.capacity = STACK_SIZE;
    s.strings = malloc(s.capacity * sizeof(int));

    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // move cursor to beginning of file   
    fseek(file, 0, SEEK_SET);
    
    while(1)
    {
        if(feof(file))
            break;
 
        int number = 0;
        // get string from file
        fscanf(file, "%d\n", &number);
        
        // keep dividing number by 2 until quotient is 1
        for(int dividend = number; dividend > 1;)
        {
            int temp = dividend % 2;
            push(temp);
            
            dividend >>= 1;
            
            if(dividend == 1)
                push(dividend);
        }
        
        while(s.size != 0)
            printf("%d", pop());
        
        printf("\n");
    } 
    // close file
    fclose(file);
    return 0;
}
