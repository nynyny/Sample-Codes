/*******************************************************************************
*
* CHALLENGE DESCRIPTION:
*
* Write a program implementing a stack inteface for integers.
* The interface should have 'push' and 'pop' functions. You will be asked to 'push' 
* a series of integers and then 'pop' and print out every alternate integer.
*
* INPUT SAMPLE:
*
* Your program should accept as its first argument a path to a filename containing 
* a series of space delimited integers, one per line. E.g.
*
* 1 2 3 4
* 10 -2 3 4
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

#define STACK_SIZE 10
#define TEST "test"

// stack container
typedef struct
{
    // dynamic storage for the elements in the stack
    int* numbers;
    // the number of elements currently in the stack
    int size;
    // the allocated capacity of the stack
    int capacity;
}
stack;

// global stack
stack s;

//push into stack
bool push(int value)
{
    if(s.size < s.capacity)
    {
        s.numbers[s.size++] = value;
        return true;
    }
    
    // double the capacity if size > capacity
    s.capacity <<= 1;
    s.numbers = realloc(s.numbers, s.capacity * sizeof(int));
    if(s.numbers == NULL)
    {
        printf("Realloc Failed");
        return false;
    }
    
    s.numbers[s.size++] = value;
    return true;
}

// pop from stack
int pop(void)
{
    if(s.size == 0)
        return -1;
    
    int top = s.numbers[s.size-1];
    s.size--;
    
    return top;
}


int main(int argc, char* argv[])
{

    // initialize the stack
    s.size = 0;
    s.capacity = STACK_SIZE;
    s.numbers = malloc(s.capacity * sizeof(int));

    // open file for reading
    FILE* file = fopen(argv[1], "r");
    if(file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }
    
    // move cursor to end of file to 
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
        fgets(str, INT_MAX, file);
        if(feof(file))
            break;

        // stack pointer
        char* sptr;
        sptr = strtok (str," \n");
        while(sptr != NULL)
        {
            // convert string to integer
            // then push into stack
            push(atoi(sptr));
            sptr = strtok (NULL," \t\n");
        }
        
        // print every alternate element
        for(int i = s.size; i > 0; i -= 2)
        {
            // print top of stack
            printf("%d", pop());
            
            // pop next element
            pop();
            
            // if end of stack
            if(s.size == 0)
                break;
            
            // otherwise print white space
            printf(" ");
        }
        
        printf("\n");
    }
    
    // free memory
    fclose(file);
    free(str);
    free(s.numbers);
    return 0;
}
