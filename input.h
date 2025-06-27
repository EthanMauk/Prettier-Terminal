#pragma once
#include <windows.h>
#include<stdio.h>

int Readf(char* FileName, char arr[100][100]);  //reads files line by line into array
char* GetInput(int inputLimit);  //custom input function to limit user input to console
