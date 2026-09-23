#define PROGRAM_FILE_NOT_FOUND 1 // Program file not found
#define FSEEK_FAILED 2 // The fseek() function has failed
#define NO_PATH 3 // No path has been specified
#define MALLOC_FAILED 4 // Memory allocation failed
#define INVALID_CHAR 5 // The char is not valid

void error(unsigned int index, size_t col, size_t row, int data_1);