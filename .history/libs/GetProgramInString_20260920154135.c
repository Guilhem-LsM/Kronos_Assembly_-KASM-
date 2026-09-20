#include <stdio.h>

char* GetProgramInString(char* path)
{
    FILE *fp = fopen(path, "r");
    
    return "program";
}