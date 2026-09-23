#include <stdio.h>
#include <stdlib.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "rb"); // Open the file in binary mode

    // Find the size of the file to allocate the right amount
    if (fp == NULL)
    {
        printf("ERROR : file not found");
        return "ERROR";
    }

    if (fseek(fp, 0L, SEEK_END) < 0) {
        fclose(fp);
        return "ERROR";
    }

    size_t size = ftell(fp) + 1; // Get the position of the cursor, so the size

    char *raw_program = malloc(size); // Create and allocate the right amount of memory on the heap 

    // Get the datas of the files in raw_program
    if (fseek(fp, 0, SEEK_SET) < 0) {
        fclose(fp);
        return "ERROR";
    }
    fread(raw_program, 1, size, fp);
    raw_program[size-1] = '\0'; // add a end to the string
    
    return raw_program;
}