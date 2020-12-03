#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef enum tokenType {  Number, Plus_Operator, Minus_Operator, Multiply_Operator,
	                        Divide_Operator, Left_Paren, Right_Paren, Syntax_Error, none}tokenType;

typedef struct mathToken {
	tokenType mathType;
	double value;
}mathToken;

mathToken* syntax_error(mathToken** lexerOutput,
                        unsigned int col, char symbol) {
	printf("[!] SYNTAX ERROR: Unexpected '%c' symbol at %i , exiting\n", symbol, col);

	free(*lexerOutput);
	mathToken * error = (mathToken *)malloc(sizeof(mathToken));
	error[0].mathType = Syntax_Error;
	return error;
}

mathToken* lexInput(const char* str){
	unsigned int outputSize = 1;
	mathToken* output = (mathToken*)malloc(sizeof(mathToken) * outputSize);

	char digits[] = "0123456789";
	unsigned int length = strlen(str);

	unsigned int currToken = 0;
	unsigned int currTokenLength = 0;
	unsigned int currTokenValueSpace = 6;
	tokenType currTokenType;
	char* currTokenValueInString;

	//Run through every symbol in the input
	for(unsigned int i = 0; i <= length; i++) {


		//If the first symbol of a token is an Number
		if(strchr(digits, str[i]) != NULL) {
			if(currTokenLength == 0) {
				//just a random size for the token buffer
				currTokenValueInString = (char*)malloc(currTokenValueSpace);
				currTokenType = Number;

				currTokenValueInString[currTokenLength] = str[i];
				currTokenLength++;
			}

			else if(currTokenType == Number) {
				//if buffer runs out of space
				if(currTokenLength >= currTokenValueSpace) {
					currTokenValueInString = (char*)realloc(currTokenValueInString, currTokenValueSpace);
				}
				currTokenValueInString[currTokenLength] = str[i];
				currTokenLength++;

			}
		}

		else if(str[i] == '.') {
			if(currTokenType == Number) {
				if(currTokenLength >= currTokenValueSpace) {
					currTokenValueInString = (char*)realloc(currTokenValueInString, currTokenValueSpace);
				}
				currTokenValueInString[currTokenLength] = str[i];
				currTokenLength++;
			}
			else{
				return syntax_error(&output, i, str[i]);
			}
		}

		else if(str[i] == ' ') {
			//if there's a number that has been terminated by the symbol, make it a token
			if(currTokenLength > 0 ) {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				if(currTokenType == Number) {
					output[currToken].value = atof(currTokenValueInString);
				}

				printf("Створено новий токен [%i %lf]\n", output[currToken].mathType, output[currToken].value);

				currToken++;
				printf("%s", currTokenValueInString);
				free(currTokenValueInString);
				currTokenType = none;
				currTokenLength = 0;
			}
			else{
				continue;
			}
		}




	}

	return 0;
}

char* takeInput(){
	char * inputString = (char*)malloc(200+1);
	printf("Будь ласка, введіть алгебраїчний вираз. Максимум 200 символів. \n");
	printf("> ");
	char symbol = 0;
	int i = 0;
	while(i < 200 && symbol != '\n') {
		symbol = getchar();
		i++;
	}

	return inputString;
}

int main(){
	//takeInput();
	lexInput("5.5 6.7 ");
}
