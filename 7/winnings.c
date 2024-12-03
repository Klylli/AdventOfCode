#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    int bid;
    char* hand;
    char type;
}card;

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)b - *(int*)a );
}

char getType(char* s, int length){
    int card[5];
    card[0] = 1;
    for(int i = 1; i < length; i++){
        card[i] = 0;
    }

    for(int i = 1; i < length; i++){
        char c = s[i];
        bool b = false;
        for(int j = 0; j < i; j++){
            if(s[j] == c){
                card[j]++;
                b = true;
                break;
            }
        }
        if(!b) card[i]++;
    }
    //for(int i = 0; i < length; i++) printf("%d ", card[i]);
    //printf("\n");
    qsort(card, length, sizeof(int), cmpfunc);
    //for(int i = 0; i < length; i++) printf("%d ", card[i]);
    //printf("\n");
    if(card[0] == 5) return '5';
    if(card[0] == 4) return '4';
    if(card[0] == 3){
        if(card[1] == 2) return 'f';
        return '3';
    }
    if(card[0] == 2){
        if(card[1] == 2) return '2';
        return '1';
    }
    if(card[0] == 1) return 'h';
    printf("This should not be reached!\n");
    return '0';
}

int convert(char* s){
    int res = 0;
    //int capacity = 6;
    //char* builder = malloc(capacity);
    //int len = 0;
    for(int i = 0; i < 5; i++){
        /*if(len == capacity){
            capacity *= 2;
            builder = realloc(builder, capacity);
        }
        */
        if(s[i] >= '2' && s[i] <= '9'){
           // builder[len] = s[i];
            res*=15;
            res += s[i]-'0';
            //len++;
        }
        else if(s[i] == 'T'){
            res*= 15;
            res += 10;
            /*builder[len] = '1';
            len++;
            builder[len] = '0';
            len++;
            */
        }
        else if(s[i] == 'J'){
            res*=15;
            res += 11;
            /*builder[len] = '1';
            len++;
            builder[len] = '1';
            len++;
            */
        }
        else if(s[i] == 'Q'){
            res*= 15;
            res += 12;
            /*builder[len] = '1';
            len++;
            builder[len] = '2';
            len++;
            */
        }
        else if(s[i] == 'K'){
            res*= 15;
            res += 13;
            /*builder[len] = '1';
            len++;
            builder[len] = '3';
            len++;
            */
        }
        else if(s[i] == 'A'){
            res*= 15;
            res += 14;
            /*builder[len] = '1';
            len++;
            builder[len] = '4';
            len++;
            */
        }
    }
    /*
    builder[len] = '\0';
    char* endptr;
    int num = strtol(builder, &endptr, 10);
    */
    printf("%d\n", res);
    
    return res;
}

void convertBack(int num, char* str){
    int counter = 4;
    while(num > 0){
        if(counter < 0) printf("Panic!");
        int curr = num % 15;
        if(curr >= 2 && curr <= 9){
            str[counter] = (curr + '0') & 0xFF;
        }
        else if(curr == 10){
            str[counter] = 'T';
        }
        else if(curr == 11){
            str[counter] = 'J';
        }
        else if(curr == 12){
            str[counter] = 'Q';
        }
        else if(curr == 13){
            str[counter] = 'K';
        }
        else if(curr == 14){
            str[counter] = 'A';
        }
        num /= 15;
        counter--;
    }
    printf("%s\n", str);
}

void put(card cards[], int amount, int* arr, int number, char c){
    printf("%c\n", c);
    int counter = 0;
    for(int i = 0; i < amount; i++){
        if(cards[i].type == c){
            arr[counter] = convert(cards[i].hand);
            counter++;
        }
    }
    qsort(arr, number, sizeof(int), cmpfunc);
    for(int i = 0; i < counter; i++) printf("%d ", arr[i]);
    printf("\n");
}

int calc(card cards[], int* counter, int* help, int arr[], int number){
    int sum = 0;
    for(int i = 0; i < number; i++){
        char* str = malloc(6);
        str[5] = '\0'; 
        convertBack(arr[i], str);
        for(int j = 0; j < (*counter); j++){
            if(strcmp(str, cards[j].hand) == 0){
                sum += ((*help)) * cards[j].bid;
                printf("sum: %d bid: %d help: %d\n", sum, cards[j].bid, *help);
                break;
            }
        }
        (*help)--;
    }
    return sum;
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    int capacity = 8;
    int amount = 0;
    char** hands = malloc(sizeof(char*) * capacity);
    card cards[1000];
    int numberOfCards = 5;
    for(int i = 0; i < 1000; i++){
        cards[i].hand = malloc(numberOfCards + 1);
    }

    while(getline(&line, &len, file) != -1){
        if(amount == capacity){
            capacity *= 2;
            hands = realloc(hands, sizeof(char*) * capacity);
        }
        for(int i = 0; i < numberOfCards; i++){
            cards[amount].hand[i] = line[i];
        }
        cards[amount].hand[numberOfCards] = '\0';
        char* endptr;
        cards[amount].bid = strtol(line + 6, &endptr, 10);
        printf("hand: %s, bid: %d\n", cards[amount].hand, cards[amount].bid);
        cards[amount].type = getType(cards[amount].hand, numberOfCards);
        printf("%c\n",cards[amount].type);
        hands[amount] = line;
        amount++;
        line = NULL;
        len = 0;
    }
    int five = 0;
    int four = 0;
    int full = 0;
    int three = 0;
    int two = 0;
    int one = 0;
    int high = 0;
    for(int i = 0; i < amount; i++){
        char opt;
        opt = cards[i].type;
        switch(opt){
            case '5': 
                five++;
                break;
            case '4':
                four++;
                break;
            case 'f':
                full++;             
                break;
            case '3':
                three++;
                break;
            case '2':
                two++;
                break;
            case '1':
                one++;
                break;
            case 'h':
                high++;
                break;
            default:
                printf("Panic!: %c\n", opt);
        }
    }
    printf("%d %d %d %d %d %d %d\n", five, four, full, three, two , one, high);
    int* five_arr = malloc(sizeof(int) * five);
    int* four_arr = malloc(sizeof(int) * four);
    int* full_arr = malloc(sizeof(int) * full);
    int* three_arr = malloc(sizeof(int) * three);
    int* two_arr = malloc(sizeof(int) * two);
    int* one_arr = malloc(sizeof(int) * one);
    int* high_arr = malloc(sizeof(int) * high);
    put(cards, amount, five_arr, five, '5');
    put(cards, amount, four_arr, four, '4');
    put(cards, amount, full_arr, full, 'f');
    put(cards, amount, three_arr, three, '3');
    put(cards, amount, two_arr, two, '2');
    put(cards, amount, one_arr, one, '1');
    put(cards, amount, high_arr, high, 'h');
    printf("Put works\n");
    int sum = 0;
    int counter = amount;
    int help = amount;
    sum += calc(cards, &counter, &help, five_arr, five);
    sum += calc(cards, &counter, &help, four_arr, four);
    sum += calc(cards, &counter, &help, full_arr, full);
    sum += calc(cards, &counter, &help, three_arr, three);
    sum += calc(cards, &counter, &help, two_arr, two);
    sum += calc(cards, &counter, &help, one_arr, one);
    sum += calc(cards, &counter, &help, high_arr, high);
    printf("%d\n", sum);
    for(int i = 0; i < amount; i++) free(hands[i]);
    free(hands);
    free(line);
    fclose(file);
    return 0;
}
