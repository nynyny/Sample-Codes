/*******************************************************************************
*
*
* Challenge Description:
*
* You have a set of rows with names of famous writers encoded inside. Each row is 
* divided into 2 parts by pipe char (|). The first part has a writer's name. The 
* second part is a "key" to generate a name.
*
* Your goal is to go through each number in the key (numbers are separated by space) 
* left-to-right. Each number represents a position in the 1st part of a row. This way 
* you collect a writer's name which you have to output.
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

        char* sptr;
        sptr = strtok (str,"|\n");
        while(sptr != NULL)
        {
            push(sptr);
            sptr = strtok (NULL,"|\n");
        }
        
        // set temporary variables for the two halves
        char* position = pop();
        char* letters = pop();
        
        // print letters according to position
        int i = 0, offset = 0;
        while(sscanf(position, "%d%n", &i, &offset) == 1)
        {
            printf("%c", letters[i-1]);
            position += offset; // read next integer from string
        }
        
        printf("\n");
    } 
        
    // close file
    fclose(file);
    free(str);
    free(s.strings);
    return 0;
}
