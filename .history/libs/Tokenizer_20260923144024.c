#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ErrorManager.h"

#define LEXEME_MAX_SIZE 25

struct token* tokenize(char* raw_program){
    char lexeme[LEXEME_MAX_SIZE] = "";
    bool in_lexeme = false;

    char* char_pointer = raw_program;
    while(*char_pointer != '\0')
    {
        
    }
}
