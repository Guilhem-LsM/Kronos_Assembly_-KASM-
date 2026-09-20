#include <stdio.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        return -1;
    }

    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        return -1;
    }

    long size = ftell(fp);
    fclose(fp);
    
    return "program";
}