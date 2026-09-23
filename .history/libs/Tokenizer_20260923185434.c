#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "ErrorManager.h"
#include "Tokenizer.h"

#define LEXEME_MAX_SIZE 10
#define SEPARATION_CHAR_NUMBER 5
#define VALID_CHAR_NUMBER 44
#define VALID_KEYWORD_NUMBER 21

// Consts
const char SEPARATION_CHARS[] = { ' ', '\t', '\n', '\r', ';' };
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

// Private functions

bool is_char_in_array(char char_, const char* array, size_t array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(array[i] == char_)
        {
            return true;
        }
    }
    return false;
}

int is_string_in_array(char* string, const char** array, size_t array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(strcmp(array[i], string) == 0)
        {
            return i;
        }
    }
    return -1;
} 

bool is_only_number_in_string(char* string)
{   
    char* char_ = string;
    while(*char_ != '\0')
    {
        if((int)*char_ < '0' || (int)*char_ > '9') // If the char is not a number (in ascii table)
        {
            return false;
        }
        char_++;
    }
    return true;
}

// Public functions

struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE + 1] = ""; // Add +1 to put a \0 at the end of the lexeme
    unsigned int lexeme_index = 0;
    bool in_lexeme = false;
    size_t line = 0;
    size_t char_ = 0;
    bool instruction_ended = false;

    struct token* token_list = malloc(sizeof(struct token));
    if(!token_list)
    {
        error(MALLOC_FAILED, 0, 0, 0, "");
    }
    struct token* current_token = token_list;
    current_token->is_dereference = false;
    current_token->next = NULL;

    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {   
        printf("-  %s\n", lexeme);
        printf("%c\n", *char_pointer);
        if(!is_char_in_array(tolower(*char_pointer), VALID_CHARS, VALID_CHAR_NUMBER)) // Checking if the char is invalid
        {
            error(INVALID_CHAR, line, char_, (int)*char_pointer, "");
        }

        if(*char_pointer == '\n') // Checking if there’s a line break
        {
            char_ = 0;
            line++;
        }
     
        if(is_char_in_array(*char_pointer, SEPARATION_CHARS, SEPARATION_CHAR_NUMBER)) // If the char is a separator
        {
            if(in_lexeme)
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
                        error(INVALID_PREFIX, line, char_, (int)lexeme[0], "");
                        break;
                    }
                    current_token->value = atoi(lexeme+1);
                }
                else // If the lexeme is not an adress
                {   
                    int which_keyword = is_string_in_array(lexeme, VALID_KEYWORDS, VALID_KEYWORD_NUMBER);
                    if(which_keyword == -1) // If keyword is invalid
                    {
                        error(INVALID_KEYWORD, line, char_, 0, lexeme);
                    }

                    current_token->type = _KEYWORD_;
                    current_token->value = which_keyword;
                    
                }
            }

            if(*char_pointer == ';')
            {
                instruction_ended = true;
            }

            in_lexeme = false;

            struct token* new_token = malloc(sizeof(struct token));
            if(!new_token)
            {
                error(MALLOC_FAILED, 0, 0, 0, "");
            }
            current_token->next = new_token;
            current_token = new_token;
            current_token->is_dereference = false;
            current_token->next = NULL;

            if(instruction_ended)
            {
                current_token->type = _INSTRUCTION_ENDING_;
                current_token->value = 0;
                struct token* separation_token = malloc(sizeof(struct token));
                if(!separation_token)
                {
                    error(MALLOC_FAILED, 0, 0, 0, "");
                }
                current_token->next = separation_token;
                current_token = separation_token;
                current_token->is_dereference = false;
                current_token->next = NULL;
                instruction_ended = false;
            }

        }
        else // if the char is not a separator 
        {
            in_lexeme = true;
            if(lexeme_index > LEXEME_MAX_SIZE-1) // Checking if the lexeme is too long
            {
                error(LEXEME_TOO_LONG, line, char_, 0, "");
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
