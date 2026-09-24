#include <stdio.h>
#include <stdlib.h>

const char* TOKEN_TYPE_STRING[10] =
{
    "_KEYWORD_",
    "_VALUE_",
    "_RAM_ADRESS_",
    "_REGISTER_ADRESS_",
    "_INPUT_ADRESS_",
    "_OUTPUT_ADRESS_",
    "_LINE_ADRESS_", 
    "_INSTRUCTION_ENDING_",
    "_RAM_REGISTER_ADRESS_",
    "_NULL_"
};

void print_token(const struct token* token)
{
    printf("---------------------\n");
    printf("Adress : %p\n", token);
    printf("Type : %i\n", token->type);
    printf("Value : %i\n", token->value);
    printf("Is dereference : %d\n", token->is_dereference);
    printf("Line : %i\n", token->line);
    printf("Char : %i\n", token->char_);
    printf("Next : %p\n", token->next);
    printf("---------------------\n");
}

