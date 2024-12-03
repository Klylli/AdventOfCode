#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

bool isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return true;
	return false;
}
bool isValid(char c){
	if(!isDigit(c) && c != '.') return true;
	return false;
}
int checkNeighbours(char** input, int i, int j, int lines){
	int len = strlen(input[0]) - 1;
	int ans = 0;
	if(i - 1 >= 0){
		if(isDigit(input[i - 1][j])) ans++;
		else{
			if(j - 1 >= 0 && isDigit(input[i - 1][j - 1])) ans++;
			if (j + 1 < len && isDigit(input[i - 1][j + 1])) ans++;
		}
	}
	if(j - 1 >= 0 && isDigit(input[i][j - 1])) ans++;
	if( j + 1 < len && isDigit(input[i][j + 1])) ans++;
	if( i + 1 < lines){
		if(isDigit(input[i + 1][j])) ans++;
		else{
			if(j - 1 >= 0 && isDigit(input[i + 1][j - 1])) ans++;
			if( j + 1 < len && isDigit(input[i + 1][j + 1])) ans++;
		}
	}
	return ans;
}

int gearNumber(char** input, int i, int j, int lines){
	int len = strlen(input[0]) - 1;
	int num = 1;
	int result = 1;
	int leftRow = j - 1;
	int rightRow = j + 1;
	char* endptr;
	int neighbours = 0;
	//same row left
	while(leftRow > 0 && isDigit(input[i][leftRow]) &&isDigit(input[i][leftRow - 1])){
		leftRow--;
	}
	//if(leftRow >= 0) printf("in i leftRow: %d String: %s", leftRow, input[i] + leftRow);
	if(leftRow >= 0 && isDigit(input[i][leftRow])){
		endptr = NULL;
		num = (int) strtol(input[i]+leftRow, &endptr, 10);
		result*= num;
		neighbours++;	
	}
	//if(rightRow < len) printf("in i rightRow: %d String: %s", rightRow, input[i] + rightRow);
	//same row right

	if(rightRow < len && isDigit(input[i][rightRow])){
		endptr = NULL;
		num = (int) strtol(input[i] + rightRow, &endptr, 10);
		result *= num;
		neighbours++;	
	}
	//upper row
	if(i - 1 >= 0){
		//	printf("Upper row: %d exists\n", i - 1);
		// one number
		if(isDigit(input[i-1][j])){
			leftRow = j;
			while(leftRow - 1 > 0 && isDigit(input[i-1][leftRow]) && isDigit(input[i - 1][leftRow - 1])){
				leftRow--;
			}

			//if(leftRow >= 0) printf("in i - 1 leftRow: %d String: %s", leftRow, input[i - 1] + leftRow);
			endptr = NULL;
			num = (int) strtol(input[i - 1]+leftRow, &endptr, 10);
			result *= num;
			neighbours++;
		}
		else{
			//upper row left
			leftRow = j - 1;
			while(leftRow > 0 && isDigit(input[i - 1][leftRow])&&isDigit(input[i - 1][leftRow - 1])){	
				//printf("Leftrow: %d\n", leftRow);
				leftRow--;
			}

			//if(leftRow >= 0) printf("in i - 1 leftRow: %d String: %s", leftRow, input[i - 1] + leftRow);
			//if (leftRow >= 0) printf("Leftrow: %d, number: %s", leftRow, input[i - 1] + leftRow);
			if(leftRow >= 0 && isDigit(input[i - 1][leftRow])){
				endptr = NULL;
				num = (int) strtol(input[i - 1] + leftRow, &endptr, 10);
				result *= num;
				//printf("Num top left: %d\n", num);
				neighbours++;
			}
			rightRow = j + 1;
			//upper row right

			//if(rightRow < len) printf("in i rightRow: %d String: %s", rightRow, input[i - 1] + rightRow);
			if(rightRow < len && isDigit(input[i - 1][rightRow])){
				endptr = NULL;
				num = (int) strtol(input[i - 1] + rightRow, &endptr, 10);
				result *= num;
				neighbours++;
			}
		}
	}

	//lower row
	if(i + 1 < lines){
		//one number
		if(isDigit(input[i + 1][j])){
			leftRow = j;
			while(leftRow - 1 > 0 && isDigit(input[i + 1][leftRow]) &&isDigit(input[i + 1][leftRow - 1])){
				leftRow--;
			}

			//if(leftRow >= 0) printf("in i + 1 leftRow: %d String: %s", leftRow, input[i + 1] + leftRow);
			endptr = NULL;
			num = (int) strtol(input[i + 1] + leftRow, &endptr, 10);
			//printf("Lower row middle: %d\n", num);
			result *= num;
			neighbours++;
		}
		else{
			//lower left
			leftRow = j - 1;
			while(leftRow > 0 && isDigit(input[i + 1][leftRow])&&isDigit(input[i + 1][leftRow - 1])){
				leftRow--;
			}

			//if(leftRow >= 0) printf("in i + 1 leftRow: %d String: %s", leftRow, input[i + 1] + leftRow);
			if(leftRow >= 0 && isDigit(input[i + 1][leftRow])){
				endptr = NULL;
				num = (int) strtol(input[i + 1] + leftRow, &endptr, 10);
				result *= num;
				neighbours++;
			}
			//lower right
			rightRow = j + 1;

			//if(rightRow < len) printf("in i rightRow: %d String: %s", rightRow, input[i + 1] + rightRow);
			if(rightRow < len && isDigit(input[i + 1][rightRow])){
				endptr = NULL;
				num = (int) strtol(input[i + 1] + rightRow, &endptr, 10);
				result *= num;
				neighbours++;
			}
		}
	}
	if(neighbours == 2) return result;
	printf("Gear found with %d neighbours, in position %d %d\n", neighbours, i, j);
	return 0;
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc-1], "r");
	char* line = NULL;
	size_t len = 0;
	char** input = malloc(sizeof(char*) * 140);
	int counter = 0;
	int sum = 0;
	while(getline(&line,&len,file) != -1){
		printf("%s",line);
		input[counter] = line;
		counter++;
		line = NULL;
		len = 0;
	}
	int length = strlen(input[0]) - 1;
	for(int i = 0; i < counter; i++){
		for(int j = 0; j < length; j++){
			if(input[i][j] == '*'){
				//	printf("i: %d, j: %d \n",i,j); 
				//	if(checkNeighbours(input, i, j, counter) == 2){
				int num = gearNumber(input, i, j, counter);
				//printf("%d ", num);
				sum += num;		
				//	}
			} 
		}
	} 
	for(int i = 0; i < 140; i++) free(input[i]);
	free(input);
	fclose(file);
	printf("Solution: %d\n", sum);
	return 0;
}
