#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "day5/nice.h"
#include "utils/utils.h"

int main(void){
  char* input = getFileContent((char*)"src/day5/strings.txt");
  int strings = 0;
  char** stringsArray = getSplitArray(input, "\n", &strings);

  int modelOne = 0, modelTwo = 0;
  checkStringList(stringsArray, strings, &modelOne, &modelTwo);
  printf("%d\n", modelOne);
  printf("%d\n", modelTwo);
  return 0;
}


static int vowelCheck(char c){
  char vowels[] = {'a', 'e', 'i', 'o', 'u'};
  for (int i = 0; i < 5; i++){
    if (c == vowels[i]){
      return TRUE;
    }
  }
  return FALSE;
}

static int forbiddenStringCheck(char* s){
  char *forbidden[] = {"ab", "cd", "pq", "xy"};
  for (int i = 0; i < 4; i++){
    if (!strcmp(s, forbidden[i])){
      return FALSE;
    }
  }
  return TRUE;
}


int checkString(char* s){
  int vowels = 0;
  int doubleLetter = FALSE;
  char prevChar = '0';
  char subStr[2] = {'0'};
  for (int i = 0; i < strlen(s); i++){
    if (vowels < 3 && vowelCheck(s[i])){
      vowels++;
    }
    if (prevChar == s[i]){
      doubleLetter = TRUE;
    }
    prevChar = s[i];
    subStr[0] = subStr[1];
    subStr[1] = s[i];
    if (!forbiddenStringCheck(subStr)){
      return FALSE;
    }
  }
  return (vowels == 3 && doubleLetter == TRUE);
}



int checkStringCorrectly(char* s){
  regex_t regex;
  int pair = 0;
  int betweens = 0;

  regcomp(&regex, "^.*((\\w)(\\w)).*\\1.*$", REG_ICASE | REG_EXTENDED | REG_NOSUB);
  pair = !regexec(&regex, s, 0, NULL, 0);
  regfree(&regex);
  if (!pair){
    return FALSE;
  }

  regcomp(&regex, "^.*(\\w).\\1.*$", REG_ICASE | REG_EXTENDED | REG_NOSUB);
  betweens = !regexec(&regex, s, 0, NULL, 0);
  regfree(&regex);

  return pair && betweens;
}



void checkStringList(char** list, int size, int* modelOne, int *modelTwo){
  for (int i = 0; i < size; i++){
    if (checkString(list[i])){
      (*modelOne)++;
    }
    if (checkStringCorrectly(list[i])){
      (*modelTwo)++;
    }
  }
}
