#include <stdio.h>
#include <stdlib.h>
#include "ErrorManager.h"

char fe = 'n';

char* GetProgram(char* path)
{
    FILE *fp = fopen(path, "rb"); // Open the file in binary mode

    // Find the size of the file to allocate the right amount
    if (fp == NULL)
    {
        Error(PROGRAM_FILE_NOT_FOUND); 
    }

    if (fseek(fp, 0L, SEEK_END) < 0) 
    {
        fclose(fp);
        Error(FSEEK_FAILED); 
    }

    size_t size = ftell(fp) + 1; // Get the position of the cursor, so the size

    // Alocate the right size of memory
    char *raw_program = malloc(size); // Create and alloscate the right amount of memory on the heap 
    // Check if the malloc() failed
    if(!raw_program)
    {
        Error(MALLOC_FAILED);
    }

    // Get the datas of the files in raw_program
    if (fseek(fp, 0, SEEK_SET) < 0) 
    {
        fclose(fp);
        Error(FSEEK_FAILED); 
    }
    fread(raw_program, 1, size, fp);
    raw_program[size-1] = '\0'; // add a end to the string



    return raw_program;
}