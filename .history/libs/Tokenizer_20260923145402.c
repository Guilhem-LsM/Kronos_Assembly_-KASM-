#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ErrorManager.h"

#define LEXEME_MAX_SIZE 10
#define SEPARATION_CHAR_NUMBER 4
#define SEPARATION_CHAR_NUMBER 30


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
    '*', ';'
};

struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE] = "";
    char* lexeme_pointer = lexeme; 
    bool in_lexeme = false;

    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {
        
    }
}

bool is_in_array(char char_, char* array, size_t array_size)
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
