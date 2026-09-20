#include <stdio.h>
#include "GetProgramInString.h"

int main(int argc, char **argv)
{       
    char* path;
    char* program;

    if(argc == 1) //Check if there's the right number of arguments 
    {
        path = argv[1]; // Get the patch of the program
    }
    program = GetProgramInString(path);
    return 0;
}