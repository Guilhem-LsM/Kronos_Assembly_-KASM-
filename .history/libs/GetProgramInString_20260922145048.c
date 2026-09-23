#include <stdio.h>
#include <stdlib.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "rb"); // Open the file in binary mode

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

    long size = ftell(fp); // Get the position of the cursor, so the size

    char *raw_program = malloc(size); // Create and allocate the right amount of memory on the heap 

    // Get the datas of the files in raw_program
    if (fseek(fp, 0, SEEK_SET) < 0) {
        fclose(fp);
        return "";
    }

    fscanf(fp, "%s", raw_program);
    printf("%s", raw_program);
    printf("%i", ftell(fp));


    
    return raw_program;
}