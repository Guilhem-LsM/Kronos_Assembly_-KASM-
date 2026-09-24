#include <stdio.h>
#include "tokenizer.h"
#include "error_manager.h"

// Consts
const int NUMBER_OF_ARGUMENT_PER_INSTRUCTION[] = 
{
    0, 3, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 2, 2, 1, 2, 2, 2, 1, 0, 1
};

const int INSTRUCTIONS_ARCHITECTURE[24][3] = 
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
    while (current_token)
    {

        if(instruction_type == -1 && current_token->type != _KEYWORD_) // If we are not in an instruction, and the type of the first token is a keyword
        {
            error(_FIRST_T_NOT_K_, current_token->line, current_token->char_, 0, token_type_string[current_token->type], 0);
        }
        else if(instruction_type == -1) // If we are not in a instrutction and the token type is a keyword
        {
            instruction_type = current_token->value;
            instruction_line = current_token->line;
            instruction_char = current_token->char_;
        }
        else if(current_token->type != _INSTRUCTION_ENDING_) // if the token's type is not an instruction ending
        {

            if(INSTRUCTIONS_ARCHITECTURE[instruction_type][argument_counter] == _RAM_REGISTER_ADRESS_ && (!current_token->type == _RAM_ADRESS_ && !current_token->type == _REGISTER_ADRESS_))
            {
                error(_WRONG_ARG_TYPE_, current_token->line, current_token->char_, INSTRUCTIONS_ARCHITECTURE[instruction_type][argument_counter], "", current_token->type);
            }
            else if(INSTRUCTIONS_ARCHITECTURE[instruction_type][argument_counter] != _RAM_REGISTER_ADRESS_ && current_token->type != INSTRUCTIONS_ARCHITECTURE[instruction_type][argument_counter])
            {
                error(_WRONG_ARG_TYPE_, current_token->line, current_token->char_, INSTRUCTIONS_ARCHITECTURE[instruction_type][argument_counter], "", current_token->type);
            }

            argument_counter++;
        }
        else // If it's the end of the instruction
        {
            if(argument_counter > NUMBER_OF_ARGUMENT_PER_INSTRUCTION[instruction_type]) // If there's too much arguments
            {
                error(_TOO_M_ARG_, instruction_line, instruction_char, NUMBER_OF_ARGUMENT_PER_INSTRUCTION[instruction_type], "", argument_counter);
            }

            if(argument_counter < NUMBER_OF_ARGUMENT_PER_INSTRUCTION[instruction_type]) // If there's too few arguments
            {
                error(_TOO_F_ARG_, instruction_line, instruction_char, NUMBER_OF_ARGUMENT_PER_INSTRUCTION[instruction_type], "", argument_counter);
            }

            instruction_type = -1; // -1 mean we're not currently treating an instruction
            argument_counter = 0;
        }
        

        if(instruction_type != -1 && !current_token->next) // If the token list reach his end but the last instruction is not closed
        {
            error(_EXPECTED_SEMICOLON_, instruction_line, instruction_char, 0, "", 0);
        }
        current_token = current_token->next;
    };
    
}