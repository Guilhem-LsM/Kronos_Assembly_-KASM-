#include <stdio.h>
#include <stdlib.h>
#include "error_manager.h"
#include "token.h"

// All the defines are in the .h

static const char* ERROR_TYPE_STRING[16] =
{
    "_PROGRAM_FILE_NOT_FOUND_", // Program file not found
    "_FSEEK_FAILED_", // The fseek() function has failed
    "_NO_PATH_", // No path has been specified
    "_MALLOC_FAILED_", // Memory allocation failed
    "_INVALID_CHAR_", // The char is not valid
    "_LEXEME_TOO_LONG_", // The lexeme is too long
    "_INVALID_PREFIX_", // Invalid prefix
    "_INVALID_KEYWORD_", // Invalid keyword
    "_UNEXPECTED_AST_", // Unexpected asterisk
    "_FIRST_T_NOT_K_", // First token of the instructin is not a keyword
    "_TOO_M_ARG_", // Too many argument in the instruction
    "_EXPECTED_SEMICOLON_", // Expected ';' at the end of the instruction
    "_TOO_F_ARG_", // Too few argument in the instruction
    "_WRONG_ARG_TYPE_", // Wrong type of argument
    "_DEREFERENCE_W_TYPE_", // You can't dereference the type 
    "_VALUE_OUT_OF_RANGE_" // A value you entered is not within the correct range
};

void error(const unsigned int index, const size_t line, const size_t char_, const int data_1, const int data_2, const char* string)
{
    switch (index)
    {
    case _PROGRAM_FILE_NOT_FOUND_: // Program file not found 
        printf("ERROR %s : Program file not found ", ERROR_TYPE_STRING[index]);
        break;

    case _FSEEK_FAILED_: // fseek() has failed
        printf("ERROR %s : fseek() has failed ", ERROR_TYPE_STRING[index]);
        break;
    
    case _NO_PATH_: // No path has been specified
        printf("\nKASM.exe [source path] [destination path]\n");
        break;
    
    case _MALLOC_FAILED_: // Memory allocation failed
        printf("ERROR %s : Memory allocation failed ", ERROR_TYPE_STRING[index]);
        break;
    
    case _INVALID_CHAR_: // Char is invalid
        printf("ERROR %s : Char '%c' is invalid ", ERROR_TYPE_STRING[index], (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _LEXEME_TOO_LONG_: // Lexeme too long
        printf("ERROR %s : Lexeme too long ", ERROR_TYPE_STRING[index]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_PREFIX_: // Invalid prefix
        printf("ERROR %s : The prefix '%c' is invalid ", ERROR_TYPE_STRING[index], (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _INVALID_KEYWORD_: // Invalid keyword
        printf("ERROR %s : The keyword \"%s\" is invalid ", ERROR_TYPE_STRING[index], string);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _UNEXPECTED_AST_: // Unexpected asterisk
        printf("ERROR %s : Unexpected asterisk, it must be placed at the end of an address ", ERROR_TYPE_STRING[index]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _FIRST_T_NOT_K_: // Unexpected asterisks
        printf("ERROR %s : Instruction must begin by a _KEYWORD_, yours begin by a %s ", ERROR_TYPE_STRING[index], string);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _TOO_M_ARG_: // Too many argument in the instruction
        printf("ERROR %s : Too many argument in the instruction [Exp : %i, Rec : %i] ", ERROR_TYPE_STRING[index], data_1, data_2);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _EXPECTED_SEMICOLON_: // Expected ';' at the end of the instruction
        printf("ERROR %s : Expected ';' at the end of the instruction ", ERROR_TYPE_STRING[index]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _TOO_F_ARG_: // Too few argument in the instruction
        printf("ERROR %s : Too few argument in the instruction [Exp : %i, Rec : %i] ", ERROR_TYPE_STRING[index], data_1, data_2);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _WRONG_ARG_TYPE_: // Wrong type of argument
        printf("ERROR %s : Wrong type of argument [Exp : %s, Rec : %s] ", ERROR_TYPE_STRING[index], TOKEN_TYPE_STRING[data_1], TOKEN_TYPE_STRING[data_2]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _DEREFERENCE_W_TYPE_: // Wrong type of argument
        printf("ERROR %s : Trying to dereference an incompatible type [Exp : _RAM_OR_REGISTER_ADRESS_, Rec : %s] ", ERROR_TYPE_STRING[index], TOKEN_TYPE_STRING[data_1]);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case _VALUE_OUT_OF_RANGE_: // A value you entered is not within the correct range
        printf("ERROR %s : A value you entered is not within the correct range [Min : %i , Max : %i] ", ERROR_TYPE_STRING[index], data_1, data_2);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    exit(1);
}