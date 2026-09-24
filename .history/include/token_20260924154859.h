#pragma once

#include <stdbool.h>

// Const
enum TOKEN_TYPE 
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

// Struct
struct token
{
    enum TOKEN_TYPE type;
    int value;
    bool is_dereference;
    size_t line;
    size_t char_;
    struct token *next; 
};

// Function
void print_token(const struct token* token);

struct token* new_node(
    enum TOKEN_TYPE type,
    int value,
    bool is_dereference,
    size_t line,
    size_t char_
);


