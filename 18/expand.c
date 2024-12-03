#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>
typedef struct{
    long x;
    long y;
}Point;

typedef struct{
    long x1;
    long y1;
    long x2;
    long y2;
    char* color;
}Edge;

void generateEdge(Edge* edges, int amount, char c, long length, char* colour){
    if(c == 'R'){
        edges[amount].x2 = edges[amount].x1 + length;
        edges[amount].y2 = edges[amount].y1;
        edges[amount + 1].x1 = edges[amount].x2;
        edges[amount + 1].y1 = edges[amount].y2;
    }
    else if(c == 'L'){
        edges[amount].x2 = edges[amount].x1 - length;
        edges[amount].y2 = edges[amount].y1;
        edges[amount + 1].x1 = edges[amount].x2;
        edges[amount + 1].y1 = edges[amount].y2;
    }
    else if(c == 'U'){
        edges[amount].x2 = edges[amount].x1;
        edges[amount].y2 = edges[amount].y1 - length;
        edges[amount + 1].x1 = edges[amount].x2;
        edges[amount + 1].y1 = edges[amount].y2;
    }
    else if(c == 'D'){
        edges[amount].x2 = edges[amount].x1;
        edges[amount].y2 = edges[amount].y1 + length;
        edges[amount + 1].x1 = edges[amount].x2;
        edges[amount + 1].y1 = edges[amount].y2;
    }
    edges[amount].color = colour;

    //printf("New edge: x1: %d y1: %d x2: %d y2: %d color: %s\n", edges[amount].x1, edges[amount].y1, edges[amount].x2, edges[amount].y2, edges[amount].color);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 16;
    int amount  = 0;
    Edge* edges = malloc(sizeof(Edge) * capacity);
    char** input = malloc(sizeof(char*) * capacity);
    long perimeter = 0;
    edges[0].x1 = 0;
    edges[0].y1 = 0;
    long up = 0;
    long down = 0;
    long left = 0;
    long right = 0;
    long width = 1;
    long height = 1;
    while(getline(&line, &len, file) != -1){
        if(amount == capacity - 1){
            capacity *= 2;
            edges = realloc(edges, sizeof(Edge) * capacity);
            input = realloc(input, sizeof(char*) * capacity);
        }
        input[amount] = line;
        char c = line[0];
        char* endptr;
        long length = strtol(line + 2, &endptr, 10);
        char* color = endptr + 3;
        
        char newDir = color[strlen(color) - 3];
        printf("%c\n", newDir);
        if(newDir == '0') c = 'R';
        else if(newDir == '1') c = 'D';
        else if(newDir == '2') c = 'L';
        else if(newDir == '3') c = 'U';
        color[strlen(color) - 3] = '\0';
        length = strtol(color, &endptr, 16);

        printf("length: %ld, direction: %c, color: %s\n",length, c, color);
        //printf("Direction: %c, Length: %ld, Color: %s", c, length, color);
        
        if(c == 'R'){
            width += length;
            right = MAX(right, width);
        }
        else if(c == 'L'){
            width -= length;
            left = MIN(left, width);
        }
        else if(c == 'U'){
            height -= length;
            up = MIN(up, height);
        }
        else if(c == 'D'){
            height += length;
            down = MAX(down, height);
        }
        perimeter += length;
        generateEdge(edges, amount, c, length, color);
        amount++;
        line = NULL;
        len = 0;
    }
    
    for(int i = 0; i < amount; i++){
        printf("Edge %d: %ld %ld %ld %ld %s\n", i + 1, edges[i].x1, edges[i].y1, edges[i].x2, edges[i].y2, edges[i].color);
    }
    
    long a = 0;
    for(long i = 0; i < amount; i++){
        a += edges[i].y1 * (edges[(i - 1) % (amount)].x1 - edges[i].x2);
    }
    a /= 2;
    long solution = a + perimeter/2 + 1;
    printf("%ld\n", a);
    printf("%ld\n", solution);
    /*
    long area = perimeter;
    for(long i = up; i < down + 1; i++){
        for(long j = left; j < right + 1; j++){
            bool visited = false;
            for(long k = 0; k < amount; k++){
                if(i >= MIN(edges[k].y1,edges[k].y2) && i <= MAX(edges[k].y1, edges[k].y2) && j >= MIN(edges[k].x1, edges[k].x2) && j <= MAX(edges[k].x1, edges[k].x2)){
                    visited = true;
                    break;
                }
            }
            if(visited) continue;
            long counter = 0;
            //printf("Point: %d %d \n\n", i, j);
            for(long k = 0; k < amount; k++){
                if(((i < edges[k].y1) != (i < edges[k].y2)) && (j < MAX(edges[k].x1, edges[k].x2))){
                    counter++;
                    //printf("%d %d %d\n", edges[k].y1, edges[k].y2, edges[k].x1);
                }
            }
            if(counter % 2 == 1){
                area++;
                printf("Point inside: i: %ld, j: %ld\n", i, j);
            }
        }
    }
    printf("perimeter: %ld, area: %ld\n",perimeter, area);
    */
    fclose(file);
    return 0;
}
