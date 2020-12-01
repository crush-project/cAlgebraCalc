#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef enum tokenType {  Number, Plus_Operator, Minus_Operator, Multiply_Operator,
	                        Divide_Operator, Left_Paren, Right_Paren, Syntax_Error}tokenType;

typedef struct mathToken {
	tokenType mathType;
	double value;
}mathToken;



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

		if(currTokenLength == 0) {

			//If the first symbol of a token is an Number
			if(strchr(digits, str[i]) != NULL) {
				//just a random size for the token buffer
				currTokenValueInString = (char*)malloc(currTokenValueSpace);
				currTokenType = Number;

				currTokenValueInString[currTokenLength] = str[i];
				currTokenLength++;
			}

			else if(str[i] == '+') {
				currTokenType = Plus_Operator;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i +]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == '-') {
				currTokenType = Minus_Operator;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i -]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == '*') {
				currTokenType = Multiply_Operator;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i *]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == '/') {
				currTokenType = Divide_Operator;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i /]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == '(') {
				currTokenType = Left_Paren;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i (]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == ')') {
				currTokenType = Right_Paren;
				//if we now have more tokens than space in the output array, resize
				if(currToken >= outputSize) {
					outputSize*=2;
					output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
				}
				output[currToken].mathType = currTokenType;

				printf("Створено новий токен [%i )]\n", output[currToken].mathType);

				currToken++;
				currTokenLength = 0;
			}

			else if(str[i] == ' ') continue;

			else{
				//TODO: move to a dedicated function
				printf("[!] SYNTAX ERROR: Unexpected '%c' symbol at %i , exiting\n", str[i], i);
				mathToken * error = (mathToken *)malloc(sizeof(mathToken));
				error[0].mathType = Syntax_Error;
				return error;
			}

		}
		//if this isn't the first symbol anymore
		else{

			if(currTokenType == Number) {
				//Yet another number, so we add it to the value
				if((strchr(digits, str[i]) != NULL) || (str[i] == '.')) {
					//if buffer runs out of space
					if(currTokenLength >= currTokenValueSpace) {
						currTokenValueInString = (char*)realloc(currTokenValueInString, currTokenValueSpace);
					}
					currTokenValueInString[currTokenLength] = str[i];
					currTokenLength++;
				}

				//TODO
				//in this case, a right parenthesis can also terminate a number
				//there's probably a smarter way to do this
				else if(str[i] == ')') {

					//if we now have more tokens than space in the output array, resize
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
					currTokenLength = 0;


					currTokenType = Right_Paren;
					//if we now have more tokens than space in the output array, resize
					if(currToken >= outputSize) {
						outputSize*=2;
						output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
					}
					output[currToken].mathType = currTokenType;

					printf("Створено новий токен [%i )]\n", output[currToken].mathType);

					currToken++;
					currTokenLength = 0;
				}

				//Not a number, so we call it a token (Yes, I will manually append a space
				//before the null terminator, i'm just not very smart)
				else if(str[i] == ' ') {
					//if we now have more tokens than space in the output array, resize
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
					currTokenLength = 0;
				}



				else{
					printf("[!] SYNTAX ERROR: Unexpected '%c' symbol at %i , exiting\n", str[i], i);
					mathToken * error = (mathToken *)malloc(sizeof(mathToken));
					error[0].mathType = Syntax_Error;
					return error;
				}
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
	lexInput("5.5 - 7.4123 - (7 + 6) * 5 / 8.99 ");
}
