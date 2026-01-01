#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define PATH_INPUT "F:\\Prog\\C\\KASM_Compiler\\input\\KASM.txt"
#define PATH_OUTPUT "F:\\Prog\\C\\KASM_Compiler\\output\\KCM.txt"
#define MAX_INSTRUCTION_NUMBER 32768
#define MAX_ARGUMENT_NUMBER 4
#define MAX_ARGUMENT_LENGHT 8
#define KEYWORD_NUMBER 24
#define NOT_A_KEYWORD -1
#define VALID_CHAR_NUMBER 42
#define SEPERATIR_CHAR_NUMBER 5
#define PREFIX_CHAR_NUMBER 5

// ENUMS

enum TokenType{
	NONE = 0,
	KEYWORD = 1, 
	REGISTER_ADRESS, 
	RAM_ADRESS, 
	REGISTER_RAM_ADRESS, 
	VALUE, 
	MEMORY_PROGRAM_ADRESS,
	OUTPUT_ADRESS,
	INPUT_ADRESS
};

// STRUCTS

typedef struct Token {
		enum TokenType type;
		int data;
}Token;

typedef struct CharList{
	char *data;
	size_t size;
	
}CharList;

typedef struct TokenList{
	Token *data;
	size_t size;
}TokenList;

typedef struct PosFile{
	int line;
	int charactere;
} PosFile;

// CONST DATAS

const char VALID_CHAR[] = { 
	'A','B','C','D','E','F',
	'G','H','I','J','K','L',
	'M','N','O','P','Q','R',
	'S','T','U','V','W','X',
	'Y','Z','0','1','2','3',
	'4','5','6','7','8','9',
	' ', '#', '@', '	', ';',
	'\n'
};

const char SEPERATOR_CHAR[] = {
	' ', '#', '	', ';','\n'
};

const char PREFIX_CHAR[] = {
	'R', '@', 'M', 'I', 'O'
};

const unsigned int ARGUMENT_NUMBER[] = {
	0, 3, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 
	3, 3, 2, 2, 1, 2, 2, 2, 1, 0, 1
};

const enum TokenType ARGUMENT_ARCHITECTURE[][24] = {
	{NONE},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS},
	{REGISTER_RAM_ADRESS, VALUE},
	{REGISTER_ADRESS, MEMORY_PROGRAM_ADRESS},
	{MEMORY_PROGRAM_ADRESS},
	{OUTPUT_ADRESS, REGISTER_RAM_ADRESS},
	{INPUT_ADRESS, REGISTER_RAM_ADRESS},
	{REGISTER_RAM_ADRESS, REGISTER_RAM_ADRESS},
	{REGISTER_RAM_ADRESS},
	{NONE},
	{REGISTER_RAM_ADRESS}
};

const char KEYWORD_LIST[24][8] = {
	{"NOP"}, {"ADD"}, {"SUB"},
	{"SHIFT_R"}, {"SHIFT_L"}, {"AND"},
	{"OR"}, {"WOR"}, {"NOT"}, {"EQUAL"},
	{"INEQUAL"}, {"SUP"}, {"INF"},
	{"SUP_EQU"}, {"INF_EQU"}, {"LOAD"},
	{"IFGOTO"}, {"JUMP"}, {"OUT"},
	{"IN"}, {"MOV"}, {"PUSH"},
	{"POP"}, {"S_STACK"}
};

const char TOKEN_TYPE_NAME_TABLE[9][25] = {
	{"NONE"},
	{"KEYWORD"},
	{"REGISTER_ADRESS"},
	{"RAM_ADRESS"},
	{"REGISTER_RAM_ADRESS"},
	{"VALUE"},
	{"MEMORY_PROGRAM_ADRESS"},
	{"OUTPUT_ADRESS"},
	{"INPUT_ADRESS"}
};

// FUNCTIONS

char toLower(char c){
	if(c >= 65 && c <= 90){
		return c + 32;
	}
	else{
		return c;
	}
}

int findKeyword(char *s){
	int output = -1;
	for(int i = 0; i < 24; i++){
		if(strcmp(s, KEYWORD_LIST[i]) == 0){
			output = i;
		}
	}
	return output;
}

bool isValidChar(char c){
	bool output = false;
	for(int i = 0; i < VALID_CHAR_NUMBER ; i++){
		if(VALID_CHAR[i] == c){
			output = true;
		}
	}
	return output;
}

bool isSeparatorChar(char c){
	bool output = false;
	for(int i = 0; i < SEPERATIR_CHAR_NUMBER ; i++){
		if(SEPERATOR_CHAR[i] == c){
			output = true;
		}
	}
	return output;
}

bool isPrefixChar(char c){
	bool output = false;
	for(int i = 0; i < PREFIX_CHAR_NUMBER; i++){
		if(PREFIX_CHAR[i] == c){
			output = true;
		}
	}
	return output;
}

size_t fileSize(FILE *file){
	size_t size = 0;
	char content_file_line[100];
	while(fgets(content_file_line, sizeof(content_file_line), file)) {
		size += strlen(content_file_line);
	}
	// For the '\0' at the end
	size++;
	fseek(file, 0, SEEK_SET);
	return size;
}

bool isNumber(char *s){
	bool output = true;
	for(char *c = s; *c ; c++){
		if(*c < '0' || *c > '9' ){output = false;}
	}
	return output;
}



void compilationError(int i, char *word, char charactere, PosFile position_file, int extra_data_1, int extra_data_2){
	printf("\n");
	printf("COMPILATION ERROR %d\n", i);
	switch(i){
		case 1:
		printf("\'%c\' is not a valid charactere\n", charactere);
		break;

		case 2:
		printf("\';\' expected\n");
		break;

		case 3:
		printf("Arguments missing\n");
		printf("EXPECTED : %d\n", ARGUMENT_NUMBER[findKeyword(word)]);
		printf("RECEIVED : %d\n", extra_data_1);
		break;

		case 4:
		printf("\'%c\' is not a valid prefix for an argument\n", charactere);
		printf("VALID ONES :\n");
		printf("	VALUES : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9\n");
		printf("	ADRESS : R, @, M, I, O\n");
		break;

		case 5:
		printf("\'%s\' is not an instruction keyword\n", word);
		break;

		case 6:
		printf("\'%s\' is not an adress or a value \n", word);
		break;

		case 7:
		printf("Wrong type of argument\n");
		printf("EXPECTED : %s\n", TOKEN_TYPE_NAME_TABLE[ARGUMENT_ARCHITECTURE[extra_data_1][extra_data_2]]);
		printf("RECEIVED : %s\n", word);
		printf("\n");
		break;

		case 8:
		printf("Too many argument\n");
		printf("EXPECTED : %d\n", ARGUMENT_NUMBER[findKeyword(word)]);
		printf("RECEIVED : %d\n", extra_data_1);
		printf("\n");
		break;

		case 9 :
		printf("\';\' unexpected\n");
		break;
	}
	
	printf("LINE : %d\n", position_file.line);
	printf("CHAR : %d\n", position_file.charactere);
	exit(1);
}

TokenList lexer(
	FILE *file, 
	size_t max_instruction_number, 
	size_t max_argument_number,
	size_t max_argument_lenght
	){
	
	// +1 is for the ' ' that we add at the end of the file
	CharList content_file = {malloc(fileSize(file)+1), fileSize(file)+1};
	if(!content_file.data){
		printf("ERROR : standarized_file allocation failed !\n");
		exit(1);
	}
	
	TokenList token_list = {malloc(max_instruction_number * max_argument_number * sizeof(Token)), max_instruction_number * max_argument_number};
	if(!token_list.data){
		printf("ERROR : standarized_file allocation failed !\n");
		exit(1);
	}
	
	content_file.data[0] = '\0';
	char content_file_line[100];
	//Get all the file
	while(fgets(content_file_line, sizeof(content_file_line), file)) {
		if((strlen(content_file.data) + strlen(content_file_line)) >= content_file.size){
			printf("ERROR : content_file overflow !\n");
			exit(1);
		}
		strcat(content_file.data, content_file_line);
	}
	size_t len = strlen(content_file.data);
	if(strlen(content_file.data)+1 >= content_file.size){
		printf("ERROR : content_file overflow !\n");
		exit(1);
	}
	else{
		content_file.data[len] = ' ';
		content_file.data[len+1] = '\0';
	}

	fseek(file, 0, SEEK_SET);
	printf("Lexer begin\n");
	
	int is_adress = 0;
	int current_keyword_index = 0;
	size_t word_index = 0;
	size_t token_index = 0;
	size_t argument_count = 0;
	bool on_word = false;
	bool last_instruction_close = true;
	bool anotation = false;
	char word[max_argument_lenght];
	word[0] = '\0';
	char current_keyword[max_argument_lenght];
	current_keyword[0] = '\0';
	PosFile position_file = {1,1};
	PosFile last_end_word = {0,0};
	PosFile beginning_word = {0,0};
	PosFile last_keyword = {0,0};
	for(char *c = content_file.data; *c ; c++){
		printf("\"%c\"  ", *c);
		printf("%d\n", isSeparatorChar(*c));
		if(word_index >= max_argument_lenght){
			printf("ERROR : word_index out of range\n");
			exit(1);
		}
		
		if(token_index >= token_list.size){
			printf("ERROR : token_index out of range\n");
			exit(1);
		}
		
		if(!anotation){
			// If the char is a separator
			if(isSeparatorChar(*c) && on_word){
				printf("1 | ");
				word[word_index] = '\0';
				word_index = 0;
				on_word = false;
				// If it's an ARGUMENT
				if(findKeyword(word) == NOT_A_KEYWORD){
					printf("1.1 | ");
					argument_count++;
					is_adress = 1;
					if(word[0] >= '0' && word[0] <= '9'){
						is_adress = 0;
					}

					if(last_instruction_close){
						compilationError(5, word, ' ', beginning_word, 0, 0);
					}

					if(argument_count > ARGUMENT_NUMBER[current_keyword_index]){
						compilationError(8, current_keyword, ' ', last_keyword, argument_count, 0);
					}

					// If the first char of the word is not a prefix or a number
					if((word[0] < '0' || word[0] > '9') && !isPrefixChar(word[0])){
						printf("1.1.2 | ");
						compilationError(4, word, word[0], beginning_word, 0, 0);
					}
					
					// If the argument is all number
					if(!isNumber((word + is_adress))){
						compilationError(6, word, ' ', beginning_word, 0, 0);
					}
					
					if(word[0] >= '0' && word[0] <= '9'){
						token_list.data[token_index].type = VALUE;
					}
					else if(current_keyword_index > 14){

						if(word[0] == 'R' || word[0] == '@'){
							token_list.data[token_index].type = REGISTER_RAM_ADRESS;
						}

					}
					else{
						switch(word[0]){
							case 'R':
							token_list.data[token_index].type = REGISTER_ADRESS;
							
							break;

							case '@':
							token_list.data[token_index].type = RAM_ADRESS;
							break;
						}
					}
					switch(word[0]){
						case 'M':
						token_list.data[token_index].type = MEMORY_PROGRAM_ADRESS;
						break;

						case 'I':
						token_list.data[token_index].type = INPUT_ADRESS;
						break;

						case 'O':
						token_list.data[token_index].type = OUTPUT_ADRESS;
						break;
					}

					// argument_count - 1 because it's an index, not a count in this case
					if(token_list.data[token_index].type != ARGUMENT_ARCHITECTURE[current_keyword_index][argument_count - 1]){
						char current_enum[25];
						strcpy(current_enum, TOKEN_TYPE_NAME_TABLE[token_list.data[token_index].type]);
						compilationError(7, current_enum, ' ', beginning_word, current_keyword_index, argument_count - 1);
					}

					token_list.data[token_index].data = atoi(word + is_adress);
				}
				// If it's a KEYWORD
				else{ 
					printf("1.2 | ");
					// If an instruction was called without being closed
					if(last_instruction_close == false){
						printf("1.2.1 | ");
						compilationError(2, word, ' ', last_end_word, 0, 0);
					} 

					last_keyword = beginning_word;
					last_instruction_close = false;
					token_list.data[token_index].type = KEYWORD;
					token_list.data[token_index].data = findKeyword(word);
					strcpy(current_keyword, word);
					current_keyword_index = findKeyword(current_keyword);					
				}
				last_end_word = position_file;
				token_index++;
			}
			// If the charactere is not valid
			else if(!isValidChar(*c)){
				printf("2 | ");
				compilationError(1, "", *c, position_file, 0, 0);
			}
			// If the charactere is valid
			else if(!isSeparatorChar(*c)){
				printf("3 | ");
				if(!on_word){
					beginning_word = position_file;
				}
				word[word_index] = *c;
				word_index++;
				on_word = true;
			}

			switch(*c){
				// End of an instruction
				case ';':
				if(last_instruction_close){
					compilationError(9, word, ' ', position_file, 0, 0);
				}

				if(argument_count < ARGUMENT_NUMBER[current_keyword_index]){
					compilationError(3, current_keyword, *c, last_keyword, argument_count, 0);
				}
				last_instruction_close = true;
				current_keyword[0] = '\0';
				argument_count = 0;
				break;

				// Start of an anotation
				case '#':
				anotation = true;
				break;
			}
			

		}

		// If we change line
		if(*c == '\n'){
			position_file.line++;
			position_file.charactere = 1;
			anotation = false;
		}
		else{
			position_file.charactere++;
		}
		printf("\n");
		printf("WORD : \"%s\"\n", word);
		printf("C_WORD : \"%s\"\n", current_keyword);
		printf("-----------------\n");

	}
	if(last_instruction_close == false){ printf("4 | \n"); compilationError(2, word, ' ', last_end_word, 0, 0); }
	
	free(content_file.data);
	return token_list;
}

// MAIN

int main(){
    FILE *KCM;
    FILE *KASM;
	KCM = fopen(PATH_OUTPUT, "w");
	KASM = fopen(PATH_INPUT, "r");	
    if (!KASM || !KCM) {
		printf("ERROR : file failed to open");
		return 1;
	}
    
	lexer(KASM, MAX_INSTRUCTION_NUMBER, MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_LENGHT);
	
	//LEXER
    //TOKENIZER
    
    //Generate token from te standarize program
	
	
    fclose(KCM);
    fclose(KASM);
        
    printf("Compilation Done !\n");
    return 0;
}
