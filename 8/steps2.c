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

bool isFull(long* arr, int size){
    bool full = true;
    for(int i = 0; i < size; i++){
        if(arr[i] == 0) full = false;
    }
    printf("Got done in full function\n");
    return full;
}
void calcLcm(long* endpoints, int size){
    printf("Got into calcLcm\n");
    long sum = endpoints[0];
    for(int i = 1; i < size; i++){
        long max = (sum > endpoints[i] ? sum : endpoints[i]);
        while(true){
            if(max % sum == 0 && max % endpoints[i] == 0){
                sum = max;
                printf("%ld", sum);
                break;
            }
            max++;
        }
    }
    printf("\n%ld\n", sum);
    exit(EXIT_SUCCESS);
}

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

    int startIdxSize = 8;
    int idxAmount = 0;
    int* startIdxs = malloc(sizeof(int) * startIdxSize);
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
        if(maps[amount].loc[2] == 'A'){
            if(idxAmount == startIdxSize){
                startIdxSize*=2;
                startIdxs = realloc(startIdxs, sizeof(int) * startIdxSize);
            }
            startIdxs[idxAmount] = amount;
            idxAmount++;
        }
        printf("loc: %s left: %s right: %s\n", maps[amount].loc, maps[amount].left, maps[amount].right);
        amount++;
        line = NULL;
        len = 0;
    }
    printf("idxAmount: %d\n", idxAmount);
    int counter = 0;
    long* endpoints = malloc(idxAmount * sizeof(long));
    for(int i = 0; i < idxAmount; i++){
        endpoints[i] = 0;
    }
    char* curr = malloc(4);
    while(true){
//        printf("Back up here in the %d iteration", counter);
        for(int i = 0; i < idxAmount; i++){

            if(endpoints[i] > 0){
                continue;
            }

            if(instructions[counter % (strlen(instructions) - 1)] == 'L'){
                strcpy(curr,maps[startIdxs[i]].left);
            }
            else{
                strcpy(curr, maps[startIdxs[i]].right);
            }
            printf("%s\n", curr);
            if(curr[2] == 'Z'){
                endpoints[i] = counter + 1;
                printf("cycle duration for starting idx %d: %ld\n", i, endpoints[i]);
                if(isFull(endpoints, idxAmount)){
                    calcLcm(endpoints, idxAmount);
                }
            }
            for(int j = 0; j < amount; j++){
                if(strcmp(curr, maps[j].loc) == 0){
                    startIdxs[i] = j;
                    break;
                }
            }
        }
        counter++;
  //      printf("I got out of the for loop!\n");
        //printf("%d ", counter);
        bool done = true;
        for(int i = 0; i < idxAmount; i++){
            printf("%ld ", endpoints[i]);
            if(endpoints[i] == 0){
                done = false;
            }
        }
        if(done){
            printf("got out of the while loop!");
            break;
        }
    }

    for(int i = 0; i < idxAmount; i++){
        printf("%ld ", endpoints[i]);
    }
    long sum = endpoints[0];
    for(int i = 1; i < idxAmount; i++){
        long max = (sum > endpoints[i] ? sum : endpoints[i]);
        while(true){
            if(max % sum == 0 && max % endpoints[i] == 0){
                sum = max;
                break;
            }
        }
    }
    printf("\n%ld\n", sum);
    fclose(file);
    return 0;
}
