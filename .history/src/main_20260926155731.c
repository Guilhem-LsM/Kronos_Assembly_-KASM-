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
    char* output_path;
    char* raw_program;
    if(argc >= 3) //Check if there's the right number of arguments 
    {
        input_path = argv[1]; // Get the input path of the program
        //output_path = strdup(argv[2]); // Get the output path of the program
        output_path = strcat(output_path, "\\output.txt");
    }
    else
    {
        error(_NO_PATH_, 0, 0, 0, 0, 0, "");
    }
    raw_program = get_program(input_path);
    struct token* token_list = tokenize(raw_program);
    /*struct token* token_ = token_list;
    while(token_)
    {   
        print_token(token_);
        token_ = token_->next;
    } */
    debug_synthax(token_list);
    replace_instruction_index_by_memory_addresses(token_list);
    debug_range(token_list);

    struct machine_code machine_code;
    machine_code = assembly(token_list);
    free_linked_token(token_list);
    generate_logisim_memory_file(machine_code, output_path);
    
    printf("Compilation Done !\n");
    return 0;
}

