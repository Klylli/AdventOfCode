#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

void moveRockToNextLine(char** input, int currLine, int currRow){
	char above = input[currLine - 1][currRow];
	if(above == '#' || above == 'O') return;
	input[currLine - 1][currRow] = 'O';
	input[currLine][currRow] = '.';
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
		input[lineCounter] = line;
		lineCounter++;
		line = NULL;
		len = 0;
	}
	int length = strlen(input[0]) - 1;
	for(int i = 1; i < lineCounter; i++){
		for(int j = 0; j < length; j++){
			int currLine = i;
			while(currLine > 0 && input[currLine][j] == 'O'){
				moveRockToNextLine(input, currLine, j);
				currLine--;
			}
		}
	}
	int sum = calcLoad(input, lineCounter);
	printf("%d\n", sum);
	for(int i = 0; i < lineCounter; i++) free(input[i]);
	free(line);
	free(input);
	fclose(file);
	return 0;
}
