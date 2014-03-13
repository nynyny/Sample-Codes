/*******************************************************************************
*
* You have received a text encoded with Morse code and want to decode it.
*
* INPUT SAMPLE:
*
* Your program should accept as its first argument a path to a filename. 
* Input example is the following:
*
* .- ...- ..--- .-- .... .. . -.-. -..-  ....- .....
* -... .... ...--
*
* Each letter is separated by space char, each word is separated by 2 space chars.
*
* OUTPUT SAMPLE:
*
* AV2WHIECX 45
* BH3
********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define LETTERS 26
#define DIGITS 10

int
main (int argc, char *argv[])
{

    // morse code for letters
    char *morse[LETTERS] = {

        ".-",                   // a
        "-...",                 // b
        "-.-.",                 // c
        "-..",                  // d
        ".",                    // e
        "..-.",                 // f
        "--.",                  // g
        "....",                 // h
        "..",                   // i
        ".---",                 // j
        "-.-",                  // k
        ".-..",                 // l
        "--",                   // m
        "-.",                   // n
        "---",                  // o
        ".--.",                 // p
        "--.-",                 // q
        ".-.",                  // r
        "...",                  // s
        "-",                    // t
        "..-",                  // u
        "...-",                 // v
        ".--",                  // w
        "-..-",                 // x
        "-.--",                 // y
        "--.."                  // z        
    };

    // morse code for digits
    char *digits[DIGITS] = {
        "-----",                 // 0
        ".----",                // 1
        "..---",                // 2
        "...--",                // 3
        "....-",                // 4
        ".....",                // 5
        "-....",                // 6
        "--...",                // 7
        "---..",                // 8
        "----."                 // 9
    };

    // open file for reading
    FILE *file = fopen (argv[1], "r");
    if (file == NULL)
    {
        printf ("Failed to open file\n");
        return 1;
    }

    // move cursor to end of file to 
    // determine file size
    fseek (file, 0, SEEK_END);
    int sz = ftell (file);

    char *str = malloc (sizeof (int) * sz);
    if (str == NULL)
    {
        printf ("Failed to allocate memory\n");
        return 2;
    }

    // move cursor to beginning of file   
    fseek (file, 0, SEEK_SET);

    // variable to store each individual morse letter
    char *s = malloc (sizeof (char) * sz);
    if (s == NULL)
        exit (3);

    // initialize variable
    memset (s, 0, sizeof (char) * 8);

    while (1)
    {
        // read-in line
        fgets (str, INT_MAX, file);
        if (feof (file))
            break;

        for (int i = 0, j = 0, space = 0; i <= strlen (str); i++)
        {

            // if space, null or newline character
            if (str[i] == 32 || str[i] == '\0' || str[i] == '\n')
            {
                ++space;
                if (space == 2)
                {
                    printf ("%c", 32);      // print space if two spaces in in-file
                    continue;
                }

                // check to see if its a letter
                for (int k = 0; k < LETTERS; k++)
                    if (strcmp (s, morse[k]) == 0)
                    {
                        printf ("%c", (k + 65));
                        continue;
                    }

                // check to see if its a digit
                for (int k = 0; k < DIGITS; k++)
                    if (strcmp (s, digits[k]) == 0)
                    {
                        printf ("%c", (k + 48));
                        continue;
                    }

                // clear memory
                memset (s, '\0', sizeof (char) * sz);
                j = 0;
            }

            // if string contains . or -
            if (str[i] == 45 || str[i] == 46)
            {
                s[j] = str[i];
                j++;
                space = 0;
                continue;
            }
        }

        printf ("\n");
    }

    // free allocated memory
    free (s);
    return 0;
}
