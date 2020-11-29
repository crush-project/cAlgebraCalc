#include <stdio.h>
#include <malloc.h>
#include <string.h>

enum tokenType {  Number, Plus_Operator, Minus_Operator};

struct mathToken {
	tokenType mathType;
	int value();
};



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
	takeInput();

}
