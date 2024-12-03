#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

int main(){
    int arr[2][4] = {{44,82,69,81}, {202,1076,1138,1458}};
    long arr2[2][1] = {{44826981},{202107611381458}};
        long ways = 1;
    for(long i = 0; i < 1; i++){
        long curr = 0;
        long raceLength = arr2[0][i];
        long raceRecord = arr2[1][i];
        for(long j = 1; j < raceLength; j++){
            long dist = (raceLength - j) * j;
            if(dist > raceRecord) curr++;
        }
        ways *= curr;
    }
    printf("%ld\n", ways);
    return 0;
}
