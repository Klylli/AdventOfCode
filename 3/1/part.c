#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

bool isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return true;
	return false;
}
bool isValid(char c){
	if(!isDigit(c) && c != '.') return true;
	return false;
}
bool checkNeighbours(char** input, int i, int j, int lines){
	int len = strlen(input[0]) - 1;
	bool valid = false;
	for(int y = -1; y < 2; y++){
		for(int x = -1; x < 2; x++){
			int newRow = i + y;
			int newCol = j + x;
			if(newRow < 0 || newCol < 0 || newRow >= lines || newCol >= len) continue;
			if(isValid(input[newRow][newCol])) valid = true;
		}
	}
	return valid;
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc-1], "r");
	char* line = NULL;
	size_t len = 0;
	char** input = malloc(sizeof(char*) * 140);
	int counter = 0;
	int sum = 0;
	while(getline(&line,&len,file) != -1){
		printf(line);
		input[counter] = line;
		counter++;
		line = NULL;
		len = 0;
	}
	int length = strlen(input[0]) - 1;
	for(int i = 0; i < counter; i++){
		for(int j = 0; j < length; j++){
			if(isDigit(input[i][j])){
				bool include = false;
				int k = j;
				while(k < length && isDigit(input[i][k])){
					if(checkNeighbours(input, i, k, counter)) include = true;
					k++;
				}
				k -= j;
				char* endptr;
				int num = (int) strtol(input[i]+j, &endptr, 10);
				//printf("%d ", num);
				j += k;
				if(include){
					printf("%d ", num);
					sum += num;	
				}
			} 
		}
	} 

	for(int i = 0; i < 140; i++) free(input[i]);
	free(input);
	fclose(file);
	printf("%d\n", sum);
	return 0;
}
