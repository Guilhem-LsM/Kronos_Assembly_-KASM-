#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"
#include "token.h"
#include "file_manager.h"
#include "syntaxe_debugger.h"
#include "range_manager.h"
#include "assembly.h"

static const char decimal_to_hexa_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static char* decimal_to_heaxa(int decimal)
{
    char* hexadecimal = maloc(5*sizeof(char));
    for(int i = 0; i < 4; i++)
    {
        int mask = 15;
        int value = decimal;
        mask = mask << 4*i;
        value = value | mask;
        value = value >> 4*i;
        hexadecimal[3-i] = decimal_to_hexa_table[value];
    }
    hexadecimal[4] = '\0'; 
    return hexadecimal;
}

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
        error(_NO_PATH_, 0, 0, 0, 0, 0, "");
    }
    raw_program = get_program(path);
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

    unsigned int* machine_code;
    machine_code = assembly(token_list);
    free_linked_token(token_list);
    
    

    printf("Compilation Done !\n");
    printf("G / %s\n",decimal_to_heaxa(15));
    return 0;
}

