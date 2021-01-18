#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day10/digits.h"


int main(void){
    char* input = (char*) malloc(10);
    strcpy(input, "1113122113");
    printf("%d\n", playLookAndSay(input, 40));
    
    input = (char*) malloc(10);
    strcpy(input, "1113122113");
    printf("%d\n", playLookAndSay(input, 50));

    return 0;
}


static char* doTurn(char* string){
    char* newString = (char*)malloc(2);
    char curr = string[0];
    int size = 2;
    int c = 0;
    for (int i= 0; i < strlen(string); i++){
        if (string[i] != curr){
            size += 2;
            newString = realloc(newString, size);
            curr = string[i];
            c = 0;
        }
        newString[size-2] = ++c+'0';
        newString[size-1] = curr;
    }
    free(string);
    newString = realloc(newString, size+1);
    newString[size] = '\0';

    return newString;
}


int playLookAndSay(char* startString, int times){
    char* playString = doTurn(startString);
    for (int i = 0; i < times-1; i++){
        playString = doTurn(playString);
    }
    return strlen(playString);
}