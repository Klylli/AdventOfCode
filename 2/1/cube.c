#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

//12 red cubes, 13 green cubes, and 14 blue cubes
int isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return 1;
	return 0;
}

bool isPossible(char c, int number, int* i){
	switch(c){
		case 'r':
			if(number <= 12){
				*i += 3;
				return true;
			}	
			break;
		case 'g':
			if(number <= 13){
				*i += 5;
				return true;
			}
			break;
		case 'b':
			if(number <= 14){
				*i += 4;
				return true;
			}
			break;
		default:
			break;
	}
	return false;
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	int gameID = 1;
	int sum = 0;
	while(getline(&line, &len, file) != -1){
		printf("%d\n", gameID);
		printf("original: %s",line);
		if(gameID < 10) line += 8;
		else if(gameID >= 100) line += 10;
		else line += 9;
		printf("cut: %s", line);
		int length = strlen(line);
		bool b = true;
		for(int i = 0; i < length && b; i++){
			int number;
			if(!isDigit(line[i])) continue;
			if(isDigit(line[i + 1])){
				number = (int) ((line[i] - '0')*10) + (int) ((line[i + 1] - '0'));
				b = isPossible(line[i + 3], number, &i);
				i+= 2;
			}
			else{
				number = (int) (line[i] - '0');
				b = isPossible(line[i + 2], number, &i);
				i++;
			}
		}	
		line = NULL;
		len = 0;
		if(b) sum += gameID;	
		++gameID;
	}
	printf("%d\n\n", sum);
	free(line);
	fclose(file);
	return 0;
}
