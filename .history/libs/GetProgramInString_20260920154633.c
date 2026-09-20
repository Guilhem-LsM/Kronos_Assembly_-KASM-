#include <stdio.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        return "";
    }

    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        return "";
    }

    long size = ftell(fp);
    fclose(fp);

    printf("%ld", size);
    
    return "program";
}