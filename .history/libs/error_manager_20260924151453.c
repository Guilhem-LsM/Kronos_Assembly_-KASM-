#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"
#include "tokenizer.h"

// All the defines are in the .h

void error(const unsigned int index, const size_t line, const size_t char_, const int data_1, const char* string, const int data_2)
{
    switch (index)
    {
    case _PROGRAM_FILE_NOT_FOUND_: // Program file not found 
        printf("ERROR %u : Program file not found ", index);
        break;

    case _FSEEK_FAILED_: // fseek() has failed
        printf("ERROR %u : fseek() has failed ", index);
        break;
    
    case _NO_PATH_: // No path has been specified
        printf("ERROR %u : No path has been specified ", index);
        break;
    
    case _MALLOC_FAILED_: // Memory allocation failed
        printf("ERROR %u : Memory allocation failed ", index);
        break;
    
    case _INVALID_CHAR_: // Char is invalid
        printf("ERROR %u : Char '%c' is invalid ", index, (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _LEXEME_TOO_LONG_: // Lexeme too long
        printf("ERROR %u : Lexeme too long ", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_PREFIX_: // Invalid prefix
        printf("ERROR %u : The prefix '%c' is invalid ", index, (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_KEYWORD_: // Invalid keyword
        printf("ERROR %u : The keyword \"%s\" is invalid ", index, string);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _UNEXPECTED_AST_: // Unexpected asterisk
        printf("ERROR %u : Unexpected asterisk, it must be placed at the end of an address ", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _FIRST_T_NOT_K_: // Unexpected asterisks
        printf("ERROR %u : Instruction must begin by a _KEYWORD_, yours begin by a %s ", index, string);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _TOO_M_ARG_: // Too many argument in the instruction
        printf("ERROR %u : Too many argument in the instruction [Exp : %i, Rec : %i] ", index, data_1, data_2);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _EXPECTED_SEMICOLON_: // Expected ';' at the end of the instruction
        printf("ERROR %u : Expected ';' at the end of the instruction ", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _TOO_F_ARG_: // Too few argument in the instruction
        printf("ERROR %u : Too few argument in the instruction [Exp : %i, Rec : %i] ", index, data_1, data_2);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _WRONG_ARG_TYPE_: // Wrong type of argument
        printf("ERROR %u : Wrong type of argument [Exp : %s, Rec : %s] ", index, TOKEN_TYPE_STRING[data_1], TOKEN_TYPE_STRING[data_2]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    exit(1);
}