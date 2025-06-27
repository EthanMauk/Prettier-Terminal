#include "input.h"

int Readf(char* FileName, char array[100][100]) {			//stores info read from file to char array
	int i = 0;												//counter for number of lines in the file.
	FILE* inFile = NULL;									//file pointer for file location
	fopen_s(&inFile, FileName, "r");						//opens file for reading to our file pointer	 
	while (inFile != NULL && !feof(inFile) && i<100)		//checks for end of array and end of file
		fgets(array[i++], 100, inFile);						//copys the line from file to array, then increment
	return i;												//returns line counter
}

char* GetInput(int inputLimit) {							
	int character = 0; int index = 0;							//variables for incrementing and storing input
	char* inputBuffer = calloc(inputLimit + 1, sizeof(char));	//allocates memory for input 
	while ((character = _getch()) != EOF) {						//stores keyboard input into character
		if ((isgraph(character) || character == 32) && (index < inputLimit)) { //checks if character is valid and buffer has enough size
			putchar(character);									//displays character to screen
			inputBuffer[index++] = tolower(character);			//stores lowercase character, to compare to later | false positive dereferencing
		}														//ends if statement 
		else if ((character == 8) && (index > 0)) {				//if input is backspace, and there is a character to backspace
			putchar(character);									//moves cursor back once
			printf(" \b");										//prints backspace to screen
			inputBuffer[--index] = 0;							//removes last character from buffer
		}
		else if ((character == 13) || (character == 10)) {		//if character is enter 
			if (inputBuffer != NULL && inputBuffer[0] != NULL) {//if there is input to enter
				putchar(character);							    //print newline
				return inputBuffer;								//return buffer 
			}
		}
	}
	return NULL;												//return zero to signify error
}