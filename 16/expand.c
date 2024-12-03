#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>


typedef struct{
    int x;
    int y;
}square;

typedef struct{
    int x;
    int y;
    char dir;
}memory;

void lightray(char** cave, int amount, int length, square* visited, int* numberVisited, int i, int j, char direction, memory* mem, int* counter){
    if(i < 0 || i >= amount || j < 0 || j >= length) return;
    printf("new Field: %c %d %d\n", cave[i][j], i, j);
    bool newSquare = true;
    for(int k = 0; k < *numberVisited; k++){
        if(visited[k].x == j && visited[k].y == i) newSquare = false;
    }
    if(newSquare){
        visited[*numberVisited].y = i;
        visited[*numberVisited].x = j;
        (*numberVisited)++;
    }
    for(int k = 0; k < *counter; k++){
        if(mem[k].x == j && mem[k].y == i && mem[k].dir == direction) return;
    }
    mem[*counter].x = j;
    mem[*counter].y = i;
    mem[*counter].dir = direction;
    (*counter)++;
    char c = cave[i][j];
    if(direction == 'n'){
        printf("Direction: %c\n\n", direction);
        if(c == '.'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n', mem, counter);
        }
        else if(c == '|'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n',  mem, counter);
        }
        else if(c == '/'){
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
        }
        else if(c == '\\'){
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
        }
        else if(c == '-'){
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
        }

    }
    else if(direction == 'w'){
        printf("Direction: %c\n\n", direction);
        if(c == '.'){
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
        }
        else if(c == '|'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n',  mem, counter);
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '/'){
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '\\'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n',  mem, counter);
        }
        else if(c == '-'){
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
        }
    }
    else if(direction == 's'){
        printf("Direction: %c\n\n", direction);
        if(c == '.'){
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '|'){
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '/'){
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
        }
        else if(c == '\\'){
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
        }
        else if(c == '-'){
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
            lightray(cave, amount, length, visited, numberVisited, i, j - 1, 'w',  mem, counter);
        }
    }
    else if(direction == 'e'){
        printf("Direction: %c\n\n", direction);
        if(c == '.'){
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
        }
        else if(c == '|'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n',  mem, counter);
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '/'){
            lightray(cave, amount, length, visited, numberVisited, i - 1, j, 'n',  mem, counter);
        }
        else if(c == '\\'){
            lightray(cave, amount, length, visited, numberVisited, i + 1, j, 's',  mem, counter);
        }
        else if(c == '-'){
            lightray(cave, amount, length, visited, numberVisited, i, j + 1, 'e',  mem, counter);
        }
    }
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 8;
    int amount = 0;
    char** cave = malloc(sizeof(char*) * capacity);
    while(getline(&line, &len, file)!=-1){
        if(amount == capacity){
            capacity *= 2;
            cave = realloc(cave, sizeof(char*) * capacity);
        }
        printf("%s", line);
        cave[amount] = line;
        amount++;
        line = NULL;
        len = 0;
    }
    int length = strlen(cave[0]) - 1;
    printf("\n");
    square* visited = malloc(sizeof(square) * amount * length);
    memory* mem = malloc(sizeof(memory) * amount * length * 4);
    int maximum = 0;
    int counter = 0;
    int numberVisited = 0;
    for(int i = 0; i < amount; i++){
        counter = 0;
        numberVisited = 0;
        lightray(cave, amount, length, visited, &numberVisited, i, 0, 'e', mem, &counter);
        maximum = MAX(numberVisited, maximum);
        counter = 0;
        numberVisited = 0;
        lightray(cave, amount, length, visited, &numberVisited, i, length - 1, 'w', mem, &counter);
        maximum = MAX(numberVisited, maximum);
    }
    for(int i = 0; i < length; i++){
         counter = 0;
         numberVisited = 0;
         lightray(cave, amount, length, visited, &numberVisited, 0, i, 's', mem, &counter);
         maximum = MAX(numberVisited, maximum);
         counter = 0;
         numberVisited = 0;
         lightray(cave, amount, length, visited, &numberVisited, amount - 1, i, 'n', mem, &counter);
         maximum = MAX(numberVisited, maximum);
    }
    printf("%d\n", maximum);
    return 0;
}
