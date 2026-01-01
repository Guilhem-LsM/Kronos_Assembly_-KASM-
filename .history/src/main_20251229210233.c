#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define PATH_INPUT "F:\\Prog\\C\\KASM Compiler\\input\\input.txt"
#define PATH_OUTPUT "F:\\Prog\\C\\KASM Compiler\\output\\output.txt"
#define MAX_INSTRUCTION_NUMBER 32768
#define MAX_ARGUMENT_NUMBER 4
#define MAX_ARGUMENT_LENGHT 8
#define KEYWORD_NUMBER 24
#define NOT_A_KEYWORD -1

enum TokenType{
	NONE,
	KEYWORD, 
	REGISTER_ADRESS, 
	RAM_ADRESS, 
	VALUE, 
	MEMORY_PROGRAM_ADRESS,
	OUTPUT_ADRESS,
	INPUT_ADRESS,
	INSTRUCTION_END
};

typedef struct Token {
		enum TokenType type;
		int data;
}Token;

typedef struct MCInstruction{
		char binary[16];
} MCInstruction;

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

KCM = fopen("F:\\Prog\\C\\KASM Compiler\\output", "w");
KASM = fopen("F:\\Prog\\C\\KASM Compiler\\input\\input.txt", "r");

const char VALID_CHAR[] = { 
	'A','B','C','D','E','F',
	'G','H','I','J','K','L',
	'M','N','O','P','Q','R',
	'S','T','U','V','W','X',
	'Y','Z','0','1','2','3',
	'4','5','6','7','8','9',
	' ', '#', '@'};
const unsigned int ARGUMENT_NUMBER[] = {
	0, 3, 3, 2, 2, 3, 3, 3, 2, 3, 3, 3, 3, 
	3, 3, 2, 2, 1, 2, 2, 2, 1, 0, 1};
const char *ARGUMENT_ARCHITECTURE[][24] = {
	{""},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_ADRESS", "REGISTER_ADRESS", "REGISTER_ADRESS"},
	{"REGISTER_RAM_ADRESS", "VALUE"},
	{"REGISTER_ADRESS", "MEMORY_PROGRAM_ADRESS"},
	{"MEMORY_PROGRAM_ADRESS"},
	{"OUTPUT_ADRESS", "REGISTER_RAM_ADRESS"},
	{"INPUT_ADRESS", "REGISTER_RAM_ADRESS"},
	{"REGISTER_RAM_ADRESS", "REGISTER_RAM_ADRESS"},
	{"REGISTER_RAM_ADRESS"},
	{""},
	{"REGISTER_RAM_ADRESS"}

};
const char KEYWORD_LIST[][24] ={
	{"NOP"},
	{"ADD"},
	{"SUB"},
	{"SHIFT_R"},
	{"SHIFT_L"},
	{"AND"},
	{"OR"},
	{"WOR"},
	{"NOT"},
	{"EQUAL"},
	{"INEQUAL"},
	{"SUP"},
	{"INF"},
	{"SUP_EQU"},
	{"INF_EQU"},
	{"LOAD"},
	{"IFGOTO"},
	{"JUMP"},
	{"OUT"},
	{"IN"},
	{"MOV"},
	{"PUSH"},
	{"POP"},
	{"S_STACK"}
	};

char toLower(char c){
	if(c >= 65 && c <= 90){
		return c + 32;
	}
	else{
		return c;
	}
}

bool* toBinary(unsigned int ui, size_t binary_size){
	bool *output = malloc(sizeof(bool)*binary_size);
	unsigned int ui_ = ui;
	for(int i = binary_size-1; i >= 0 ; i--){
		if(ui_- (int) pow(2,i) >= 0){
			output[i] = true;
			ui_ -= (int) pow(2,i);
		}
	}
	return output;
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

bool isCharValid(char c){
	bool output = false;
	for(int i = 0; i < 38 ; i++){
		if(VALID_CHAR[i] == c){
			output = true;
		}
	}
	return output;
}

int fileSize(FILE *file){
	int size = 0;
	char content_file_line[100];
	while(fgets(content_file_line, sizeof(content_file_line), file)) {
		for(char *c = content_file_line; *c ; c++){
			size++;
		}
		size += 2;
	}
	fseek(file, 0, SEEK_SET);
	return size;
}

void compilationError(int i, char *word, PosFile position_file){
	printf("\n");
	printf("COMPILATION ERROR %d\n", i);
	switch(i){
		case 1:
		printf("\';\' exprected\n");
		break;
		
		case 2:
		printf("Unknown instruction\n");
		break;
		
		case 3:
		printf("The address \"%s\" is not a number\n", (word+1));
		break;
		
		case 4:
		printf("\"%s\" is not a number\n", (word+1));
		break;
		
		case 5:
		printf("\"%c\" is not a prefix\n", word[0]);
		break;
	}
	
	printf("LINE : %d\n", position_file.line);
	printf("CHAR : %d\n", position_file.charactere);
	exit(1);
}

bool isNumber(char *s, int size){
	bool output = true;
	for(char *c = s; *c ; c++){
		if(*c < 48 || *c >57 ){output = false;}
	}
	return output;
}

TokenList lexer(
	FILE *file, 
	size_t max_instruction_number, 
	size_t max_argument_number,
	size_t max_argument_lenght
	){
	
	CharList content_file = {malloc(fileSize(file)), fseek(file, 0, SEEK_END)};
	if(!content_file.data){
		printf("ERROR : standarized_file allocation failed !\n");
	}
	
	TokenList token_list = {malloc(fileSize(file)), fileSize(file)};
	if(!token_list.data){
		printf("ERROR : standarized_file allocation failed !\n");
	}
	
	content_file.data[0] = '\0';
	char content_file_line[100];
	//Get all the 
	while(fgets(content_file_line, sizeof(content_file_line), file)) {
		for(char *c = content_file_line; *c ; c++){
			if(*c == '\r'){*c = ' ';}
		}
		strcat(content_file.data, content_file_line);
	}
	fseek(file, 0, SEEK_SET);
	
	printf("Lexer begin\n");
	
	size_t word_index = 0;
	size_t token_index = 0;
	size_t argument_count = 0;
	bool on_word = false;
	bool anotation = false;
	char word[max_argument_lenght];
	word[0] = '\0';
	char currenKeyword[max_argument_lenght];
	currenKeyword[0] = '\0';
	PosFile position_file = {1,1};
	PosFile last_end_word = {0,0};
	PosFile beginning_word = {0,0};
	for(char *c = content_file.data; *c ; c++){
		printf("%c\n", *c);
		if(word_index >= max_argument_lenght){
			printf("ERROR : word_index out of range\n");
			exit(1);
		}
		
		if(token_index >= token_list.size){
			printf("ERROR : token_index out of range\n");
			exit(1);
		}
		
		if(anotation){
			//do nothing
		}
		else if((*c == ' ' || *c == ',' || *c == '	' || *c == '#' || *c == ';') && on_word){
			word[word_index] = '\0';
			word_index = 0;
			
			if(findKeyword(word) != -1){
				if(currenKeyword[0] != '\0'){
					compilationError(1, word, last_end_word);
				}
				else {
					strcpy(currenKeyword, word);
					token_list.data[token_index].type = KEYWORD;
				}
			}
			else{
				if(currenKeyword[0] == '\0'){
					compilationError(2, word, beginning_word);
				}
				else{
					switch(word[0]){
						case 'R':
						if(isNumber(word, max_argument_lenght-1)){
							token_list.data[token_index].type = REGISTER_ADRESS;
							token_list.data[token_index].data = atoi(word+1);
						}
						else{
							compilationError(3, word, beginning_word);
						}
						break;
						case '@':
						if(isNumber(word, max_argument_lenght-1)){
							token_list.data[token_index].type = RAM_ADRESS;
							token_list.data[token_index].data = atoi(word+1);
						}
						else{
							compilationError(3, word, beginning_word);
						}
						break;
						case 'O':
						if(isNumber(word, max_argument_lenght-1)){
							token_list.data[token_index].type = OUTPUT_ADRESS;
							token_list.data[token_index].data = atoi(word+1);
						}
						else{
							compilationError(3, word, beginning_word);
						}
						case 'I':
						if(isNumber(word, max_argument_lenght-1)){
							token_list.data[token_index].type = INPUT_ADRESS;
							token_list.data[token_index].data = atoi(word+1);
						}
						else{
							compilationError(3, word, beginning_word);
						}
						break;
						case 'M':
						if(isNumber(word, max_argument_lenght-1)){
							token_list.data[token_index].type = MEMORY_PROGRAM_ADRESS;
							token_list.data[token_index].data = atoi(word+1);
						}
						else{
							compilationError(3, word, beginning_word);
						}
						break;
						default:
						if(word[0] > 47 && word[0] < 58){
							if(isNumber(word, max_argument_lenght)){
								token_list.data[token_index].type = VALUE;
								token_list.data[token_index].data = atoi(word);
							}
							else{
								compilationError(4, word, beginning_word);
							}
						}
						else{
							compilationError(5, word, beginning_word);
						}
						break;
					}
				}
			}
			last_end_word = position_file;
			on_word = false;
			token_index++;
		}
		switch(*c){
			case ' ' :
			if(!anotation){
			}
			break;
			
			case ';' :
			if(!anotation){
			}
			break;
			
			case '\n' :
			position_file.charactere = 1;
			position_file.line++;
			anotation = false;
			break;
				
			case '#' :
			if(!anotation){
			}
			break;
			
			default :
			if(!anotation){
				if(!on_word){
					beginning_word = position_file;
				}
				word[word_index] = *c;
				word_index++;
				on_word = true;
			}
			break;
		}
		position_file.charactere++;
	}
	
	free(content_file.data);
	return token_list;
}


int main(){
    FILE *KCM;
    FILE *KASM;
    if (!KASM || !KCM) {
		printf("ERROR : file failed to open");
		return 1;
	}

	printf(" uhiui %d %d", '0', '9');
    
	lexer(KASM, MAX_INSTRUCTION_NUMBER, MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_LENGHT);
	
	//LEXER
    //TOKENIZER
    
    //Generate token from te standarize program
	
	
    fclose(KCM);
    fclose(KASM);
        
    printf("Compilation Done !\n");
    return 0;
}
