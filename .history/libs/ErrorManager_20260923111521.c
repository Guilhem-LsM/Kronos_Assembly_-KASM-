#include <stdio.h>
#include <stdlib.h>

enum errors_list 
{
    _Success_,
    _Program_File_Missing_
};

void Error(unsigned int index)
{
    switch (index)
    {
    case 1: // Program file not found 
        printf("ERROR %u : Program file not found", index);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    exit(1);
}