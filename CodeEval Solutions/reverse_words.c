/*******************************************************************************
*
*
* Challenge Description:
*
* Write a program to reverse the words of an input sentence.
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
    char** strings;
    // the number of elements currently in the stack
    int size;
    // the allocated capacity of the stack
    int capacity;
}
stack;

// global stack
stack s;

//push into stack
bool push(char* str)
{
    if(s.size < s.capacity)
    {
        s.strings[s.size++] = str;
        return true;
    }
    
    // double the capacity if size > capacity
    s.capacity <<= 1;
    s.strings = realloc(s.strings, s.capacity * sizeof(char*));
    if(s.strings == NULL)
    {
        printf("Realloc Failed");
        return false;
    }
    
    s.strings[s.size++] = str;
    return true;
}

// pop from stack
char* pop(void)
{
    if(s.size == 0)
        return NULL;
    
    char* top = s.strings[s.size-1];
    s.size--;
    
    return top;
}

int main(int argc, char* argv[])
{

    // initialize the stack
    s.size = 0;
    s.capacity = STACK_SIZE;
    s.strings = malloc(s.capacity * sizeof(char*));

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
        // get string from file
        fgets(str, INT_MAX, file);
        if(feof(file))
            break;

        // stack pointer
        char* sptr;
        sptr = strtok (str," \n");
        while(sptr != NULL)
        {
            push(sptr);
            sptr = strtok (NULL," \t\n");
        }
        
        // print out string in reverse order with spaces in between
        for(int i = 0, height = s.size; i < (height + (height - 1)); i++)
        {
            if(i % 2 == 0)
                printf("%s", pop());
            else
                printf(" ");
        }
        
        printf("\n");
    }
        
    // close file
    fclose(file);
    free(str);
    return 0;
}
