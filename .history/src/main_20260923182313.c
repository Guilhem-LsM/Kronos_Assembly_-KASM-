#include <stdio.h>
#include <stdlib.h>
#include "ErrorManager.h"
#include "Tokenizer.h"
#include "FileManager.h"


int main(int argc, char **argv)
{       
    char* path;
    char* raw_program;
    if(argc == 2) //Check if there's the right number of arguments 
    {
        path = argv[1]; // Get the patch of the program
    }
    else
    {
        error(NO_PATH, 0, 0, 0, "");
    }
    raw_program = get_program(path);
    struct token* token_list = tokenize(raw_program);

    struct token* token_ = token_list;
    unsigned int i = 0;
    do
    {
        printf("%i\n", token_->type);
        if(token_->next)
        {
            token_ = token_->next;
        }
        i++;
    } while(token_->next && i < 10);

    printf("Compilation Done !");
    return 0;
}

