#include <stdio.h>
#include "token.h"

static const int WORD_PER_INSTRUCTION[24] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 1, 2};

static size_t calculate_machine_code_array_size(struct token* token_list)
{
    struct token* token_ = token_list;
    size_t size = 0;
    while (token_)
    {
        if(token_->type == _KEYWORD_)
        {
            size += WORD_PER_INSTRUCTION[token_->value];
        }
        token_ = token_->next;
    }
    return size;
}

unsigned int* assembly(struct token* token_list)
{
    unsigned int* machine_code = malloc(calculate_machine_code_array_size(token_list)*sizeof(unsigned int));
    struct token argument_list[3];
    unsigned int argument_index = 0;
    int instruction_type = -1;
    while (token_list)
    {
        if(token_list->type == _KEYWORD_) // If the token type is a keyword
        {
            instruction_type = token_list->value;
        }
        else if(token_list->type != _INSTRUCTION_ENDING_) // If the token type is an argument
        {
            argument_list[argument_index] = *token_list; // If the token type is an instruction ending
        }
        else
        {

        }


        token_list = token_list->next;
    }
}

