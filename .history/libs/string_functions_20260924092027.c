bool is_char_in_array(char char_, const char* array, size_t array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(array[i] == char_)
        {
            return true;
        }
    }
    return false;
}

int is_string_in_array(char* string, const char** array, size_t array_size)
{
    for(int i = 0; i < array_size; i++)
    {
        if(strcmp(array[i], string) == 0)
        {
            return i;
        }
    }
    return -1;
} 

bool is_only_number_in_string(char* string)
{   
    char* char_ = string;
    while(*char_ != '\0')
    {
        if((int)*char_ < '0' || (int)*char_ > '9') // If the char is not a number (in ascii table)
        {
            return false;
        }
        char_++;
    }
    return true;
}