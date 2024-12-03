#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>



typedef struct{
    int x;
    int y;
}justVisited;

typedef struct{
    int x1;
    int x2;
    int y1;
    int y2;
}edge;



char getChar(char** maze, int amount, int length, int i, int j){
    if(i < 0 || i >= amount || j < 0 || j >= length) return '0';
    return maze[i][j];
}

long calcFurthest(char** maze, int amount, int length, int i, int j, justVisited last, long result, int* visited, edge* polygon, int* edges){
    visited[i*length + j] = 1;
    //printf("char: %c result: %ld\n", maze[i][j],result);
    if(maze[i][j] != '-' && maze[i][j] != '|' && maze[i][j] != 'S'){
        polygon[*edges].x2 = j;
        polygon[*edges].y2 = i;
        (*edges)++;
        polygon[*edges].x1 = j;
        polygon[*edges].y1 = i;
    }
    if(result != 0 && maze[i][j] == 'S'){
        return result;
    }
    //printf("got past sanity check\n");
    char west, north, east, south;
    north = getChar(maze, amount, length, i - 1, j);
    west = getChar(maze, amount, length, i, j - 1);
    south = getChar(maze, amount, length, i + 1, j);
    east = getChar(maze, amount, length, i, j + 1);
    //printf("north: %c west: %c south: %c east: %c\n", north, west, south, east);
    justVisited current;
    current.y = i;
    current.x = j;
    char c = maze[i][j];
    if(north != '0' && (c == 'S' || c == '|' || c == 'L' || c == 'J')){
        //printf("North possible!\n");
        if(north == '|' && !(last.y == i - 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i - 1, j, current, result +1, visited, polygon, edges);
        }
        else if(north == '7' && !(last.y == i - 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i - 1, j, current, result + 1, visited ,polygon, edges);
        }
        else if(north == 'F' && !(last.y == i - 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i - 1, j, current, result + 1, visited ,polygon, edges);
        }
    }
    if(west != '0' && (c == 'S' || c == '-' || c == 'J' || c == '7')){
        //printf("West possible!\n");
        if(west == '-' && !(last.y == i && last.x == j - 1)){
            return calcFurthest(maze, amount, length, i, j - 1, current, result + 1, visited ,polygon, edges);          
        }
        else if(west == 'L'&& !(last.y == i && last.x == j - 1)){
            return calcFurthest(maze, amount, length, i, j - 1, current, result + 1, visited ,polygon, edges);
        }
        else if(west == 'F'&& !(last.y == i && last.x == j - 1)){
            return calcFurthest(maze, amount, length, i, j - 1, current, result + 1, visited ,polygon, edges);
        }
    }
    if(south != '0' && (c == 'S' || c == '|' || c == '7' || c == 'F')){
        //printf("South possible!\n");
        if(south ==  '|' && !(last.y == i + 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i + 1, j, current, result + 1, visited ,polygon, edges);
        }
        else if(south == 'J'&& !(last.y == i + 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i + 1, j, current, result + 1, visited ,polygon, edges);
        }
        else if(south == 'L'&& !(last.y == i + 1 && last.x == j)){
            return calcFurthest(maze, amount, length, i + 1, j, current, result + 1, visited ,polygon, edges);
        }
    }
    if(east != '0' && (c == 'S' || c == '-' || c == 'L' || c == 'F')){
        //printf("East possible!\n");
        if(east == '-' && !(last.y == i && last.x == j + 1)){
            return calcFurthest(maze, amount, length, i, j + 1, current, result + 1, visited ,polygon, edges);
        }
        else if(east == '7'&& !(last.y == i && last.x == j + 1)){
            return calcFurthest(maze, amount, length, i, j + 1, current, result + 1, visited ,polygon, edges);
        }
        else if(east == 'J'&& !(last.y == i  && last.x == j + 1)){
            return calcFurthest(maze, amount, length, i, j + 1, current, result + 1, visited ,polygon, edges);      
        }
    }
    return result + 1;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 8;
    int amount = 0;
    char** maze = malloc(capacity * sizeof(char*));
    while(getline(&line, &len, file) != -1){
        if(amount == capacity){
            capacity *= 2;
            maze = realloc(maze, sizeof(char*) * capacity);
        }
        printf("%s",line);
        maze[amount] = line;
        amount++;
        line = NULL;
        len = 0;
    }
    long result = 0;
    int length = strlen(maze[0]) - 1;
    int* visited = malloc(sizeof(int) * amount * length);
    if(visited == NULL) printf("ERROR MALLOC \n");
    for(int i = 0; i < amount * length; i++){
        visited[i] = 0;
    }
    printf("%d %d\n", amount, length);
    edge* polygon = malloc(sizeof(edge) * amount*length);
    int edges = 0;
    for(int i = 0; i < amount; i++){
        for(int j = 0; j < length; j++){
            if(maze[i][j] == 'S'){
                justVisited start;
                start.x = -1;
                start.y = -1;
                polygon[edges].x1 = j;
                polygon[edges].y1 = i;
                result = calcFurthest(maze, amount, length, i, j, start, 0, visited, polygon, &edges);
            }
        }
    }
    polygon[edges].x2 = polygon[0].x1;
    polygon[edges].y2 = polygon[0].y1;
    printf("Edges in polygon: %d\n", edges + 1);
    for(int i = 0; i <= edges; i++){
        printf("Edge %d: (%d,%d)-(%d,%d)\n", i, polygon[i].x1, polygon[i].y1, polygon[i].x2, polygon[i].y2);
    }
    printf("Number of steps: %ld\n", result);
    result/=2;
    printf("%ld\n", result);
    int numberInside = 0;
    for(int i = 0; i < amount; i++){
        for(int j = 0; j < length; j++){
            if(visited[i*length + j]) continue;
            int counter = 0;
            for(int k = 0; k <= edges; k++){
//                printf("%d %d\n", ((i < polygon[i].y1) != (i < polygon[i].y2)), j < MIN(polygon[i].x1, polygon[i].x2));
                if(((i < polygon[k].y1) != (i < polygon[k].y2)) && j < MIN(polygon[k].x1, polygon[k].x2)){
                    counter++;
                    //printf("%d, %d\n", i, j);
                }
            }
            if(counter % 2 == 1){
         printf("i: %d j: %d\n", i, j);
                numberInside++;
            }
        }
    }   

    printf("Number of tiles inside: %d\n", numberInside);
    fclose(file);
    return 0;
}
