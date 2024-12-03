#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int hashCode(char* line, int length){
	int sum = 0;
	int currSum = 0;
	for(int i = 0; i < length; i++){
		if(line[i] == '\n') continue;
		if(line[i] == ',' || i == length - 1){
			sum += currSum;
			currSum = 0;
			continue;
		}
		currSum += line[i];
		currSum *= 17;
		currSum %= 256;
	}
	return sum;
}

typedef struct{
	char label[2];
	int fl;
}lens;

typedef struct{
	int capacity;
	int amountInBox;
	lens* lenses;
}box;

void initBox(box* currBox){
	currBox->capacity = 8;
	currBox->amountInBox = 0;
	currBox->lenses = malloc(sizeof(lens) * 8);
	for(int i = 0; i < 8; i++){
		strcpy((currBox->lenses)[i].label, "  ");
	}
}

bool contains(box* currBox, char* lbl){
	bool contained = false;
	for(int i = 0; i < currBox->amountInBox; i++){
		if(strcmp(lbl, (currBox->lenses)[i].label) == 0) contained = true;
	 }
	return contained;
}

void removeFromBox(box* currBox, char* lbl){
	bool found = false;
	for(int i = 0; i < currBox->amountInBox; i++){
		if(strcmp(lbl, (currBox->lenses)[i].label) == 0){
		found = true;
		continue;
		}
		if(found){
			(currBox->lenses)[i - 1] = (currBox->lenses)[i];
		} 
	}
	currBox->amountInBox -= 1;
}

bool addIntoBox(box* currBox, char* lbl, int focal, lens* newLens){
	if(currBox->amountInBox == currBox->capacity){
		currBox->capacity *= 2;
		currBox->lenses = realloc(currBox->lenses, sizeof(lens)*currBox->capacity);
		for(int i = currBox->amountInBox; i < currBox->capacity; i++){
			strcpy((currBox->lenses)[i].label, "  ");
		}
		printf("Increased size to %d\n", currBox->capacity);
	}
	bool new = false;
	if(contains(currBox, lbl)){
		for(int i = 0; i < currBox->amountInBox; i++){
			if(strcmp(lbl, (currBox->lenses)[i].label) == 0){
				(currBox->lenses)[i].fl = focal;
				
			}
		}
	}
	else{
		strcpy(newLens->label, lbl);
		newLens->fl = focal;
		new = true;
	}
	return new;
}

int calcPower(box* currBox, int boxNumber){
	int power = 0;
	for(int i = 0; i < currBox->amountInBox; i++){
		power += (1 + boxNumber)*(i + 1)*((currBox->lenses)[i].fl);
	}	
	return power;
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	getline(&line, &len, file);
	int length = strlen(line) + 1;
	box boxes[256];
	for(int i = 0; i < 256; i++){
		initBox(&boxes[i]);
	}
	char currLabel[2];
	int counter = 0;
	for(int i = 0; i < length; i++){
		if(line[i] == '\n') continue;
		if(line[i] == ','){
			counter = 0;
			continue;
		}
		if(counter == 2){
			int boxNumber = hashCode(currLabel, 2);
			if(line[i] == '-'){
				if(contains(&boxes[boxNumber], currLabel)){
					removeFromBox(&boxes[boxNumber], currLabel);
				}
			}
		}
		else if(counter == 3){
			int boxNumber = hashCode(currLabel, 2);
			lens newLens;
			bool new = addIntoBox(&boxes[boxNumber], currLabel, line[i] - '0', &newLens);
			if(new){
			(boxes[boxNumber].lenses)[boxes[boxNumber].amountInBox] = newLens;
			boxes[boxNumber].amountInBox += 1;
			}
		}
		else{
			currLabel[counter] = line[i];
		}
		counter++;	
	}

	int focusingPower = 0;
	for(int i = 0; i < 256; i++){
		if(boxes[i].amountInBox > 0) focusingPower += calcPower(&boxes[i], i);
	}

	printf("%d\n", focusingPower);
	free(line);
	fclose(file);
	return 0;
}
