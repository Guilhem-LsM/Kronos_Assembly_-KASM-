#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "token.h"
#include "machine_code.h"


#define NULL_ 0

static const int WORD_PER_INSTRUCTION[24] = {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 3, 2, 1, 2};

static const unsigned int ARGUMENT_POSITION_IN_BYTES[24][3] =
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
    {5, 0, NULL_},
    {5, 0, NULL_},
    {0, 0, NULL_},
    {0, NULL_, NULL_},                                                                                                                                                     
    {NULL_, NULL_, NULL_},
    {0, NULL_, NULL_},
};

static const unsigned int ARGUMENT_BYTE_NUMBER[24][3] =
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

static const unsigned int DEREFERENCING_BIT_POSITION[2][3] =
{
    {5,6,7},
    {11,12,NULL_}
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

struct machine_code assembly(struct token* token_list)
{
    struct machine_code machine_code;
    machine_code.size = calculate_machine_code_array_size(token_list);
    machine_code.binary = calloc(machine_code.size, sizeof(unsigned int));
    unsigned int* binary = machine_code.binary;
    unsigned int argument_counter = 0;
    int instruction_type = -1;
    while (token_list)
    {
        if(token_list->type == _KEYWORD_) // If the token type is a keyword
        {
            instruction_type = token_list->value;
            binary[0] = binary[0] | instruction_type;
        }
        else if(token_list->type != _INSTRUCTION_ENDING_) // If the token type is an argument
        {
            unsigned int value = token_list->value;
            if(token_list->type == _RAM_ADRESS_ || token_list->type == _REGISTER_ADRESS_)
            {
                value << 1;
                if(token_list->type == _RAM_ADRESS_){value++;}
            }

            value = value << ARGUMENT_POSITION_IN_BYTES[instruction_type][argument_counter];
            binary[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] 
            = binary[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] | value;

            if(token_list->is_dereference)
            {
                if(instruction_type <= 14)
                {
                    value = 1 << DEREFERENCING_BIT_POSITION[0][argument_counter];
                }
                else if(instruction_type == 16)
                {
                    value = 1 << 10;
                }
                else
                {
                    value = 1 << DEREFERENCING_BIT_POSITION[1][argument_counter];
                }

                binary[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] 
                    = binary[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] | value;
            }

            argument_counter++;
        }
        else
        {
            argument_counter = 0;
            binary += WORD_PER_INSTRUCTION[instruction_type];
            instruction_type = -1;
        }

        token_list = token_list->next;
    }
    return machine_code;
}

