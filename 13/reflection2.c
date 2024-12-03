#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int findMirrors(char** maze, int linesInMaze){
	int sum = 0;
	int len = strlen(maze[0]);
	// horizontal reflection
	for(int i = 0; i < linesInMaze - 1; i++){
		//printf("linesInMaze: %d\n", linesInMaze);
		int counter = 0;
		int up = i;
		int down = i + 1;
		while(up >= 0 && down < linesInMaze){
			for(int j = 0; j < len; j++){
				if(maze[up][j] != maze[down][j]) counter++;
			}
			up--;	
			down++;
		}
		if(counter == 1){
			printf("Row: %d\n", i);
			sum += 100*(i+1);
			//return 100 * (i + 1);
		}

	}
	//printf("no horizontal reflection, checking for vertical!\n");
	// vertical reflection
	for(int i = 0; i < len - 2; i++){
			int counter = 0;
			int left = i;
			int right = i + 1;
			while(left >= 0 && right < len - 1){
				for(int j = 0; j < linesInMaze; j++){
					if(maze[j][left] != maze[j][right]) counter++;
				}
				left--;
				right++;
			}
			if(counter == 1){
				printf("Col: %d reflection found\n", i); 
				sum += i + 1;
				//return i + 1;
			}
		
	}
	printf("%d\n", sum);
	if(sum == 0) printf("this point should not be reached, no reflection found\n");
	return sum;
}

int main(int argc, char** argv){
	FILE* file = fopen(argv[argc - 1], "r");
	char* line = NULL;
	size_t len = 0;
	int size = 2;
	char** maze = malloc(sizeof(char*) * size);
	int linesInMaze = 0;
	int sum = 0;
	//read maze
	while(getline(&line, &len, file) != -1){
		if(strlen(line) == 1){ //\n
			sum += findMirrors(maze, linesInMaze);
			linesInMaze = 0;
			line = NULL;
			len = 0;
			printf("\n");
			continue;
		}
		if(linesInMaze == size){
			size*=2;
			maze = realloc(maze, sizeof(char*) * size);
		}
		printf(line);
		maze[linesInMaze] = line;
		linesInMaze++;
		line = NULL;
		len = 0;
	}
	free(line);
	free(maze);
	fclose(file);
	printf("%d\n", sum);
}
