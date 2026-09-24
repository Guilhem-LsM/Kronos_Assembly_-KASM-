#include <stdio.h>
#include "tokenizer.h"
#include "error_manager.h"

void synthaxe_debug(struct token* token_list)
{

    unsigned int argument_counter = 0;
    int instruction_type = -1;

    struct token* current_token = token_list;
    do
    {
        if(instruction_type == -1 && current_token->type != _KEYWORD_)
        {
            error(_FIRST_T_NOT_K_, current_token->line, current_token->char_, 0, token_type_string[current_token->type]);
        }
        instruction_type = current_token->type;

    } while (current_token->next);
    
}