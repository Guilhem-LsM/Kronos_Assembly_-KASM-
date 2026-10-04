#include <stdio.h>
#include "error_manager.h"

static const char decimal_to_hexa_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static char decimal_to_heaxa(int decimal)
{

}

void generate_logisim_memory_fil(unsigned int* machine_code, char* path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        error(_PROGRAM_FILE_NOT_FOUND_, 0, 0, 0, 0, 0, strcat(path, "output.exe")); 
    }

    
    for(int i = 1; i < 2^16; i++)
    {
        
    }
}