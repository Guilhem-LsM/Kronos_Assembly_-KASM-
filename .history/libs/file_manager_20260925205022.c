#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "error_manager.h"

#define UNWANTED_CHARS_NUMBER 2

const char UNWANTED_CHARS[] = {'\n','\r'};

char* get_program(char* path)
{
    FILE *program = fopen(path, "rb"); // Open the file in binary mode

    // Find the size of the file to allocate the right amount
    if (program == NULL)
    {
        error(_PROGRAM_FILE_NOT_FOUND_, 0, 0, 0, 0, 0, path); 
    }

    if (fseek(program, 0L, SEEK_END) < 0) 
    {
        fclose(program);
        error(_FSEEK_FAILED_, 0, 0, 0, 0, 0, ""); 
    }

    size_t size = ftell(program) + 2; // Get the cursor position, which gives us the size. The +2 gives us the space we need to add a space, which is useful for the tokenizer, and a character indicating the end of the string

    // Alocate the right size of memory
    char *raw_program = malloc(size); // Create and alloscate the right amount of memory on the heap 
        // Check if the malloc() failed
    if(!raw_program)
    {
        error(_MALLOC_FAILED_, 0, 0, 0, 0, 0, "");
    }

    // Get the datas of the files in raw_program
    if (fseek(program, 0, SEEK_SET) < 0) 
    {
        fclose(file);
        error(_FSEEK_FAILED_, 0, 0, 0, 0, 0, ""); 
    }
    fread(raw_program, 1, size, program);
    raw_program[size-2] = ' ';  // add a separator char as the last char in the string, useful for the tokenizer
    raw_program[size-1] = '\0'; // add a end to the string

    fclose(program);
    return raw_program;
}