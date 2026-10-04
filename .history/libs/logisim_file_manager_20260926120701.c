#include <stdio.h>
#include <string.h>
#include "error_manager.h"


static const char decimal_to_hexa_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static char* decimal_to_heaxa(int decimal)
{
    char* hexadecimal = malloc(5*sizeof(char));
    for(int i = 0; i < 4; i++)
    {
        int mask = 15;
        int value = decimal;
        mask = mask << 4*i;
        value = value & mask;
        value = value >> 4*i;
        hexadecimal[3-i] = decimal_to_hexa_table[value];
    }
    hexadecimal[4] = '\0'; 
    return hexadecimal;
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