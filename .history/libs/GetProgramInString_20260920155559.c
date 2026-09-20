#include <stdio.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "rb");

    // Find the size of the file to allocate the right amount
    if (fp == NULL)
    {
        printf("ERROR : file not found");
        return "";
    }

    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        return "";
    }

    long size = ftell(fp);
    fclose(fp);

    char *raw_program = malloc(size); // Create and allocate the right amount of memory on the heap 
    
    return raw_program;
}