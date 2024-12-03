#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>



int main(int argc, char** argv){
FILE* file = fopen(argv[argc - 1], "r");
char* line = NULL;
size_t len = 0;
getline(&line, &len, file);
int length = strlen(line) + 1;
//printf("%ld %d\n", len, length);
int sum = 0;
int currSum = 0;
int counter = 0;
for(int i = 0; i < length; i++){
	if(line[i] == '\n') continue;
	if(line[i] == ',' || i == length - 1){
		sum += currSum;
		counter++;
		currSum = 0;
		continue;
	}
	currSum += line[i];
	currSum *= 17;
	currSum %= 256;
}

printf("%d %d\n", sum, counter);
free(line);
fclose(file);
}
