#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

typedef enum tokenType {  Number, Plus_Operator, Minus_Operator}tokenType;

typedef struct mathToken {
	tokenType mathType;
	int value;
}mathToken;

mathToken* lexInput(const char* str){
	unsigned int outputSize = 1;
	mathToken* output = (mathToken*)malloc(sizeof(mathToken) * outputSize);

	char digits[] = "0123456789";
	unsigned int length = strlen(str);

	unsigned int currToken = 0;
	unsigned int currTokenLength = 0;
	tokenType currTokenType;
	char* currTokenValueInString;

	for(unsigned int i = 0; i <= length; i++) {


		if(currTokenLength == 0) {

			//If the first symbol of a token is a number
			if(strchr(digits, str[i]) != NULL) {
				currTokenValueInString = (char*)malloc(10);
				currTokenType = Number;
				currTokenValueInString[currTokenLength] = str[i];
				currTokenLength++;
			}
		}

		else{

			if(currTokenType == Number) {
				//Yet another number, so we add it to the value
				if(strchr(digits, str[i]) != NULL) {
					currTokenValueInString[currTokenLength] = str[i];
					currTokenLength++;
				}

				//Not a number, so we call it a token
				else{
					//if we now have more tokens than space in the output array, resize
					if(currToken > outputSize) {
						outputSize*=2;
						output = (mathToken*)realloc(output, sizeof(mathToken) * outputSize);
					}
					output[currToken].mathType = currTokenType;

					if(currTokenType == Number) {
						output[currToken].value = atoi(currTokenValueInString);
					}

					printf("Створено новий токен [%i %i]\n", output[currToken].mathType, output[currToken].value);

					currToken++;
					free(currTokenValueInString);
					currTokenLength = 0;
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
	lexInput("5 + 5 ");
}
