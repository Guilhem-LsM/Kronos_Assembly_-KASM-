#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error_manager.h"
#include "token.h"
#include "file_manager.h"
#include "syntaxe_debugger.h"
#include "range_manager.h"
#include "assembly.h"
#include "machine_code.h"
#include "logisim_file_manager.h"

int main(int argc, char **argv)
{       
    char* input_path;
    char* output_path = "C:\\Users\\vvilh\\Documents\\KASM\\Kronos_Assembly_-KASM-\\output\\output.txt";
    //char* FILE_NAME = "\\output.txt";
    char* raw_program;
    struct token* token_list = tokenize(raw_program);
    struct machine_code machine_code;
    if(argc >= 2) //Check if there's the right number of arguments 
    {
        input_path = argv[1]; // Get the input path of the program
        //output_path = strdup(argv[2]); // Get the output path of the program
        //strcat(output_path, FILE_NAME);
    }
    else
    {
        error(_NO_PATH_, 0, 0, 0, 0, 0, "");
    }

    raw_program = get_program(input_path);
    debug_synthax(token_list);
    replace_instruction_index_by_memory_addresses(token_list);
    debug_range(token_list);
    machine_code = assembly(token_list);
    free(token_list);
    free_linked_token(token_list);
    generate_logisim_memory_file(machine_code, output_path);
    free_linked_token(machine_code);
    printf("Compilation Done !\n");
    return 0;
}

