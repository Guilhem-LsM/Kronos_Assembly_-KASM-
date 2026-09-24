#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "error_manager.h"
#include "tokenizer.h"
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
 
const char* VALID_KEYWORDS[21] =
{
    "noop",
    "load",
    "mov",
    "push",
    "pop",
    "add",
    "sub",
    "equal",
    "inequal",
    "sup",
    "inf",
    "supequ",
    "infequ",
    "and",
    "or",
    "xor",
    "not",
    "jump",
    "ifgoto",
    "in",
    "out"
};

const char* token_type_string[8] =
{
    "_KEYWORD_",
    "_VALUE_",
    "_RAM_ADRESS_",
    "_REGISTER_ADRESS_",
    "_INPUT_ADRESS_",
    "_OUTPUT_ADRESS_",
    "_LINE_ADRESS_", 
    "_INSTRUCTION_ENDING_"
};

void print_token(const struct token* token)
{
    printf("---------------------\n");
    printf("Adress : %p\n", token);
    printf("Type : %i\n", token->type);
    printf("Value : %i\n", token->value);
    printf("Is dereference : %d\n", token->is_dereference);
    printf("Line : %i\n", token->line);
    printf("Char : %i\n", token->char_);
    printf("Next : %i\n", token->next);
    printf("---------------------\n");
}

struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE + 1] = ""; // Add +1 to put a \0 at the end of the lexeme
    unsigned int lexeme_index = 0;
    bool in_lexeme = false;
    size_t line = 0;
    size_t char_ = 0;
    bool instruction_ended = false;
    size_t first_char_pos = 0;
    bool token_done = false;

    struct token* token_list = calloc(1, sizeof(struct token));
    if(!token_list)
    {
        error(_MALLOC_FAILED_, 0, 0, 0, "", 0);
    }
    struct token* current_token = token_list;
    current_token->is_dereference = false;
    current_token->next = NULL;

    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {   
        printf("%c\n", *char_pointer);
        if(!is_char_in_array(tolower(*char_pointer), VALID_CHARS, VALID_CHAR_NUMBER)) // Checking if the char is invalid
        {
            error(_INVALID_CHAR_, line, char_, (int)*char_pointer, "", 0);
        }

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
                    printf("1\n");
                    current_token->type = _VALUE_;
                    current_token->value = atoi(lexeme);
                }
                else if(is_only_number_in_string(lexeme+1)) // Check if the lexeme is an adress
                {
                    printf("2\n");
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
                    printf("3\n");
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

            in_lexeme = false;

            if(instruction_ended)
            {
                struct token* separation_token = malloc(sizeof(struct token));
                if(!separation_token)
                {
                    error(_MALLOC_FAILED_, 0, 0, 0, "", 0);
                }
                current_token->next = separation_token;
                separation_token->type = _INSTRUCTION_ENDING_;
                separation_token->value = 0;
                separation_token->is_dereference = false;
                separation_token->line = line;
                separation_token->char_ = char_;
                separation_token->next = NULL;
                current_token = separation_token;

                instruction_ended = false;
            }
        }
        else // if the char is not a separator 
        {   
            if(!in_lexeme) // If the lexeme begin
            {
                first_char_pos = char_;
                
                print_token(current_token);
                struct token* new_token = malloc(sizeof(struct token));
                if(!new_token)
                {
                    error(_MALLOC_FAILED_, 0, 0, 0, "", 0);
                }
                new_token->is_dereference = false;
                new_token->next = NULL;
                current_token->next = new_token;
                current_token = new_token;
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
