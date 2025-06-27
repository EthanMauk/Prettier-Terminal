#include "output.h"
struct Pair { char text[CHAR_LIMIT]; int age; }; //helper struct assigns each string to an age

typedef struct BufferStruct {				//main struct defining the buffer type
	int count, size;						//attributes for read/write to buffer
	struct Pair at[MAX_BUFFER_SIZE];		//array for storing text and age of input
}Buffer;

static char* temp[MAX_BUFFER_SIZE] = { 0 };				//temp array for sorting buffer
static Buffer outputBuffer = { 0, OUTPUT_BUFFER_SIZE };	//story output buffer, top of screen
static Buffer inputBuffer = { 0, INPUT_BUFFER_SIZE };   //user input buffer, bottom of screen
int backgroundColor = 0;

void AddToBuffer(Buffer* buffer, char text[CHAR_LIMIT]) {		//adds text to buffer 
	int position = buffer->count++ % buffer->size;				//finds next element in circular array and increments
	for (int i = 0; i < buffer->size; i++) buffer->at[i].age++;	//increments every age in the buffer
	memcpy(buffer->at[position].text, text, CHAR_LIMIT);		//assigns next element in array to input
	buffer->at[position].age = 0;								//resets age to zero 
}

void SetBuffer(Buffer* buffer) {	//readies buffer for printing
	memset(temp, 0, sizeof(temp));		//resets temp array 
	for (int i = 0; i < buffer->size; i++)	//iterates through array
		temp[buffer->at[i].age] = buffer->at[i].text;	//sorts array to order of age
}

void PrintScreen(HANDLE window, int OVERRIDE) {
	static int a = 0; static int b = 0;					 //counts number of inputs into each buffer, init to zero once, as the buffers begin empty
	if (OVERRIDE) system("cls");						//rewrites screen if override is passed
	if (a != inputBuffer.count || OVERRIDE == TRUE) {  //only updates if window info has changed or override is called
		SetBuffer(&inputBuffer);				      //populates temp array with inputBuffer's info
		for (int i = 0; i < inputBuffer.size; i++) { //interates through buffer
			SetConsoleCursorPosition(window, (COORD) { 60, i + 20 }); //moves cursor to position
			Colorize(window, (i < inputBuffer.size / 2) ? 15 : (i < inputBuffer.size - 1) ? 7 : 8); //colors text based on position
			if (temp[i] != NULL) printf("%s%*c\n", temp[i], (UINT32)(50 - strlen(temp[i])), ' '); //prints each line padded with spaces 
		} a = inputBuffer.count;						 //sets buffer counter to current count
	}
	if (b != outputBuffer.count || OVERRIDE == TRUE) {  //only updates if window info has changed or override is called
		SetBuffer(&outputBuffer);
		int count = 0;
		for (int i = 0; i < outputBuffer.size; i++) {
			if (temp[i] && (temp[i][0] == '\n')) {
				count = i - 1;
				break;
			}
		}
		for (int i = 0; i < outputBuffer.size; i++) {
			if (temp[i] != NULL) {
				SetConsoleCursorPosition(window, (COORD) { 15, i + 3 });
				printf("%*c", 100, ' ');
				SetConsoleCursorPosition(window, (COORD) { 15, i + 3 });
				Colorize(window, (i > count) ? 8 : 15);
				if (temp[i] && (temp[i][0] == '\n')) Spacer();
				else printf("%s%*c", temp[i], (120), ' ');
			}
		} b = outputBuffer.count;
	}
	SetConsoleCursorPosition(window, (COORD) { 15, 20 });
	Colorize(window, 7);
	printf(">>%*C", 40, ' ');
	SetConsoleCursorPosition(window, (COORD) { 15 + 3, 20 });
}
void BufferInput(char text[CHAR_LIMIT]) { AddToBuffer(&inputBuffer, text); }  //wrapper function
void BufferOutput(char text[CHAR_LIMIT]) { AddToBuffer(&outputBuffer, text); }  //wrapper function
void Colorize(HANDLE window, int color) { SetConsoleTextAttribute(window, (color + (backgroundColor * 16))); }  //helper function for printscreen
void SetBackgroundColor(int color) { backgroundColor = color; } //helper function for printscreen
void Spacer() { printf(" -----------------------------------------------------------------------------------"); } //helper function for printscreen
