#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isDigit(char c){
	char c2 = c - '0';
	if(c2 >= 0 && c2 < 10) return true;
	return false;
}

bool contains(int* winning, int num, int length){
	for(int i = 0; i < length; i++){
		if(winning[i] == num) return true;
	}
	return false;
}

void printArray(int* arr, int length){
	for(int i = 0; i< length; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	int numbersWinning = 10;
	int numbersMine = 25;
	int winningNumbers[numbersWinning];
	int myNumbers[numbersMine];
	int sum = 0;
	int ticketNumber = 1;
	while(getline(&line, &len, file)!=-1){
		printf("Ticket number: %d\n", ticketNumber++);
		printf("%s", line);
		if(numbersWinning == 5) line += 8;
		else line += 10;		
		printf("%s", line);
		int length = strlen(line);
		int curr = 0;
		bool pre = true;
		int counter = 0;
		for(int i = 0; i < length; i++){
			if(line[i] == '|'){
				pre = false;
				counter = 0;
				continue;
			}
			if(line[i] == ' ') continue;
			if(pre){
				if(i + 1 < length && isDigit(line[i + 1])){
					int x = 10*(line[i] - '0') + line[i + 1] - '0';
					winningNumbers[counter] = x;
					//printf("%d\n", winningNumbers[counter]);
					i++;
				}
				else{
					winningNumbers[counter] = line[i] - '0';
				}
				counter++;
			}
			else{
				if(i + 1 < length && isDigit(line[i + 1])){
					myNumbers[counter] = 10*(line[i] - '0') + line[i + 1] - '0';
					i++;
				}
				else{
					myNumbers[counter] = line[i] - '0';
				}
				counter++;
				//printf("%d ", counter);
			}
		}
	//	printf("%d\n",winningNumbers[0]);
//		printArray(winningNumbers, numbersWinning);
//		printArray(myNumbers, numbersMine);
		for(int i = 0; i < numbersMine; i++){
			if(contains(winningNumbers, myNumbers[i], numbersWinning)){
					if(curr == 0) curr = 1;
					else curr*=2;
			}
		}
		sum += curr;
		line = NULL;
		len = 0;
	}
	printf("%d\n", sum);
	
	fclose(file);
	return 0;
}
