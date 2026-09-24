#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "error_manager.h"
#include "token.h"
#include "string_functions.h"

#define LEXEME_MAX_SIZE 10
#define SEPARATION_CHAR_NUMBER 6
#define VALID_CHAR_NUMBER 44
#define VALID_KEYWORD_NUMBER 21

// Consts
const char SEPARATION_CHARS[] = { ' ', '\t', '\n', '\r', ';', '*'};
const char VALID_CHARS[] = 
{
    'a', 'b', 'c', 'd', 
    'e', 'f', 'g', 'h', 
    'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 
    'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x', 
    'y', 'z', '@', '#', 
    '*', ';', ' ', '\t',
    '\n', '\r', '0', '1',
    '2', '3', '4', '5',
    '6', '7', '8', '9',
};
 
const char* VALID_KEYWORDS[24] =
{
    "noop",
    "add",
    "sub",
    "shiftr",
    "shiftl",
    "and",
    "or",
    "xor",
    "not",
    "equal",
    "inequal",
    "sup",
    "inf",
    "supque",
    "infequ",
    "load",
    "ifgoto",
    "jump",
    "out",
    "in",
    "mov",
    "push",
    "pop",
    "sstack"
    
};

// Functions
    // Private
void is_char_valid(char char_, char* VALID_CHARS, unsigned int VALID_CHAR_NUMBER_, unsigned int line, unsigned int char__)
{
    if(!is_char_in_array(tolower(char_), VALID_CHARS, VALID_CHAR_NUMBER_)) // Checking if the char is invalid
        {
            error(_INVALID_CHAR_, line, char__, (int)char_, "", 0);
        }
}

// 144 lines
    // Public
struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE + 1] = ""; // Add +1 to put a \0 at the end of the lexeme
    unsigned int lexeme_index = 0;
    bool in_lexeme = false;
    size_t line = 0;
    size_t char_ = 0;
    bool instruction_ended = false;
    size_t first_char_pos = 0;
    bool token_done = false;

    struct token* token_list = new_token(_NULL_, 0, false, 0, 0, NULL);
    struct token* current_token = token_list;
    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {   

        is_char_valid(tolower(*char_pointer), VALID_CHARS, VALID_CHAR_NUMBER, line, char_);

        if(*char_pointer == '\n') // Checking if there’s a line break
        {
            char_ = 0;
            line++;
        }
     
        if(is_char_in_array(*char_pointer, SEPARATION_CHARS, SEPARATION_CHAR_NUMBER)) // If the char is a separator
        {
            if(in_lexeme) //If the lexeme just end
            {   
                lexeme[lexeme_index] = '\0';
                lexeme_index = 0;
                if(is_only_number_in_string(lexeme))
                {
                    current_token->type = _VALUE_;
                    current_token->value = atoi(lexeme);
                }
                else if(is_only_number_in_string(lexeme+1)) // Check if the lexeme is an adress
                {
                    switch (tolower(lexeme[0]))
                    {
                    case 'r':
                        current_token->type = _REGISTER_ADRESS_;
                        break;
                        
                    case 'l':
                        current_token->type = _LINE_ADRESS_;
                        break;
                        
                    case '@':
                        current_token->type = _RAM_ADRESS_;
                        break;
                        
                    case 'i':
                        current_token->type = _INPUT_ADRESS_;
                        break;
                        
                    case 'o':
                        current_token->type = _OUTPUT_ADRESS_;
                        break;
                    
                    default:
                        error(_INVALID_PREFIX_, line, char_, (int)lexeme[0], "", 0);
                        break;
                    }
                    current_token->value = atoi(lexeme+1);
                }
                else // If the lexeme is not an adress
                {   
                    int which_keyword = is_string_in_array(lexeme, VALID_KEYWORDS, VALID_KEYWORD_NUMBER);
                    if(which_keyword == -1) // If keyword is invalid
                    {
                        error(_INVALID_KEYWORD_, line, char_, 0, lexeme, 0);
                    }
                    current_token->type = _KEYWORD_;
                    current_token->value = which_keyword;
                    
                }

                if(*char_pointer == '*')
                {
                    current_token->is_dereference = true;
                }
                current_token->line = line;
                current_token->char_ = first_char_pos;

                token_done = true;
            }
            else
            {
                if(*char_pointer == '*')
                {
                    error(_UNEXPECTED_AST_, line, char_, 0, "", 0);
                }
            }

            if(*char_pointer == ';')
            {
                instruction_ended = true;
            }

            if(instruction_ended)
            {
                struct token* separation_token = new_token(_INSTRUCTION_ENDING_, 0, false, line, char_, NULL);
                current_token->next = separation_token;
                current_token = separation_token;
                
                instruction_ended = false;
            }

            in_lexeme = false;
        }
        else // if the char is not a separator 
        {   
            if(!in_lexeme) // If the lexeme begin
            {
                first_char_pos = char_;
                
                if(token_done)
                {
                    struct token* new_token_ = new_token(_NULL_, 0, false, 0, 0, NULL);
                    current_token->next = new_token_;
                    current_token = new_token_;

                    token_done = false;
                }
            }

            in_lexeme = true;
            if(lexeme_index > LEXEME_MAX_SIZE-1) // Checking if the lexeme is too long
            {
                error(_LEXEME_TOO_LONG_, line, char_, 0, "", 0);
            }

            lexeme[lexeme_index] = tolower(*char_pointer);
            lexeme_index++;
        }

        char_++;
        char_pointer++;
    }

    free(raw_program);
    return token_list;
}
