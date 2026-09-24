#include <stdio.h>
#include "tokenizer.h"
#include "error_manager.h"

// Consts
const int* number_of_argument_per_instruction[] =
{
    0, 3, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 2, 2, 1, 2, 2, 2, 1, 0, 1
};

const int* insutructions_architecture[24][3] =
{
    {_NULL_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_REGISTER_ADRESS_, _REGISTER_ADRESS_, _REGISTER_ADRESS_},
    {_RAM_REGISTER_ADRESS_, _VALUE_},
    {_REGISTER_ADRESS_, _LINE_ADRESS_},
    {_LINE_ADRESS_},
    {_OUTPUT_ADRESS_, _RAM_REGISTER_ADRESS_},
    {_INPUT_ADRESS_, _RAM_REGISTER_ADRESS_},
    {_RAM_REGISTER_ADRESS_, _RAM_REGISTER_ADRESS_},
    {_RAM_REGISTER_ADRESS_},
    {_NULL_},
    {_RAM_REGISTER_ADRESS_}
};

void synthaxe_debug(struct token* token_list)
{

    unsigned int argument_counter = 0;
    int instruction_type = -1;
    size_t instruction_line = 0;
    size_t instruction_char = 0;

    struct token* current_token = token_list;
    do
    {
        if(instruction_type == -1 && current_token->type != _KEYWORD_)
        {
            error(_FIRST_T_NOT_K_, current_token->line, current_token->char_, 0, token_type_string[current_token->type]);
        }
        else if(instruction_type == -1)
        {
            instruction_type = current_token->type;
        }
        else if(current_token->type != _INSTRUCTION_ENDING_)
        {
            argument_counter++;
        }
        else
        {
            if(argument_counter > number_of_argument_per_instruction[instruction_type])
            {
                error(_TOO_M_ARG_, current_token->line, current_token->char_, argument_counter, "", number_of_argument_per_instruction[instruction_type]);
            }
        }



        if(current_token->next)
        {
            current_token = current_token->next;
        }
    } while (current_token->next);
    
}