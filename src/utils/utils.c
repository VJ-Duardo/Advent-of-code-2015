#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** getSplitArray(char* input, const char* del, int* size){
  char *s = strtok(input, del);
  char **result = (char**) malloc(sizeof(char*));
  int c = 0;
  while (s != NULL){
    (*size)++;
    result = realloc(result, *size*sizeof(char*));
    result[c] = (char*)malloc(strlen(s)*sizeof(char)+1);
    strcpy(result[c], s);
    c++;
    s = strtok(NULL, del);
  }
  return result;
}

char* getFileContent(char* path){
  FILE *file;
  int c, size = 1, i = 0;
  char* content = malloc(1);
  file = fopen(path, "r");
  if (file){
    while ((c = getc(file)) != EOF){
      size++;
      content = realloc(content, size * sizeof(char));
      content[i++] = c;
    }
    fclose(file);
    return content;
  }
  return (char*)"";
}
