#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ErrorManager.h"

#define LEXEME_MAX_SIZE 10
#define SEPARATION_CHAR_NUMBER 4
#define VALID_CHAR_NUMBER 34


// Consts
const char SEPARATION_CHARS[] = { ' ', '\t', '\n', '\r', };
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
    '\n', '\r',
};

// Private functions

bool is_in_array(char char_, const char* array, size_t array_size)
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

// Public functions

struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE + 1] = ""; // Add +1 to put a \0 at the end of the lexeme
    unsigned int lexeme_index = 0;
    bool in_lexeme = false;
    size_t line = 0;
    size_t char_ = 0;

    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {
        if(!is_in_array(*char_pointer, VALID_CHARS, VALID_CHAR_NUMBER)) // Checking if the char is invalid
        {
            error(INVALID_CHAR, 0, 0, (int)*char_pointer);
        }

        if(*char_pointer == '\n') // Checking if there’s a line break
        {
            char_ = 0;
            line++;
        }

        if(is_in_array(*char_pointer, SEPARATION_CHARS, SEPARATION_CHAR_NUMBER)) // If the char is a separator
        {
            if(in_lexeme)
            {
                lexeme[lexeme_index+1] = '\0';
                lexeme_index = 0;
            }
            in_lexeme = false;
        }
        else // if the char is not a separator 
        {
            in_lexeme = true;
            if(lexeme_index > LEXEME_MAX_SIZE-1) // Checking if the lexeme is too long
            {
                error(LEXEME_TOO_LONG, line, char_, 0);
            }

            lexeme[lexeme_index] = *char_pointer;
        }

    }
}
