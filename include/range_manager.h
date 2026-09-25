#pragma once

#include "token.h"

void debug_range(struct token* token_list); 

void replace_instruction_index_by_memory_addresses(struct token* token_list);