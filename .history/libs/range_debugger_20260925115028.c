#include "token.h"
#include "error_manager.h"

void debug_range(struct token* token_list)
{
    struct token* token_ = token_list;
    while(token_)
    {
        switch (token_->type)
        {
        case _VALUE_:
            if(token_->value < 0 || token_->value < 65535 )
            {
                error();
            }
            break;

        case _REGISTER_ADRESS_:
        
            break;
        
        case _RAM_ADRESS_:
        
            break;
        
        case _INPUT_ADRESS_:
        
            break;
        
        case _OUTPUT_ADRESS_:
        
            break;
        
        case _LINE_ADRESS_:
        
            break;
        
        default:
            break;
        }
    }
} 