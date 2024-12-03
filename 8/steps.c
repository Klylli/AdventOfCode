#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    char loc[4];
    char left[4];
    char right[4];
}map;

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    getline(&line, &len, file);
    char* instructions = malloc(strlen(line) + 1);
    strcpy(instructions, line);
    printf("%s", instructions);
    line = NULL;
    len = 0;
    int capacity = 8;
    int amount = 0;
    int startIdx = 0;
    map* maps = malloc(sizeof(map) * capacity);
    while(getline(&line, &len, file)!=-1){
        if(strlen(line) == 1) continue;
        if(amount == capacity){
            capacity*= 2;
            maps = realloc(maps, sizeof(map) * capacity);
        }
        for(int i = 0; i < 3; i++){
            maps[amount].loc[i] = line[i];
            maps[amount].left[i] = line[i + 7];
            maps[amount].right[i] = line[i + 12];
        }
        maps[amount].loc[3] = '\0';
        maps[amount].left[3] = '\0';
        maps[amount].right[3] = '\0';
        if(strcmp("AAA", maps[amount].loc) == 0){
            startIdx = amount;
        }
        printf("loc: %s left: %s right: %s\n", maps[amount].loc, maps[amount].left, maps[amount].right);
        amount++;
        line = NULL;
        len = 0;
    }
    int counter = 0;
    char curr[4] = "AAA";
    int currIdx = startIdx;
    while(strcmp(curr, "ZZZ") != 0){

        if(instructions[counter % (strlen(instructions) - 1)] == 'L'){
            strcpy(curr,maps[currIdx].left);
        }
        else{
            strcpy(curr, maps[currIdx].right);
        }
        for(int i = 0; i < amount; i++){
            if(strcmp(curr, maps[i].loc) == 0){
                currIdx = i;
                break;
            }
        }
        counter++;
    }

    printf("%d\n", counter);
    fclose(file);
    return 0;
}
