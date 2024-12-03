#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>

//12 red cubes, 13 green cubes, and 14 blue cubes
int isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return 1;
	return 0;
}

void isPossible(char c, int number, int* i, int* red, int* green, int* blue){
	switch(c){
		case 'r':
			*red = MAX(*red, number);
			*i += 3;	
			break;
		case 'g':
			*green = MAX(*green, number);
			*i += 5;
			break;
		case 'b':
			*blue = MAX(*blue, number);
			*i += 4;
			break;
		default:
			break;
	}
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
		int red = 0;
		int green = 0;
		int blue = 0;
		for(int i = 0; i < length; i++){
			int number;
			if(!isDigit(line[i])) continue;
			if(isDigit(line[i + 1])){
				number = (int) ((line[i] - '0')*10) + (int) ((line[i + 1] - '0'));
				isPossible(line[i + 3], number, &i, &red, &green, &blue);
				i+= 2;
			}
			else{
				number = (int) (line[i] - '0');
				isPossible(line[i + 2], number, &i, &red, &green, &blue);
				i++;
			}
		}	
		line = NULL;
		len = 0;
		int power = red * green * blue;
		sum += power;	
		++gameID;
	}
	printf("%d\n\n", sum);
	free(line);
	fclose(file);
	return 0;
}
