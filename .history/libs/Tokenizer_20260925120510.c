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
#define VALID_KEYWORD_NUMBER 24

// Consts
static const char SEPARATION_CHARS[] = { ' ', '\t', '\n', '\r', ';', '*'};
static const char VALID_CHARS[] = 
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
    '6', '7', '8', '9'
};

static const char* VALID_KEYWORDS[24] =
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
static void is_char_valid(char char_, unsigned int line, unsigned int char__)
{
    if(!is_char_in_array(tolower(char_), VALID_CHARS, VALID_CHAR_NUMBER)) // Checking if the char is invalid
        {
            error(_INVALID_CHAR_, line, char__, (int)char_, 0, "");
        }
}

static void determine_token_type_and_value(struct token* token_, char* lexeme, int line, char char_ )
{
    if(is_only_number_in_string(lexeme))
    {
        token_->type = _VALUE_;
        token_->value = atoi(lexeme);
    }
    else if(is_only_number_in_string(lexeme+1)) // Check if the lexeme is an adress
    {
        switch (tolower(lexeme[0]))
        {
        case 'r':
            token_->type = _REGISTER_ADRESS_;
            break;
            
        case 'l':
            token_->type = _LINE_ADRESS_;
            break;
            
        case '@':
            token_->type = _RAM_ADRESS_;
            break;
            
        case 'i':
            token_->type = _INPUT_ADRESS_;
            break;
            
        case 'o':
            token_->type = _OUTPUT_ADRESS_;
            break;
        
        default:
            error(_INVALID_PREFIX_, line, char_, (int)lexeme[0], 0, "");
            break;
        }
        token_->value = atoi(lexeme+1);
    }
    else // If the lexeme is not an adress
    {   
        int which_keyword = is_string_in_array(lexeme, VALID_KEYWORDS, VALID_KEYWORD_NUMBER);
        if(which_keyword == -1){ error(_INVALID_KEYWORD_, line, char_, 0, 0, lexeme); } // If keyword is invalid
        token_->type = _KEYWORD_;
        token_->value = which_keyword;
    }
}

    // Public
struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE + 1] = ""; // Add +1 to put a \0 at the end of the lexeme
    unsigned int lexeme_index = 0;
    char* char_pointer = raw_program;
    size_t line = 0;
    size_t char_ = 0;
    size_t first_char_pos = 0;
    struct token* token_list = NULL;
    struct token* current_token = NULL;

    while(*char_pointer != '\0')
    {   
        is_char_valid(tolower(*char_pointer), line, char_);  // Is the current char valid
        if(*char_pointer == '\n') { char_ = 0; line++; } // Checking if there’s a line break and update line and char_
        if(!is_char_in_array(*char_pointer, SEPARATION_CHARS, SEPARATION_CHAR_NUMBER)) // If the char is not a separator
        {   
            if(lexeme[0] == '\0') // If the lexeme begin
            {
                first_char_pos = char_;
            }
            if(lexeme_index > LEXEME_MAX_SIZE-1) { error(_LEXEME_TOO_LONG_, line, char_, 0, "", 0); } // Checking if the lexeme is too long
            lexeme[lexeme_index] = tolower(*char_pointer);
            lexeme_index++;
        }
        else // if the char is a separator 
        {
            if(lexeme[0] != '\0') //If lexeme is not empty
            {
                lexeme[lexeme_index] = '\0';
                lexeme_index = 0;
                struct token* new_token_ = new_token(_NULL_, 0, false, 0, 0, NULL);
                determine_token_type_and_value(new_token_, lexeme, line, char_);
                lexeme[0] = '\0';
                if(*char_pointer == '*') { new_token_->is_dereference = true; }
                new_token_->line = line;
                new_token_->char_ = first_char_pos;
                if(current_token){current_token->next = new_token_;}
                else{token_list = new_token_;}
                current_token = new_token_;
            }
            else if(*char_pointer == '*'){ error(_UNEXPECTED_AST_, line, char_, 0, "", 0); printf("d\n");}

            if(*char_pointer == ';')
            {
                struct token* new_token_ = new_token(_INSTRUCTION_ENDING_, 0, false, line, char_, NULL);
                if(current_token){current_token->next = new_token_;}
                else{token_list = new_token_;}
                current_token = new_token_;
            }
        }
        char_++;
        char_pointer++;
    }
    return token_list;
}