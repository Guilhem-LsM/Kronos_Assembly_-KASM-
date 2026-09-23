#include <stdio.h>
#include <stdlib.h>
#include "ErrorManager.h"
#include "Tokenizer.h"
#include "FileManager.h"



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
        Error(NO_PATH);
    }
    raw_program = GetProgram(path);
    free(raw_program);
    return 0;
}

