#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <limits.h>

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

void print_binary(int num) {
    // Determine the number of bits in an integer (usually 32 bits)
    printf("0(");
    int total_bits = sizeof(int) * CHAR_BIT;
    
    // Flag to skip leading zeros for cleaner output
    int started = 0; 

    // Loop through each bit starting from the Most Significant Bit (MSB)
    for (int i = total_bits - 1; i >= 0; i--) {
        // Shift the number and check if the current bit is 1 or 0
        int bit = (num >> i) & 1;
        
        if (bit == 1) {
            started = 1; // Found the first non-zero bit
        }
        
        if (started) {
            printf("%d", bit);
        }
    }
    
    // If the number was 0, the loop prints nothing, so handle it here
    if (!started) {
        printf("0");
    }
    printf(")");
    printf("\n");
}


unsigned int* assembly(struct token* token_list)
{
    unsigned int size = calculate_machine_code_array_size(token_list);
    unsigned int* machine_code = calloc(size, sizeof(unsigned int));
    unsigned int* machine_code_ = machine_code;
    unsigned int argument_counter = 0;
    int instruction_type = -1;
    while (token_list)
    {
        if(token_list->type == _KEYWORD_) // If the token type is a keyword
        {
            instruction_type = token_list->value;
            machine_code_[0] = machine_code_[0] | instruction_type;
        }
        else if(token_list->type != _INSTRUCTION_ENDING_) // If the token type is an argument
        {
            unsigned int value = token_list->value;
            if(token_list->type == _RAM_ADRESS_ || token_list->type == _REGISTER_ADRESS_)
            {
                value << 1;
                if(token_list->type == _RAM_ADRESS_){value++;}
            }

            printf("- %i\n",ARGUMENT_POSITION_IN_BYTES[instruction_type][argument_counter]);
            value = value << ARGUMENT_POSITION_IN_BYTES[instruction_type][argument_counter];
            printf("-- %i\n",value);
            machine_code_[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] 
            = machine_code_[ARGUMENT_BYTE_NUMBER[instruction_type][argument_counter]] | value;
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
        print_binary(machine_code[i]);
    }
}

