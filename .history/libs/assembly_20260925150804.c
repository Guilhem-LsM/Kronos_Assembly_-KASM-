#include <stdio.h>
#include "token.h"

static calculate_machine_code_array_size(struct token* token_list)
{
    struct token* token_ = token_list;
    while ((token_))
    {
        
        token_ = token_->next;
    }
    
}

unsigned int* assembly(struct token* token_list)
{
    
}

