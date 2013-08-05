/****************************************
* Challenge Description:
* Print the odd numbers from 1 to 99.
*****************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // if the least significant bit is set,
    // then the number is odd
    for(int i=0; i<100; i++)
        if((i & 1) == 1)
            printf("%d\n", i);
    
    return 0;
}
