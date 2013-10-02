/**************************************************************
Problem

The Latin alphabet contains 26 characters and telephones only 
have ten digits on the keypad. We would like to make it 
easier to write a message to your friend using a sequence of 
keypresses to indicate the desired characters. The letters are 
mapped onto the digits as shown below. To insert the character 
B for instance, the program would press 22. In order to insert 
two characters in sequence from the same key, the user must pause
before pressing the key a second time. The space character ' ' 
should be printed to indicate a pause. For example, 2 2 indicates
AA whereas 22 indicates B.


Input

The first line of input gives the number of cases, N. N test cases 
follow. Each case is a line of text formatted as

desired_message
Each message will consist of only lowercase characters a-z and 
space characters ' '. Pressing zero emits a space.

Output

For each test case, output one line containing "Case #x: " followed
 by the message translated into the sequence of keypresses.

Limits

1 ≤ N ≤ 100.

Small dataset

1 ≤ length of message in characters ≤ 15.

Large dataset

1 ≤ length of message in characters ≤ 1000.
***************************************************************/
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

    // move cursor to end of file to 
    // determine file size
    fseek(file, 0, SEEK_END);
    int sz = ftell(file);

    // move cursor to beginning of file   
    fseek(file, 0, SEEK_SET);
    
    int f = 0;    
    
    // read # of test cases
    fscanf (file, "%d", &f);
    
    char *s = malloc(sizeof(char) * sz);
    
    int letters[27] = {
        0,      // space
        2,      // a
        22,     // b
        222,    // c
        3,      // d
        33,     // e
        333,    // f
        4,      // g
        44,     // h
        444,    // i
        5,      // j
        55,     // k
        555,    // l
        6,      // m
        66,     // n
        666,    // o
        7,      // p
        77,     // q
        777,    // r
        7777,   // s
        8,      // t
        88,     // u
        888,    // v
        9,      // w
        99,     // x
        999,    // y
        9999    // z
    };  
    
    // move cursor to new line
    // after reading # of test cases
    fseek(file, 1, SEEK_CUR);
    for(int i = 0, testcase = f; i < testcase; i++)
    {   
        // set string to 0
        int k = 0;
        memset(s, 0, sizeof(char) * sz);
        
        // read characters from file line by line
        // stop reading if new line character
        char a;
        while((a = fgetc(file)) != EOF)
        {            
            s[k] = a;
            k++;
            //printf("%c", a);
            
            if(a == '\n')
                break;
        }

        // previous character
        int previous = -1;
        
        // pointer to string        
        char* p = s;
        for (int j = 0, curr = 0; j < strlen(s) - 1; j++, p++)
        {   
            // if character is a space set curr to 0
            if(*p == 32)
                curr = 0;
            else 
                curr = (*p ^ ('z' & 'a'));  
            
            // if previous character is not set
            // set curr to previous
            if(previous == -1)
            {
                previous = curr;
                fprintf(wfile, "Case #%d: %d", i+1, letters[curr]);
                printf("Case #%d: %d", i+1, letters[curr]);
                continue;
            }
                        
            // get previous number
            int prev_number = letters[previous];
            while(prev_number > 9)
                prev_number %= 10;
            
            // get current number
            int curr_number = letters[curr];
            while(curr_number > 9)
                curr_number %= 10;
            
            // if previous number and current number are the same
            if(prev_number == curr_number)
            {
                fprintf(wfile, " ");
                printf(" ");
            }
            
            // print to file
            fprintf(wfile, "%d", letters[curr]);
            printf("%d", letters[curr]);
            previous = curr;
        }
        
        fprintf(wfile, "\n");
        printf("\n");
    }
    
    // close file
    fclose(file);
    fclose(wfile);
    free(s);
    return 0;
}
