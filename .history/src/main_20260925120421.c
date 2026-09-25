#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"
#include "token.h"
#include "file_manager.h"
#include "syntaxe_debugger.h"
#include "range_debugger.h"


const char* VALID_KEYWORD[21] =
{
    "_KEYWORD_",
    "_VALUE_",
    "_RAM_ADRESS_",
    "_REGISTER_ADRESS_",
    "_INPUT_ADRESS_",
    "_OUTPUT_ADRESS_",
    "_LINE_ADRESS_", 
    "_INSTRUCTION_ENDING_"
};

int main(int argc, char **argv)
{       
    char* path;
    char* raw_program;
    if(argc == 2) //Check if there's the right number of arguments 
    {
        path = argv[1]; // Get the patch of the program
    }
    else
    {
        error(_NO_PATH_, 0, 0, 0, 0, "");
    }
    raw_program = get_program(path);
    struct token* token_list = tokenize(raw_program);
    struct token* token_ = token_list;
    while(token_)
    {   
        print_token(token_);
        token_ = token_->next;
    } 
    
    debug_synthax(token_list);
    debug_range(token_list);

    printf("Compilation Done !");
    return 0;
}

