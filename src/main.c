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
    printf("Compilation Begin...\n");
    char* input_path;
    char* output_path = "C:\\Users\\vvilh\\Documents\\KASM\\Kronos_Assembly_-KASM-\\output\\output.txt";
    //char* FILE_NAME = "\\output.txt";
    char* raw_program;
    struct token* token_list;
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
    raw_program = get_program(input_path); // Get the program in a string

    token_list = tokenize(raw_program); // Tokenize the program and debug all the spelling and vocabulary errors

    debug_synthax(token_list); // Debug the synthaxs
    replace_instruction_index_by_memory_addresses(token_list); // Change the value of all the branching instruction
    debug_range(token_list); // Debug the value entered (range)

    machine_code = assembly(token_list); // Generate the binary

    generate_logisim_memory_file(machine_code, output_path); // Encode the binary in the format for Logisim ROM/RAM
    
    
    free(raw_program);
    free_linked_token(token_list);
    printf("i\n");
    printf("%p\n", machine_code.binary);
    free(machine_code.binary);
    printf("Compilation Done !\n");
    return 0;
}

 