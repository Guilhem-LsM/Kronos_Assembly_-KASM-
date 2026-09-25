#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "error_manager.h"

static const int WORD_PER_INSTRUCTION[24] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 1, 2};

void debug_range(struct token* token_list)
{
    struct token* token_ = token_list;
    while(token_)
    {
        printf("%s\n",TOKEN_TYPE_STRING[token_->type])
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
        default:
            printf("\nHow tf did you get here ??\n");
            exit(1);
            break;
        }
        token_ = token_->next;
    }
} 