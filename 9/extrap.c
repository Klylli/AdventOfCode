#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>


long f(int* nums, int amount){
    printf("\n");
    int new = amount - 1;
    int* arr = malloc(sizeof(int) * new);
    bool notZero = false;
    for(int i = 0; i < new; i++){
        arr[i] = nums[i + 1] - nums[i];
        printf("%d ", arr[i]);
        if(arr[i] != 0) notZero = true; 
    }
    if(!notZero){
        long l = nums[0];
        free(arr);
        free(nums);
        printf("\nPart of sum: %ld", l);
        return l;
    }
    else{
        long l = (long) nums[0];
        printf("\nPart of sum: %ld", l);
        free(nums);
        return l - f(arr, new);
    }
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    long sum = 0;
    while(getline(&line, &len, file)!=-1){
            int amount = 1;
            for(int i = 0; i < strlen(line) - 1; i++){
                if(line[i] == ' ') amount++;
            }
        int* nums = malloc(sizeof(int) * amount);
        char* endptr = line;
        printf("New line: ");
        for(int i = 0; i < amount; i++){
            nums[i] = strtol(endptr, &endptr, 10);
            printf("%d ", nums[i]);
            endptr++;
        }
        sum += f(nums, amount);
        printf("\n");
        //free(nums);
        free(line);
        line = NULL;
        len = 0;
    }
    free(line);
    printf("%ld\n", sum);
    fclose(file);
    return 0;
}
