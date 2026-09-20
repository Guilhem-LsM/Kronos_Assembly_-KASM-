#include <stdio.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "r");

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

    char *raw_program = malloc(size);
    
    return raw_program;
}