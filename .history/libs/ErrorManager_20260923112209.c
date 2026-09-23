#include <stdio.h>
#include <stdlib.h>

void Error(unsigned int index)
{
    switch (index)
    {
    case 1: // Program file not found 
        printf("ERROR %u : Program file not found", index);
        break;

    case 2: // fseek() has failed
        printf("ERROR %u : fseek() has failed", index);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    exit(1);
}