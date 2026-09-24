#pragma once

#include <stdbool.h>

enum token_type 
{
    _KEYWORD_,
    _VALUE_,
    _RAM_ADRESS_,
    _REGISTER_ADRESS_,
    _INPUT_ADRESS_,
    _OUTPUT_ADRESS_,
    _LINE_ADRESS_, 
    _INSTRUCTION_ENDING_,
    _RAM_REGISTER_ADRESS_,
    _NULL_
};

const char* TOKEN_TYPE_STRING[10];

struct token
{
    enum token_type type;
    int value;
    bool is_dereference;
    size_t line;
    size_t char_;
    struct token *next; 
};

void print_token(const struct token* token);

struct token* tokenize(char* raw_program);
