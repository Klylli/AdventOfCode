#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

bool equals(char** obj, char** cmp, int lines){
	bool equal = true;
	for(int i = 0; i < lines; i++){
		if(strcmp(obj[i], cmp[i]) != 0) equal = false;
	}
	return equal;
}

bool contains(char*** set, char** value, int amountInSet, int linesInValue){
	bool contains = false;
	for(int i = 0; i < amountInSet; i++){
		if(equals(set[i], value, linesInValue)) contains = true;
	}
	return contains;
}

void copyStateIntoSet(char*** set, char** state, int amountInSet, int linesInState){
	char** copy = malloc(sizeof(char*) * linesInState);
	for(int i = 0; i < linesInState; i++){
		copy[i] = malloc(strlen(state[0]) + 1);
		strcpy(copy[i], state[i]);
	}
	set[amountInSet] = copy;
}

int calcLoad(char** input, int lines){
	int sum = 0;
	for(int i = 0; i < lines; i++){
		for(int j = 0; j < strlen(input[0]) - 1; j++){
			if(input[i][j] == 'O') sum += lines - i;
		}
	}
	return sum;
}

void calcEndstate(char*** set, char** input, int cycleNumber, int amountInSet, int linesInInput){
	int sum = 0;
	for(int i = 0; i < amountInSet; i++){
		if(equals(set[i], input, linesInInput)){
			int idx = (1000000000 - cycleNumber) % (amountInSet - i); 
			sum = calcLoad(set[i + idx], linesInInput);	
		}
	}
	printf("%d\n", sum);
	for(int i = 0; i < linesInInput; i++){
		printf("%s", input[i]);
		free(input[i]);

	}

	exit(EXIT_SUCCESS);
}

void moveRockNorth(char** input, int currLine, int currRow){
	char above = input[currLine - 1][currRow];
	if(above == '#' || above == 'O') return;
	input[currLine - 1][currRow] = 'O';
	input[currLine][currRow] = '.';
}
void  moveRockWest(char** input, int currLine, int currRow){
	char left = input[currLine][currRow - 1];
	if(left == '#' || left == 'O') return;
	input[currLine][currRow - 1] = 'O';
	input[currLine][currRow] = '.';
}

void moveRockSouth(char** input, int currLine, int currRow){
	char down = input[currLine + 1][currRow];
	if(down == '#' || down == 'O') return;
	input[currLine + 1][currRow] = 'O';
	input[currLine][currRow] = '.';
}

void moveRockEast(char** input, int currLine, int currRow){
	char right = input[currLine][currRow + 1];
	if(right == '#' || right == 'O') return;
	input[currLine][currRow + 1] = 'O';
	input[currLine][currRow] = '.';
}



int main(int argc, char** argv){
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	int lines = 10;
	char** input = malloc(sizeof(char*) * lines);
	int lineCounter = 0;
	while(getline(&line, &len, file) != -1){
		if(lineCounter == lines){
			lines *= 10;
			input = realloc(input, sizeof(char*) * lines);
		}
		printf("%s", line);
		input[lineCounter] = line;
		lineCounter++;
		line = NULL;
		len = 0;
	}
	int setSize = 16;
	int amountInSet = 0;
	char*** set = malloc(sizeof(char**) * setSize);
	int length = strlen(input[0]) - 1;
	int x = 0;
	while(x < 1000000000){
		if(amountInSet == setSize){
			setSize *= 2;
			set = realloc(set, sizeof(char**) * setSize);
		}
		if(contains(set, input, amountInSet, lineCounter)) calcEndstate(set, input, x, amountInSet, lineCounter); 
		else{
			copyStateIntoSet(set, input, amountInSet, lineCounter);
			amountInSet++;
			x++;
		//	if(x % 100000 == 0 )printf("%d ", x);
			for(int i = 1; i < lineCounter; i++){
				for(int j = 0; j < length; j++){
					int currLine = i;
					while(currLine > 0 && input[currLine][j] == 'O'){
						moveRockNorth(input, currLine, j);
						currLine--;
					}
				}
			}
			for(int i = 1; i < length; i++){
				for(int j = 0; j < lineCounter; j++){
					int currRow = i;
					while(currRow > 0 && input[j][currRow] == 'O'){
						moveRockWest(input, j, currRow);
						currRow--;
					}
				}
			}
			for(int i = lineCounter - 2; i >= 0; i--){
				for(int j = 0; j < length; j++){
					int currLine = i;
					while(currLine < lineCounter - 1 && input[currLine][j] == 'O'){
						moveRockSouth(input, currLine, j);
						currLine++;
					}
				}
			}
			for(int i = length - 2; i >= 0; i--){
				for(int j = 0; j < lineCounter; j++){
					int currRow = i;
					while(currRow < length - 1 && input[j][currRow] == 'O'){
						moveRockEast(input, j, currRow);
						currRow++;
					}
				}
			}	

		}
	}


	int sum = calcLoad(input, lineCounter);
	printf("%d\n", sum);
	for(int i = 0; i < lineCounter; i++){
		printf("%s", input[i]);
		free(input[i]);

	}
	free(line);
	free(input);
	fclose(file);
	return 0;
}
