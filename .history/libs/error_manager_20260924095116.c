#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"

// All the defines are in the .h

void error(unsigned int index, size_t line, size_t char_, int data_1, char* string)
{
    switch (index)
    {
    case _PROGRAM_FILE_NOT_FOUND_: // Program file not found 
        printf("ERROR %u : Program file not found\n", index);
        break;

    case _FSEEK_FAILED_: // fseek() has failed
        printf("ERROR %u : fseek() has failed\n", index);
        break;
    
    case _NO_PATH_: // No path has been specified
        printf("ERROR %u : No path has been specified\n", index);
        break;
    
    case _MALLOC_FAILED_: // Memory allocation failed
        printf("ERROR %u : Memory allocation failed\n", index);
        break;
    
    case _INVALID_CHAR_: // Char is invalid
        printf("ERROR %u : Char '%c' is invalid\n", index, (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _LEXEME_TOO_LONG_: // Lexeme too long
        printf("ERROR %u : Lexeme too long\n", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_PREFIX_: // Invalid prefix
        printf("ERROR %u : The prefix '%c' is invalid\n", index, (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_KEYWORD_: // Invalid keyword
        printf("ERROR %u : The keyword \"%s\" is invalid\n", index, string);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _UNEXPECTED_AST_: // Unexpected asterisk
        printf("ERROR %u : Unexpected asterisk, it must be placed at the end of an address\n", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _FIRST_T_NOT_K_: // Unexpected asterisk
        printf("ERROR %u : Unexpected asterisk, it must be placed at the end of an address\n", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    exit(1);
}