#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[])
{
    // open file for reading
    FILE* f = fopen(argv[1], "r");
    if(f == NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    // move cursor to end of file to 
    // determine file size
    fseek(f, 0, SEEK_END);
    int sz = ftell(f);
     
    char* str = malloc(sizeof(char)*sz);
    if(str == NULL)
    {
        printf("Failed to allocate memory");
        return 2;
    }
    
    // move cursor to beginning of file   
    fseek(f, 0, SEEK_SET);
    
    while(1)
    {
        fgets(str, INT_MAX,f);
        if(feof(f))
            break;
        
        // convert all uppercase letters to lower
        for(int i=0; i < strlen(str); i++)
        {
            if(str[i]>= 'A' && str[i] <= 'Z')
                str[i] ^= ('a' - 'A');
        }
        
        printf("%s", str);
    }
    
    fclose(f);
    free(str);
    return 0;
}
