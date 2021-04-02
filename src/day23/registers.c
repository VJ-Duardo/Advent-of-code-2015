#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day23/registers.h"
#include "utils/utils.h"


int main(void){
    char* input = getFileContent((char*)"src/day23/instructions.txt");

    int size = 0;
    char*** instructions = createInstructions(input, &size);
    free(input);

    int a = 0, b = 0;
    doInstructions(instructions, size, &a, &b);
    printf("%d\n", b);

    a = 1, b = 0;
    doInstructions(instructions, size, &a, &b);
    printf("%d\n", b);
}



char*** createInstructions(char* input, int* size){
    char** lines = getSplitArray(input, "\n", size);
    char*** instructions = (char***) malloc(*size * sizeof(char**));

    for (int i=0; i < *size; i++){
        int paramSize = 0;
        instructions[i] = getSplitArray(lines[i], ", ", &paramSize);
        free(lines[i]);
    }
    free(lines);
    return instructions;
}


void doInstructions(char*** instructions, int size, int* a, int* b){
    int* regs[2] = {b, a};
    for (int i=0; i < size; i++){
        char* instr = instructions[i][0];
        if (!strcmp(instr, "hlf")){
            *regs[instructions[i][1][0] % 2] /= 2;
        } else if(!strcmp(instr, "tpl")){
            *regs[instructions[i][1][0] % 2] *= 3;
        } else if(!strcmp(instr, "inc")){
            (*regs[instructions[i][1][0] % 2])++;
        } else if(!strcmp(instr, "jmp")){
            i += atoi(instructions[i][1])-1;
        } else if(!strcmp(instr, "jie")){
            if (!(*regs[instructions[i][1][0] % 2] % 2)){
                i += atoi(instructions[i][2])-1;
            }
        } else if(!strcmp(instr, "jio")){
            if ((*regs[instructions[i][1][0] % 2] == 1)){
                i += atoi(instructions[i][2])-1;
            }
        }
    }
}