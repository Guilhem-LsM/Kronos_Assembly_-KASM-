#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error_manager.h"
#include "machine_code.h"


static const char decimal_to_hexa_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static char* decimal_to_hexa(int decimal)
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

void generate_logisim_memory_file(struct machine_code machine_code, char* path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        error(_PROGRAM_FILE_NOT_FOUND_, 0, 0, 0, 0, 0, path); 
    }
    unsigned int line_counter = 0;
    unsigned int value_counter = 0;
    fprintf(file, "v3.0 hex words addressed\n");
    for(int i = 0; i < 2^16; i++)
    {   
        printf("u : %s\n", i);
        if(value_counter == 0)
        {
            char* string = decimal_to_hexa(16*line_counter);
            fprintf(file, "%s: ", string);
            free(string);
        }

        if(i < machine_code.size)
        {
            char* string = decimal_to_hexa(machine_code.binary[i]);
            fprintf(file, "%s ", string);
            free(string);
        }
        else
        {
            fprintf(file, "0000 ");
        }

        value_counter++;

        if(value_counter == 16)
        {
            fprintf(file, "\n");
            value_counter = 0;
            line_counter++;
        }
    }
}