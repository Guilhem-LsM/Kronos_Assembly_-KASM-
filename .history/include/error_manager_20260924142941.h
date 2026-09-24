#pragma once

enum error_type 
{
    _PROGRAM_FILE_NOT_FOUND_, // Program file not found
    _FSEEK_FAILED_, // The fseek() function has failed
    _NO_PATH_, // No path has been specified
    _MALLOC_FAILED_, // Memory allocation failed
    _INVALID_CHAR_, // The char is not valid
    _LEXEME_TOO_LONG_, // The lexeme is too long
    _INVALID_PREFIX_, // Invalid prefix
    _INVALID_KEYWORD_, // Invalid keyword
    _UNEXPECTED_AST_, // Unexpected asterisk
    _FIRST_T_NOT_K_, // First token of the instructin is not a keyword
    _TOO_M_ARG_, // Too many argument in the instruction
    _EXPECTED_SEMICOLON_, // Expected ';' at the end of the instruction
    _TOO_F_ARG_ // Too few argument in the instruction
};


void error(const unsigned int index, const size_t line, const size_t char_, const int data_1, const char* string, const int data_2);