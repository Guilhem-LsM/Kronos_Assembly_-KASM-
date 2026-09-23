#include <stdio.h>
#include <stdlib.h>
#include "GetProgramInString.h"

int main(int argc, char **argv)
{       
    char* path;
    char* raw_program;
    if(argc == 2) //Check if there's the right number of arguments 
    {
        path = argv[1]; // Get the patch of the program
    }
    else
    {
        printf("ERROR 1");
        return 1;
    }
    raw_program = GetProgramInString(path);
    free(raw_program);
    return 0;
}