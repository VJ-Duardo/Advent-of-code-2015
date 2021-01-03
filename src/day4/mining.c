#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#include "day4/mining.h"


int main(void){
  char* input = "bgvyzdsv";

  int solution = getNumber(input);
  printf("%d\n", solution);

  return 0;
}


static int checkMD5(char* input){
  unsigned char md[MD5_DIGEST_LENGTH];
  MD5_CTX c;

  MD5_Init (&c);
  MD5_Update (&c, input, strlen(input));
  MD5_Final (md, &c);

  return !md[0] && !md[1] && !md[2];
  //return !md[0] && !md[1] && md[2] <= 9;
}


int getNumber(char* key){
  int num = -1;
  int result = 0;
  do {
    num++;
    char input[20];
    strcpy(input, key);
    char numStr[12];
    sprintf(numStr, "%d", num);
    result = checkMD5(strcat(input, numStr));
  } while (!result);
  return num;
}
