#include <stdio.h>
#include <stdlib.h>

// All the defines are in the .h

void error(unsigned int index, size_t line, size_t char_, int data_1)
{
    switch (index)
    {
    case 1: // Program file not found 
        printf("ERROR %u : Program file not found", index);
        break;

    case 2: // fseek() has failed
        printf("ERROR %u : fseek() has failed", index);
        break;
    
    case 3: // No path has been specified
        printf("ERROR %u : No path has been specified", index);
        break;
    
    case 4: // Memory allocation failed
        printf("ERROR %u : Memory allocation failed", index);
        break;
    
    case 5: // Char is invalid
        printf("ERROR %u : Char '%c' is invalid\n", index, (char)data_1);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    case 6: // Lexeme too long
        printf("ERROR %u : Lexeme too long", index);
        printf("ln:%u,ch:%u\n", line, char_);
        break;
    
    default:
        printf("wtf is this error ?");
        break;
    }
    printf("\n");
    exit(1);
}