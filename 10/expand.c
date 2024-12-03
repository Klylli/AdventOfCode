#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/param.h>


long calcDistance(int i, int j, int k, int l, int* rows, int* cols, int emptyRows, int emptyCols){
    //printf("got into calcDistance for %d %d %d %d %d %d\n", i, j, k, l, emptyRows, emptyCols);
    long extraRows = 0;
    for(int x = 0; x < emptyRows; x++){
        //printf("%d ", x);
        if(rows[x] < k && rows[x] > i) extraRows+= 999999;
    }
    printf("\ngot to count how many double rows there are between %d %d: %ld\n", i, k, extraRows);
    long extraCols = 0;
    for(int x = 0; x < emptyCols; x++){
        //printf("%d ", x);
        if(cols[x] < MAX(j,l) && cols[x] > MIN(j,l)) extraCols+=999999;
    }
    printf("\ngot to count how many double rows there are between %d %d: %ld\n",j,l, extraCols);
    long distance = k + extraRows - i + labs(MAX(l,j) + extraCols - MIN(l,j));
    printf("Distance: %ld\n", distance);
    return distance;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 13;
    int amount = 0;
    long sum = 0;
    char** galaxy = malloc(sizeof(char*) * capacity);
    int rowSize = 8;
    int emptyRows = 0;
    int* rows = malloc(sizeof(int) * rowSize);
    int colSize = 8;
    int emptyCols = 0;
    int* cols = malloc(sizeof(int) * colSize);
    while(getline(&line, &len, file) != -1){
        if(amount == capacity){
            capacity*=2;
            galaxy = realloc(galaxy, sizeof(char*) * capacity);
        }
        bool gal = false;
        for(int i = 0; i < strlen(line); i++){
            if(line[i] == '#'){
                gal = true;
                break;
            }
        } 
        if(!gal){
            if(emptyRows == rowSize){
                rowSize*=2;
                rows = realloc(rows, sizeof(int) * rowSize);
            }
            rows[emptyRows] = amount;
            emptyRows++;
        }
        galaxy[amount] = line;
        amount++;
        line = NULL;
        len = 0;
    }
    for(int i = 0; i < amount; i++){
        for(int j = 0; j < strlen(galaxy[i]); j++){
                printf("%c", galaxy[i][j]);
            }
        printf("\n");
    }

    for(int j = 0; j < strlen(galaxy[0]) - 1; j++){
        bool b = false;
        for(int i = 0; i < amount; i++){
            if(galaxy[i][j] == '#'){
                b = true;
                break;
            }
        }
        if(!b){
             if(emptyCols == colSize){
                colSize*=2;
                cols = realloc(cols, sizeof(int) * colSize);
            }
            cols[emptyCols] = j;
            emptyCols++;
        }
    }
    printf("Double rows: %d Double cols: %d\n", emptyRows, emptyCols);
    
    for(int i = 0; i < amount; i++){
        for(int j = 0; j < strlen(galaxy[0]) - 1; j++){
            if(galaxy[i][j] == '#'){
                for(int k = i; k < amount; k++){
                    if(k == i){
                        for(int l = j + 1; l < strlen(galaxy[0]) - 1; l++){
                            if(galaxy[k][l] == '#'){
                                sum += calcDistance(i,j, k,l, rows, cols, emptyRows, emptyCols);
                                printf("sum same row: %ld\n", sum);
                            }
                        }
                    }
                    else{
                        for(int l = 0; l < strlen(galaxy[0]) - 1; l++){
                            if(galaxy[k][l] == '#'){
                                sum += calcDistance(i,j, k,l, rows, cols, emptyRows, emptyCols);
                                printf("sum after: %ld\n", sum);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%ld\n", sum);
    fclose(file);
    return 0;
}
