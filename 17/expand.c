#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/param.h>

typedef struct{
    int x;
    int y;
}Point;

typedef struct{
    Point p;
    char dir;
    int steps;
}Node;

typedef struct{
    int cost;
    Node n;
}State;

Node* valid_next(char** heatmap, int amount, int length, int i, int j, int* possible){
    Node* n = malloc(sizeof(Node) * 4);
    if(i > 0){
        n[*possible].p.x = j;
        n[*possible].p.y = i - 1;
        n[*possible].dir = 'n';
        (*possible)++;
    }
    if(i < amount - 1){
        n[*possible].p.x = j;
        n[*possible].p.y = i + 1;
        n[*possible].dir = 's';
        (*possible)++;
    }
    if(j > 0){
        n[*possible].p.x = j - 1;
        n[*possible].p.y = i;
        n[*possible].dir = 'w';
        (*possible)++;
    }
    if(j < length - 1){
        n[*possible].p.x = j + 1;
        n[*possible].p.y = i;
        n[*possible].dir = 'e';
        (*possible)++;
    }
    return n;
}

char opposite(char d){
    if(d == 'n'){
        return 's';
    }
    else if(d == 'w'){
        return 'e';
    }
    else if(d == 's'){
        return 'n';
    }
    return 'w';
}

Node* getNeighbours(Node* node, char** heatmap, int amount, int length, int* numberOfNeighbours){
    Node* neighbours = malloc(sizeof(Node) * 3);
    int possible = 0;
    Node* valid = valid_next(heatmap, amount, length, (node->p).y,(node->p).x, &possible);
    for(int i = 0; i < possible; i++){
        if(valid[i].dir == opposite(node->dir)){
            continue;
        }
        else if(valid[i].dir != node->dir){
            neighbours[*numberOfNeighbours].p = valid[i].p;
            neighbours[*numberOfNeighbours].dir = valid[i].dir;
            neighbours[*numberOfNeighbours].steps = 1;
            (*numberOfNeighbours)++;
        }
        else if(node->steps < 3){
            neighbours[*numberOfNeighbours].p = valid[i].p;
            neighbours[*numberOfNeighbours].dir = valid[i].dir;
            neighbours[*numberOfNeighbours].steps = node->steps + 1;
            (*numberOfNeighbours)++;
        }
    }
    return neighbours;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 16;
    int amount = 0;
    char** heatmap = malloc(sizeof(char*) * capacity);
    while(getline(&line, &len, file) != -1){
        if(amount == capacity){
            capacity *= 2;
            heatmap = realloc(heatmap, capacity);
        }
        printf("%s", line);
        heatmap[amount] = line;
        amount++;
        line = NULL;
        len = 0;
    }
    int queueCapacity = 2;
    int queueSize = 0;
    Node* queue = malloc(sizeof(Node) * queueCapacity);
    fclose(file);
    return 0;
}
