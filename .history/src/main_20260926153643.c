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
    if(argc == 3) //Check if there's the right number of arguments 
    {
        input_path = argv[1]; // Get the input path of the program
        output_path = strcat(argv[2], "\\output.txt"); // Get the output path of the program
    }
    else
    {
        error(_NO_PATH_, 0, 0, 0, 0, 0, "");
    }
    printf("a\n");
    raw_program = get_program(input_path);
    struct token* token_list = tokenize(raw_program);
    /*struct token* token_ = token_list;
    while(token_)
    {   
        print_token(token_);
        token_ = token_->next;
    } */
    printf("b\n");
    debug_synthax(token_list);
    printf("c\n");
    replace_instruction_index_by_memory_addresses(token_list);
    printf("d\n");
    debug_range(token_list);

    struct machine_code machine_code;
    machine_code = assembly(token_list);
    printf("e\n");
    free_linked_token(token_list);
    printf("f\n");
    //generate_logisim_memory_file(machine_code, output_path);
    
    printf("Compilation Done !\n");
    return 0;
}

