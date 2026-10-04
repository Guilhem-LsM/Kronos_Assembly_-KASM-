#include <stdio.h>
#include "error_manager.h"

void generate_logisim_memory_fil(unsigned int* machine_code, char* path)
{
    FILE *file = fopen(path, "w");
    if (file == NULL)
    {
        error(_PROGRAM_FILE_NOT_FOUND_, 0, 0, 0, 0, 0, path + "output.txt"); 
    }

    for(int i = 1; i < 2^16; i++)
    {
        
    }
    

}