#include <regex.h>
#include <stdio.h>


int isMatching(const char* regexString, char* input){
  regex_t regex;
  int match = 0;

  regcomp(&regex, regexString, REG_ICASE | REG_EXTENDED | REG_NOSUB);
  match = !regexec(&regex, input, 0, NULL, 0);
  
  regfree(&regex);
  return match;
}