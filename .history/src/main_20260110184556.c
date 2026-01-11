#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INSTRUCTION_NUMBER 32768
#define MAX_ARGUMENT_NUMBER 4
#define MAX_ARGUMENT_LENGHT 8
#define KEYWORD_NUMBER 24
#define NOT_A_KEYWORD -1
#define VALID_CHAR_NUMBER 42
#define SEPERATIR_CHAR_NUMBER 5
#define PREFIX_CHAR_NUMBER 5

#ifdef _WIN32
	#define WHICH_OS 1
	#include <windows.h>
	#include <libloaderapi.h>
#elif __linux__
	#define WHICH_OS 2
	#include <unistd.h>
#else  
	#define WHICH_OS 0
#endif

// ENUMS

enum TokenType{
	NONE = 0,
	KEYWORD = 1, 
	REGISTER_ADRESS, 
	RAM_ADRESS, 
	REGISTER_OR_RAM_ADRESS, 
	VALUE, 
	MEMORY_PROGRAM_ADRESS,
	OUTPUT_ADRESS,
	INPUT_ADRESS
};

// STRUCTS

typedef struct Token {
		enum TokenType type;
		int data;
		bool pointer;
}Token;

typedef struct Hexa{
	char *data;
} Hexa;

// The LSB is the first char of the string
typedef struct Binary{
	char *data;
	size_t size;
} Binary;

typedef struct BinaryPosition{
	int which_word;
	int start_bit;
	size_t binary_size;
} BinaryPosition;

typedef struct CharList{
	char *data;
	size_t size;
	
}CharList;

typedef struct TokenList{
	Token *data;
	size_t size; 
	size_t instruction_number;
}TokenList;

typedef struct HexaList{
	Hexa *data;
	size_t size;
}HexaList;

typedef struct BinaryList{
	Binary *data;
	size_t size;
}BinaryList;

typedef struct PosFile{
	int line;
	int charactere;
} PosFile;

// CONST DATAS

const Binary EMPTY_BINARY = {"0000000000000000", 16};

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
	'R', '@', 'L', 'I', 'O'
};

const unsigned int ARGUMENT_NUMBER[] = {
	0, 3, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 
	3, 3, 2, 2, 1, 2, 2, 2, 1, 0, 1
};

const enum TokenType ARGUMENT_ARCHITECTURE[24][25] = {
	{NONE},												 // 0 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 1 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 2
	{REGISTER_ADRESS, REGISTER_ADRESS},					 // 3 
	{REGISTER_ADRESS, REGISTER_ADRESS},					 // 4 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 5 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 6 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 7 
	{REGISTER_ADRESS, REGISTER_ADRESS},					 // 8 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 9 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 10 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 11 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 12 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 13 
	{REGISTER_ADRESS, REGISTER_ADRESS, REGISTER_ADRESS}, // 14
	{REGISTER_OR_RAM_ADRESS, VALUE},					 // 15
	{REGISTER_ADRESS, MEMORY_PROGRAM_ADRESS},			 // 16
	{MEMORY_PROGRAM_ADRESS},							 // 17
	{OUTPUT_ADRESS, REGISTER_OR_RAM_ADRESS},			 // 18
	{INPUT_ADRESS, REGISTER_OR_RAM_ADRESS},				 // 19
	{REGISTER_OR_RAM_ADRESS, REGISTER_OR_RAM_ADRESS},	 // 20
	{REGISTER_OR_RAM_ADRESS},							 // 21
	{NONE},												 // 22
	{REGISTER_OR_RAM_ADRESS}							 // 23
};

const BinaryPosition BINARY_ARCHITECTURE[24][4] = {
	{{0, 0, 5}},									// 0
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 1
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 2
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}},				// 3
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}},				// 4
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 5
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 6
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 7
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}},				// 8
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 9
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 10
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 11
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 12
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 13
	{{0, 0, 5}, {0, 5, 5}, {0, 10, 5}, {1, 0, 5}},	// 14
	{{0, 0, 5}, {1, 0, 16}, {2, 0, 16}},			// 15
	{{0, 0, 5}, {0, 5, 5}, {1, 0, 16}},				// 16
	{{0, 0, 5}, {1, 0, 16}},						// 17
	{{0, 0, 5}, {0, 5, 4}, {1, 0, 16}},				// 18
	{{0, 0, 5}, {0, 5, 4}, {1, 0, 16}},				// 19
	{{0, 0, 5}, {1, 0, 16}, {2, 0, 16}},			// 20
	{{0, 0, 5}, {1, 0, 16}},						// 21
	{{0, 0, 5}},									// 22
	{{0, 0, 5}, {1, 0, 16}}							// 23
};

const char KEYWORD_LIST[24][8] = {
	{"NOP"}, {"ADD"}, {"SUB"},
	{"SHIFT_R"}, {"SHIFT_L"}, {"AND"},
	{"OR"}, {"WOR"}, {"NOT"}, {"EQUAL"},
	{"UNEQUAL"}, {"SUP"}, {"INF"},
	{"SUP_EQU"}, {"INF_EQU"}, {"LOAD"},
	{"IFGOTO"}, {"JUMP"}, {"OUT"},
	{"IN"}, {"MOV"}, {"PUSH"},
	{"POP"}, {"S_STACK"}
};

const char TOKEN_TYPE_NAME_TABLE[9][23] = {
	{"NONE"},
	{"KEYWORD"},
	{"REGISTER_ADRESS"},
	{"RAM_ADRESS"},
	{"REGISTER_OR_RAM_ADRESS"},
	{"VALUE"},
	{"MEMORY_PROGRAM_ADRESS"},
	{"OUTPUT_ADRESS"},
	{"INPUT_ADRESS"}
};

// FUNCTIONS

char* decimalToBinary(int decimal_value, size_t binary_size){
	if(binary_size > 16){
		printf("ERROR : Binary size too high");
		exit(1);
	}
	char *binary_number = malloc(17 * sizeof(char));
	for(int i = 0; i < binary_size; i++){
		if((decimal_value - (int)pow(2, ((binary_size -1) - i))) >= 0){
			binary_number[(binary_size -1) - i] = '1';
			decimal_value -= (int)pow(2, ((binary_size -1) - i));
			
		}
		else{
			binary_number[(binary_size -1) - i] = '0';
		}
	}

	binary_number[binary_size] = '\0';

	return binary_number;
}

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
		printf("	ADRESS : R, @, L, I, O\n");
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

		case 10 :
		printf("Identifier too long\n");
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
	
	TokenList token_list = {malloc(max_instruction_number * max_argument_number * sizeof(Token)), max_instruction_number * max_argument_number, 0};
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
	size_t insutrciton_count = 0;
	bool on_word = false;
	bool last_instruction_close = true;
	bool anotation = false;
	bool is_pointer = false;
	char word[max_argument_lenght];
	word[0] = '\0';
	char current_keyword[max_argument_lenght];
	current_keyword[0] = '\0';
	PosFile position_file = {1,1};
	PosFile last_end_word = {0,0};
	PosFile beginning_word = {0,0};
	PosFile last_keyword = {0,0};
	for(char *c = content_file.data; *c ; c++){
		// Check Overflow for word
		if(word_index >= max_argument_lenght){
			// Identifier too long
			compilationError(10, word, ' ', beginning_word, 0, 0);
			exit(1);
		}
		
		// Check Overflow for token list
		if(token_index >= token_list.size){
			printf("ERROR : token_index out of range\n");
			exit(1);
		}
		
		if(!anotation){
			// If the char is a separator
			if(isSeparatorChar(*c) && on_word){
				word[word_index] = '\0';
				word_index = 0;
				on_word = false;
				// If it's an ARGUMENT
				if(findKeyword(word) == NOT_A_KEYWORD){
					argument_count++;
					is_adress = 1;
					if(word[0] >= '0' && word[0] <= '9'){
						is_adress = 0;
					}

					if(last_instruction_close){
						// Invalid instruction Keyword
						compilationError(5, word, ' ', beginning_word, 0, 0);
					}

					if(argument_count > ARGUMENT_NUMBER[current_keyword_index]){
						// Too many arguments
						compilationError(8, current_keyword, ' ', last_keyword, argument_count, 0);
					}

					// If the first char of the word is not a prefix or a number
					if((word[0] < '0' || word[0] > '9') && !isPrefixChar(word[0])){
						printf("1.1.2 | ");
						// Not valid prefix
						compilationError(4, word, word[0], beginning_word, 0, 0);
					}
					
					// If the argument is all number
					if(!isNumber((word + is_adress))){
						// Argument is not an address or a value
						compilationError(6, word, ' ', beginning_word, 0, 0);
					}
					
					if(word[0] >= '0' && word[0] <= '9'){
						token_list.data[token_index].type = VALUE;
					}
					
					switch(word[0]){
						case 'R':
						token_list.data[token_index].type = REGISTER_ADRESS;
						break;

						case '@':
						token_list.data[token_index].type = RAM_ADRESS;
						break;

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
					char current_enum[25];
					strcpy(current_enum, TOKEN_TYPE_NAME_TABLE[token_list.data[token_index].type]);
					if(ARGUMENT_ARCHITECTURE[current_keyword_index][argument_count - 1] == REGISTER_OR_RAM_ADRESS){
						if(token_list.data[token_index].type != REGISTER_ADRESS && token_list.data[token_index].type != RAM_ADRESS){
							// Wrong type of argument
							compilationError(7, current_enum, ' ', beginning_word, current_keyword_index, argument_count - 1);
						}
					}
					else if(token_list.data[token_index].type != ARGUMENT_ARCHITECTURE[current_keyword_index][argument_count - 1]){
						// Wrong type of argument
						compilationError(7, current_enum, ' ', beginning_word, current_keyword_index, argument_count - 1);
					}

					token_list.data[token_index].data = atoi(word + is_adress);
				}
				// If it's a KEYWORD
				else{ 
					// If an instruction was called without being closed
					if(last_instruction_close == false){
						// ‘;’ expected
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
				// charactere not valid
				compilationError(1, "", *c, position_file, 0, 0);
			}
			// If the charactere is valid
			else if(!isSeparatorChar(*c)){
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
					// ‘;’ unexpected
					compilationError(9, word, ' ', position_file, 0, 0);
				}

				if(argument_count < ARGUMENT_NUMBER[current_keyword_index]){
					// Arguments missing
					compilationError(3, current_keyword, *c, last_keyword, argument_count, 0);
				}
				insutrciton_count++;
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

	}													   // ‘;’ expected
	if(last_instruction_close == false){ printf("4 | \n"); compilationError(2, word, ' ', last_end_word, 0, 0); }
	free(content_file.data);
	token_list.instruction_number = insutrciton_count;
	printf("Total instruction : %d\n", insutrciton_count);
	return token_list;
}

HexaList machineCodeEncoder(
	size_t max_instruction_number, 
	size_t max_argument_number,
	size_t max_argument_lenght,
	TokenList token_list
){

	printf("Machine code encoder begin\n");

	BinaryList machine_code_binary = {malloc(token_list.instruction_number * 3 * sizeof(Binary)), token_list.instruction_number * 3};
	for(int i = 0; i < machine_code_binary.size ; i++){
		machine_code_binary.data[i].data = NULL;
	}

	HexaList machine_code_hexa;
	size_t indentifier_index = 0;
	int instruction_index = -1;
	int instruction_id = 0;
	for(int i = 0; i < token_list.size ; i++){
		if(token_list.data[i].type == 0){break;}

		if(token_list.data[i].type == KEYWORD){ 
			instruction_id = token_list.data[i].data;
			indentifier_index = 0;
			instruction_index++;
		}

		if(machine_code_binary.data[instruction_index * 3].data == NULL){
			for(int l = 0; l < 3; l++){
				if(instruction_index * 3 + l >= machine_code_binary.size){
					printf("ERROR : machine_code_binary overflow !");
					exit(1);
				}
				char *c = malloc(17 * sizeof(char));
				strcpy(c, "0000000000000000");
				machine_code_binary.data[instruction_index * 3 + l].data = c;
			}
		}


		char *binary_value = decimalToBinary(token_list.data[i].data, BINARY_ARCHITECTURE[instruction_id][indentifier_index].binary_size);

		memcpy(((machine_code_binary.data + (instruction_index * 3) + BINARY_ARCHITECTURE[instruction_id][indentifier_index].which_word)->data + BINARY_ARCHITECTURE[instruction_id][indentifier_index].start_bit), binary_value, (size_t)BINARY_ARCHITECTURE[instruction_id][indentifier_index].binary_size);
		free(binary_value);

		indentifier_index++;
	}

	printf("MACHINE CODE BINARY\n");
	for(Binary *b = machine_code_binary.data; b->data != NULL ; b++){
		printf("%s\n", b->data);
	}

	return machine_code_hexa;
}

// MAIN

int main(int argc, char *argv[]){

	if(!WHICH_OS){
		printf("ERROR : Unsuported OS\n");
	}

	char PROGRAM_PATH[1000];
	char INPUT_PATH[1000];
	char OUTPUT_PATH[1000];
	#ifdef _WIN32
		GetModuleFileNameA(NULL, PROGRAM_PATH, 1000);
		size_t index_path = strlen(PROGRAM_PATH);
		while(PROGRAM_PATH[index_path] != '\\'){
			index_path--;
		}
		PROGRAM_PATH[index_path+1] = '\0';
		strcpy(INPUT_PATH, PROGRAM_PATH);
		strcpy(OUTPUT_PATH, PROGRAM_PATH);
		strcat(INPUT_PATH, "input\\input.txt");
		strcat(OUTPUT_PATH, "output\\output.txt");
	#else
		int index_path = readlink("/proc/self/exe", PROGRAM_PATH, 1000);
		if(index_path != -1){
			PROGRAM_PATH[index_path] = '\0';
		}
		while(PROGRAM_PATH[index_path] != '/'){
			index_path--;
		}
		PROGRAM_PATH[index_path+1] = '\0';
		strcpy(INPUT_PATH, PROGRAM_PATH);
		strcpy(OUTPUT_PATH, PROGRAM_PATH);
		strcat(INPUT_PATH, "input/input.txt");
		strcat(OUTPUT_PATH, "output/output.txt");
	#endif

	printf("INPUT PATH : %s\n", INPUT_PATH);
	printf("OUTPUT PATH : %s\n", OUTPUT_PATH);

    FILE *KCM;
    FILE *KASM;
	KCM = fopen(OUTPUT_PATH, "w");
	KASM = fopen(INPUT_PATH, "r");	
    if (!KASM || !KCM) {
		printf("ERROR : file failed to open");
		return 1;
	}
    
	TokenList token_list;
	token_list = lexer(KASM, MAX_INSTRUCTION_NUMBER, MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_LENGHT);
	
	machineCodeEncoder(MAX_INSTRUCTION_NUMBER, MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_LENGHT, token_list);

	//LEXER
    //TOKENIZER
    
    //Generate token from te standarize program
	
	
    fclose(KCM);
    fclose(KASM);
    free(token_list.data);
    printf("Compilation Done !\n");
    return 0;
}
