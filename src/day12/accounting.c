#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "day12/accounting.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day12/json.txt");

  int i = 0;
  printf("%d\n", getNumbersSum(input, &i, 0));
  printf("%d\n", getNumbersSum(input, &i, 1));

  return 0;
}


int getNumbersSum(char* elems, int* i, int fix){
  int c = 0;
  int invalid = 0;
  for (; *i < strlen(elems); (*i)++){
    if (elems[*i] == '{'){
      (*i)++;
      c += getNumbersSum(elems, i, fix);
      if (invalid){
        c = 0;
      }
    } else if (!invalid && (elems[*i] == '-' || isdigit(elems[*i]))){
      char newNum[5] = {elems[*i]};
      int j = 0;
      while (isdigit(elems[(*i)+1])){
        (*i)++;
        j++;
        newNum[j] = elems[*i];
      }
      newNum[j+1] = '\0';
      c += atoi(newNum);
    } else if (fix && elems[*i] == ':' && elems[(*i)+1] == '"' && elems[(*i)+2] == 'r'){
      invalid = 1;
      c = 0;
    } else if (elems[*i] == '}'){
      return c;
    }
  }
  *i = 0;
  return c;
}
