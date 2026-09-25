#include <stdio.h>
#include <stdlib.h>
#include "token.h"

#define NULL_ 0

static const int WORD_PER_INSTRUCTION[24] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 1, 2};

static const int ARGUMENT_POSITION_IN_BYTES[24][3] =
{
    {NULL_, NULL_, NULL_},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, NULL_},
    {5, 10, NULL_},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, NULL_},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, 0},
    {5, 10, 0},
    {0, 0, NULL_},
    {0, 0, NULL_},
    {0, NULL_, NULL_},
    {0, 0, NULL_},
    {0, 0, NULL_},
    {0, 0, NULL_},
    {0, NULL_, NULL_},
    {NULL_, NULL_, NULL_},
    {0, NULL_, NULL_},
};

static const int ARGUMENT_BYTE_NUMBER[24][3] =
{
    {NULL_, NULL_, NULL_},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, NULL_},
    {0, 0, NULL_},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, NULL_},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {0, 0, 1},
    {1, 2, NULL_},
    {0, 2, NULL_},
    {1, NULL_, NULL_}, 
    {0, 1, NULL_},
    {0, 1, NULL_},
    {1, 2, NULL_},
    {1, NULL_, NULL_},
    {NULL_, NULL_, NULL_},
    {1, NULL_, NULL_}
};

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
    unsigned int size = calculate_machine_code_array_size(token_list);
    unsigned int* machine_code = malloc(size*sizeof(unsigned int));
    unsigned int* machine_code_ = machine_code;
    unsigned int argument_counter = 0;
    int instruction_type = -1;
    while (token_list)
    {
        if(token_list->type == _KEYWORD_) // If the token type is a keyword
        {
            instruction_type = token_list->value;
        }
        else if(token_list->type != _INSTRUCTION_ENDING_) // If the token type is an argument
        {
            int value = token_list->value;
            if(token_list->type == _RAM_ADRESS_ || token_list->type == _REGISTER_ADRESS_)
            {
                value << 1;
                if(token_list->type == _RAM_ADRESS_){value++;}
            }

            value << ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter];
            machine_code_[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] | value;
            argument_counter++;
        }
        else
        {
            argument_counter = 0;
            machine_code_ += WORD_PER_INSTRUCTION[instruction_type];
            instruction_type = -1;
        }


        token_list = token_list->next;
    }
    printf("MACHINE CODE\n");
    for(int i = 0; i < size; i++)
    {
        printf("%i\n", machine_code[i]);
    }
}

