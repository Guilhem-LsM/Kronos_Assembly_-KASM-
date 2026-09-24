#pragma once

#include <stdbool.h>

bool is_char_in_array(char char_, const char* array, size_t array_size);

int is_string_in_array(char* string, const char** array, size_t array_size);

bool is_only_number_in_string(const char* string);