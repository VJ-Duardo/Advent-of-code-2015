#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day11/password.h"
#include "utils/match.h"


int main(void){
  char input[9] = "hepxcrrq";
  setNewPassword(input);
  printf("%s\n", input);

  setNewPassword(input);
  printf("%s\n", input);

  return 0;
}


static int checkPassword(char* input){
  int incrReq = 0;
  for (int i=0; i < PASS_LEN; i++){
    if (!incrReq && i < PASS_LEN-2 && input[i] == input[i+1]-1 && input[i+1] == input[i+2]-1){
      incrReq = 1;
    }
    if (input[i] == 'i' || input[i] == 'o' || input[i] == 'l'){
      return 0;
    }
  }
  return incrReq && isMatching("\\w*(\\w)\\1\\w*(\\w)\\2\\w*", input);
}



void setNewPassword(char* input){
  int result = 0;
  do {
    input[PASS_LEN-1]++;
    for (int i = PASS_LEN-1; i >= 0; i--){
      if (input[i] > 'z'){
        input[i] = 'a';
        if (i > 0){
          input[i-1]++;
        }
      }
    }
    result = checkPassword(input);
  } while (!result);
}


