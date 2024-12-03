#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/param.h>

typedef struct{
    int x;
    int m;
    int a;
    int s;
}Part;

typedef struct{
    char var;
    char compare;
    int number;
    char* consequence;
}Instruction;

typedef struct{
    char* name;
    Instruction* instructions;
    int instructionCapacity;
    int instructionAmount;
}Workflow;

bool isDigit(char character){
    char c = character - '0';
    if(c >= 0 && c < 10) return true;
    return false;
}

char runWorkflow(Workflow* w, Part* p, char* toRun, int workflowAmount){
    if(strcmp(toRun, "A") == 0){
        return 'A';
    }
    if(strcmp(toRun, "R") == 0){
        return 'R';
    }
    int idx = -1;
    for(int i = 0; i < workflowAmount; i++){
        //printf("%s %s\n", toRun, w[i].name);
        if(strcmp(toRun, w[i].name) == 0){
            idx = i;
        }
    }
    if(idx == -1) printf("ERROR\n");
    for(int i = 0; i < w[idx].instructionAmount; i++){
        char v = w[idx].instructions[i].var;
        char sb = w[idx].instructions[i].compare;
        if(sb == '='){
            return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
        }
        int num = w[idx].instructions[i].number;
        //bool jmp = false;
        if(v == 'x'){
            if(sb == '<'){
                if(p->x < num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
            else if(sb == '>'){
                if(p->x > num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
        }
        else if(v == 'm'){
            if(sb == '<'){
                if(p->m < num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
            else if(sb == '>'){
                if(p->m > num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
        }
        else if(v == 'a'){
            if(sb == '<'){
                if(p->a < num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
            else if(sb == '>'){
                if(p->a > num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
        }
        else if(v == 's'){
            if(sb == '<'){
                if(p->s < num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }
            else if(sb == '>'){
                if(p->s > num){
                    return runWorkflow(w, p, w[idx].instructions[i].consequence, workflowAmount);
                }
            }           
        }
    }
    return 'R';
}

void initWorkflow(Workflow* w){
    w->instructionCapacity = 16;
    w->instructionAmount = 0;
    w->instructions = malloc(sizeof(Instruction) * w->instructionCapacity);
}

int main(int argc, char** argv){
    FILE* file = fopen(argv[argc - 1], "r");
    char* line = NULL;
    size_t len = 0;
    bool p = false;

    int partCapacity = 8;
    int partAmount = 0;
    Part* parts = malloc(sizeof(Part) * partCapacity);

    int workflowCapacity = 16;
    int workflowAmount = 0;
    Workflow* workflows = malloc(sizeof(Workflow) * workflowCapacity);

    while(getline(&line, &len, file) != -1){
        if(strlen(line) == 1){
            p = true;
            continue;
        }
        if(p){
            if(partAmount == partCapacity){
                partCapacity *= 2;
                parts = realloc(parts, sizeof(Part) * partCapacity);
            }
            for(int i = 0; i < strlen(line); i++){
                char* endptr;
                if(line[i] == 'x'){
                    parts[partAmount].x = strtol(line + i + 2, &endptr, 10);
                }
                else if(line[i] == 'm'){
                    parts[partAmount].m = strtol(line + i + 2, &endptr, 10);
                }
                else if(line[i] == 'a'){
                    parts[partAmount].a = strtol(line + i + 2, &endptr, 10);
                }
                else if(line[i] == 's'){
                    parts[partAmount].s = strtol(line + i + 2, &endptr, 10);
                }
            }
            printf("New part: %d %d %d %d\n", parts[partAmount].s, parts[partAmount].a ,parts[partAmount].m, parts[partAmount].x);
            partAmount++;
        }
        else{
            if(workflowAmount == workflowCapacity){
                workflowCapacity *= 2;
                workflows = realloc(workflows, sizeof(Workflow) * workflowCapacity);
            }
            initWorkflow(&workflows[workflowAmount]);

            //get name
            int counter = 0;
            while(line[counter] != '{'){
                counter++;
            }
            workflows[workflowAmount].name = malloc(counter + 1);
            for(int i = 0; i < counter; i++){
                workflows[workflowAmount].name[i] = line[i];
            }
            workflows[workflowAmount].name[counter] = '\0';

            //get conditions
            bool newCondition = true;
            for(int i = counter + 1; i < strlen(line) - 1; i++){
                if(line[i] == ','){
                    newCondition = true;
                    continue;
                }
                if(!newCondition) continue;
                if(workflows[workflowAmount].instructionAmount == workflows[workflowAmount].instructionCapacity){
                    workflows[workflowAmount].instructionCapacity *= 2;
                    workflows[workflowAmount].instructions = realloc(workflows[workflowAmount].instructions, sizeof(Instruction) * workflows[workflowAmount].instructionCapacity);
                }
                int ins = workflows[workflowAmount].instructionAmount;
                if(line[i + 1] == '<' || line[i + 1] == '>'){
                    workflows[workflowAmount].instructions[ins].var = line[i];
                    workflows[workflowAmount].instructions[ins].compare = line[i + 1];
                    char* endptr;
                    workflows[workflowAmount].instructions[ins].number = strtol(line + i + 2, &endptr, 10);
                    //build consequence string
                    int cnt = 0;
                    while(endptr[cnt + 1] != ','){
                        cnt++;
                    }
                    workflows[workflowAmount].instructions[ins].consequence = malloc(cnt + 1);
                    for(int j = 1; j < cnt + 1; j++){
                        workflows[workflowAmount].instructions[ins].consequence[j - 1] = endptr[j]; 
                    }
                    workflows[workflowAmount].instructions[ins].consequence[cnt] = '\0';
                }
                else{
                    int consCounter = 0;
                    while(line[i + consCounter] != '}'){
                        consCounter++;
                    }
                    workflows[workflowAmount].instructions[ins].consequence = malloc(consCounter + 1);
                    for(int j = i; j < i + consCounter; j++){
                        workflows[workflowAmount].instructions[ins].consequence[j - i] = line[j];
                    }
                    workflows[workflowAmount].instructions[ins].consequence[consCounter] = '\0';
                    //printf("else: %s\n", workflows[workflowAmount].instructions[ins].consequence);
                    workflows[workflowAmount].instructions[ins].compare = '=';
                    workflows[workflowAmount].instructions[ins].var = '1';
                    workflows[workflowAmount].instructions[ins].number = 0;
                }
                newCondition = false;
                workflows[workflowAmount].instructionAmount += 1; 
            }
            printf("New workflow: %s\n", workflows[workflowAmount].name);
            printf("%d\n", workflows[workflowAmount].instructionAmount);
            for(int j = 0; j < workflows[workflowAmount].instructionAmount; j++){
                printf("%c %c %d %s\n", workflows[workflowAmount].instructions[j].var, workflows[workflowAmount].instructions[j].compare, workflows[workflowAmount].instructions[j].number, workflows[workflowAmount].instructions[j].consequence);
            }
            workflowAmount++;
        }
        line = NULL;
        len = 0;
    }
    int sum = 0;
    for(int i = 0; i < partAmount; i++){
        if(runWorkflow(workflows, &parts[i], "in", workflowAmount) == 'A'){
            sum += parts[i].s;
            sum += parts[i].a;
            sum += parts[i].m;
            sum += parts[i].x;
        }
    }
    printf("%d\n", sum);
    fclose(file);
    return 0;
}
