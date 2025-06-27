#pragma once
#include <windows.h>   //access window and cursor properties
#include <stdio.h>     //std input/output for console output
#include <string.h>    //formatting methods for char arrays
#include <conio.h>	   //extra char array methods

#define CHAR_LIMIT 100   
#define INPUT_BUFFER_SIZE 5   
#define OUTPUT_BUFFER_SIZE 15
#define MAX_BUFFER_SIZE (OUTPUT_BUFFER_SIZE > INPUT_BUFFER_SIZE)?OUTPUT_BUFFER_SIZE:INPUT_BUFFER_SIZE

void PrintScreen(HANDLE window, int OVERRIDE); //checks for changes in buffers and prints them, override prints them regardless of change
void Colorize(HANDLE window, int color);   //changes console text colors
void BufferInput(char text[CHAR_LIMIT]);	//adds text to input buffer 
void BufferOutput(char text[CHAR_LIMIT]);	//adds text to output buffer
void SetBackgroundColor(int color);			//changes background color
void Spacer();								//prints divider 

extern int backgroundColor;		//for user to control background color of the programs