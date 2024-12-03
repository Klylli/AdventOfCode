#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return 1;
	return 0;
}
/* one, two, six
 * zero, four, five, nine
 * three, seven, eight
 */

/*z: zero
 *o: one
 *t: two, three
 *f: four, five
 *s: six, seven
 *e: eight
 *n: nine
 */
void replaceNumbers(char* line, int length){
	printf("original: %s", line);
	for(int i = 0; i < length; i++){
		char c = line[i];
		switch(c){
			case 'z':
				if( (i + 3) < length && line[i + 1] == 'e' && line[i + 2] == 'r' && line[i + 3] == 'o'){
					line[i] = '0';
					//i += 3;
				}
				break;
			case 'o':
				if( (i + 2) < length && line[i + 1] == 'n' && line[i + 2] == 'e'){
					line[i] = '1';
					//i += 2;
				}
				break;
			case 't':
				if( (i + 2) < length && line[i + 1] == 'w' && line[i + 2] == 'o'){
					line[i] = '2';
					//i += 2;
				}
				else if( (i + 4) < length && line[i + 1] == 'h' && line[i + 2] == 'r' && line[i + 3] == 'e' && line[i + 4] == 'e'){
					line[i] = '3';
					//i += 4;
				}
				break;
			case 'f':	
				if( (i + 3) < length && line[i + 1] == 'o' && line[i + 2] == 'u' && line[i + 3] == 'r'){
					line[i] = '4';
					//i += 3;	
				}
				else if( (i + 3) < length && line[i + 1] == 'i' && line[i + 2] == 'v' && line[i + 3] == 'e'){
					line[i] = '5';
					//i += 3;

				}
				break;
			case 's':
				if( (i + 2) < length && line[i + 1] == 'i' && line[i + 2] == 'x'){
					line[i] = '6';
					//i += 2;
				}
				else if( (i + 4) < length && line[i + 1] == 'e' && line[i + 2] == 'v' && line[i + 3] == 'e' && line[i + 4] == 'n'){
					line[i] = '7';
					//i += 4;
				}
				break;
			case 'e':
				if( (i + 4) < length && line[i + 1] == 'i' && line[i + 2] == 'g' && line[i + 3] == 'h' && line[i + 4] == 't'){
					line[i] = '8';
					//i += 4;
				}
				break;
			case 'n':
				if( (i + 3) < length && line[i + 1] == 'i' && line[i + 2] == 'n' && line[i + 3] == 'e'){
					line[i] = '9';
					//i += 3;
				}
				break;
			default:
				continue;
		}
	}
	printf("converted: %s", line);
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
		replaceNumbers(line, length);
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
		printf("onlyDigits: %s\n", onlyDigits);
		sum += (int)((onlyDigits[0] - '0')*10) +(int) (onlyDigits[counter - 1] - '0');
		printf("%d\n\n",  (int)((onlyDigits[0] - '0')*10) +(int) (onlyDigits[counter - 1] - '0'));
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
