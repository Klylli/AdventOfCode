#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int isDigit(char c){
char c2 = c - '0';
if(c2 >= 0 && c2 < 10) return 1;
return 0;
}

int main(int argc, char** argv){
	int sum = 0;
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	while(getline(&line, &len, file) != -1){
		int length = strlen(line);
		//printf("%s %d ",line, length);
		if(length <= 1) continue;
		char* onlyDigits = malloc(length + 1);
		memset(onlyDigits,0,length+1);
		int counter = 0;
		for(int i = 0; i < length; i++){
			if(isDigit(line[i])){
				onlyDigits[counter] = line[i];
				counter++;
			}
		}
		onlyDigits[counter] = '\0';
		//printf("%d: %s\n", counter, onlyDigits);
		sum += (int)((onlyDigits[0] - '0')*10) +(int) (onlyDigits[counter - 1] - '0');
		free(onlyDigits);
		free(line);
		line = NULL;
		len = 0;
	} 
	free(line);
	fclose(file);
	printf("%d\n",sum);
	return 0;
}
