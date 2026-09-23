#include <stdio.h>
#include <stdlib.h>
#include "ErrorManager.h"

enum token_type 
{
    _KEYWORD_,
    _VALUE_,
    _RAM_ADRESS_,
    _REGISTER_ADRESS_,
    _INPUT_ADRESS_,
    _OUTPUT_ADRESS_,
    _LINE_ADRESS_, 
    _INSTRUCTION_ENDING_
};

struct token
{
    enum token_type type;
    int value;
    bool is_dereference;
};

token* Tokenize(){

}
