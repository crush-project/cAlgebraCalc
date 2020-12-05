#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum tokenType {  Number, Plus_Operator, Minus_Operator, Multiply_Operator,
	                        Divide_Operator, Power_Operator,
	                        Left_Paren, Right_Paren, Syntax_Error, none}tokenType;

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

	unsigned int length = strlen(str);

	unsigned int currToken = 0;
	unsigned int currTokenLength = 0;
	unsigned int currTokenValueSpace = 6;
	tokenType currTokenType;
	char* currTokenValueInString;

	//Run through every symbol in the input
	for(unsigned int i = 0; i <= length; i++) {
		if(i == length) {
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
				free(currTokenValueInString);
				currTokenType = none;
				currTokenLength = 0;
			}

			break;
		}

		//If the first symbol of a token is an Number
		if(isdigit(str[i])) {
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

		else {
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
				free(currTokenValueInString);
				currTokenType = none;
				currTokenLength = 0;
			}
			if(str[i] == ' ' || str[i] == '\n') {
				continue;
			}

			else if(str[i] == '+') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Plus_Operator;
				printf("Створено новий токен [%i +]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == '-') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Minus_Operator;
				printf("Створено новий токен [%i -]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == '*') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Multiply_Operator;
				printf("Створено новий токен [%i *]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == '/') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Divide_Operator;
				printf("Створено новий токен [%i /]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == '(') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Left_Paren;
				printf("Створено новий токен [%i (]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == ')') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Right_Paren;
				printf("Створено новий токен [%i )]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else if(str[i] == '^') {
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}

				output[currToken].mathType = Power_Operator;
				printf("Створено новий токен [%i ^]\n", output[currToken].mathType);

				currToken++;
				currTokenType = none;
				currTokenLength = 0;
			}

			else{
				return syntax_error(&output, i, str[i]);
			}

		}

	}

	return output;
}

char* takeInput(){
	char * inputString = (char*)malloc(200+2);
	printf("Будь ласка, введіть алгебраїчний вираз. Максимум 200 символів. \n");
	printf("input > ");
	int i = 0;
	char symbol = 0;
	while(i < 200) {
		if(symbol == '\n' || symbol == EOF) {break;}
		else{
			symbol = getchar();
			inputString[i] = symbol;
			i++;
		}
	}
	return inputString;
}

int main(){
	lexInput(takeInput());

	return 0;
}
