#include <stdio.h>
#include "error_manager.h"

void generate_logisim_memory_fil(unsigned int* machine_code, char* path)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        error(_PROGRAM_FILE_NOT_FOUND_, 0, 0, 0, 0, 0, ""); 
    }
}