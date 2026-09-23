#define PROGRAM_FILE_NOT_FOUND 1 // Program file not found
#define FSEEK_FAILED 2 // The fseek() function has failed
#define NO_PATH 3 // No path has been specified
#define MALLOC_FAILED 4 // Memory allocation failed
#define INVALID_CHAR 5 // The char is not valid
#define LEXEME_TOO_LONG 6 // The lexeme is too long
#define INVALID_PREFIX 7 // Invalid prefix


void error(unsigned int index, size_t line, size_t char_, int data_1);