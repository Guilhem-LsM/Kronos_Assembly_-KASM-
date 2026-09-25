#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "error_manager.h"

static const int WORD_PER_INSTRUCTION[24] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 1, 2};

int find_memory_adress_from_line_index(struct token* token_list, struct token* current_token, size_t instruction_index)
{   
    size_t adress_counter = 0;
    size_t instruction_index_counter = 0;
    struct token* token_ = token_list;
    while(instruction_index_counter < instruction_index)
    {
        if(!token_)
        {
            error(_INSTRUCTION_ADRESS_TOO_FAR_, current_token->line, current_token->char_, instruction_index_counter, 0, 0, "");
        }
        if(token_->type == _KEYWORD_)
        {
            instruction_index_counter++;
            adress_counter += WORD_PER_INSTRUCTION[token_->value];
        }
        token_ = token_->next;
    }
    return adress_counter;
}

void debug_range(struct token* token_list)
{
    struct token* token_ = token_list;
    while(token_)
    {   

        switch (token_->type)
        {
        case _VALUE_:
            if(token_->value < 0 || token_->value > 65535 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    65535,
                    token_->type,
                    ""
                );
            }
            break;

        case _REGISTER_ADRESS_:
            if(token_->value < 0 || token_->value > 31 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    31,
                    token_->type,
                    ""
                );
            }
            break;
        
        case _RAM_ADRESS_:
            if(token_->value < 0 || token_->value > 32767 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    32767,
                    token_->type,
                    ""
                );
            }
            break;
        
        case _INPUT_ADRESS_:
            if(token_->value < 0 || token_->value > 14 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    14,
                    token_->type,
                    ""
                );
            }
            break;
        
        case _OUTPUT_ADRESS_:
            if(token_->value < 0 || token_->value > 14 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    14,
                    token_->type,
                    ""
                );
            }
            break;

        case _LINE_ADRESS_:
            if(token_->value < 0 || token_->value > 14 )
            {
                error(
                    _VALUE_OUT_OF_RANGE_,
                    token_->line,
                    token_->char_,
                    0,
                    14,
                    token_->type,
                    ""
                );
            }
            break;

        default:
            break;
        }
        token_ = token_->next;
    }
} 