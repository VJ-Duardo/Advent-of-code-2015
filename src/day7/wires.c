#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#include "day7/wires.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day7/circuit.txt");

  int wires = 0;
  char** linesArray = getSplitArray(input, "\n", &wires);

  Wire* wireArray = createWires(linesArray, wires);
  int a = getSignal(wireArray, "a", wires);
  printf("%d\n", a);
  
  wireArray = createWires(linesArray, wires);
  for (int i = 0; i <wires; i++){
    if (!strcmp(wireArray[i].name, "b"))
      wireArray[i].value = a;
  }
  a = getSignal(wireArray, "a", wires);
  printf("%d\n", a);

  return 0;
}


int getSignal(Wire* wireArray, char* wire, int wires){
  Wire* w;
  for (int i= 0; i<wires; i++){
    if (!strcmp(wireArray[i].name, wire)){
      w = &wireArray[i];
    }
  }
  if (!w->done){
    if (!strcmp(w->op, "AND")){
      int left = (isdigit(w->srcs[0][0])) ? atoi(w->srcs[0]) : getSignal(wireArray, w->srcs[0], wires);
      int right = (isdigit(w->srcs[1][0])) ? atoi(w->srcs[1]) : getSignal(wireArray, w->srcs[1], wires);
      w->value = left & right;
    } else if (!strcmp(w->op, "OR")){
      w->value = getSignal(wireArray, w->srcs[0], wires) | getSignal(wireArray, w->srcs[1], wires);
    } else if (!strcmp(w->op, "LSHIFT")){
      w->value = getSignal(wireArray, w->srcs[0], wires) << w->opVal;
    } else if (!strcmp(w->op, "RSHIFT")){
      w->value = getSignal(wireArray, w->srcs[0], wires) >> w->opVal;
    } else if (!strcmp(w->op, "NOT")){
      w->value = ~getSignal(wireArray, w->srcs[0], wires);
    } else {
      w->value = getSignal(wireArray, w->srcs[0], wires);
    }
    w->done = true;
  }
  return w->value;
}


static char** getMatches(char* line, int* size){
  regex_t regex;
  size_t maxMatches = 4;
  size_t subMatches = 1;
  regmatch_t matchArray[subMatches];

  regcomp(&regex, "\\w+", REG_EXTENDED);

  char** matches = (char**) malloc(maxMatches*sizeof(char*));

  for (int i = 0; i < maxMatches; i++) {
    if (regexec(&regex, line, subMatches, matchArray, 0)){
      break;
    }
    (*size)++;

    unsigned int offset = matchArray[0].rm_eo;

    char* tempCursor = (char*)malloc(strlen(line)+1);
    strcpy(tempCursor, line);
    tempCursor[matchArray[0].rm_eo] = 0;
    matches[i] = tempCursor + matchArray[0].rm_so;
    line += offset;
  }

  regfree(&regex);

  return matches;
}

Wire* createWires(char** lines, int size){
  Wire* wireArray = (Wire*)malloc(size*sizeof(Wire));
  for (int i= 0; i< size; i++){
    int matchesNum = 0;
    char** matches = getMatches(lines[i], &matchesNum);
    char** sources = (char**)(malloc(2*sizeof(char*)));
    if (matchesNum == 4){
      if (!strcmp(matches[1], "AND") || !strcmp(matches[1], "OR")){
        sources[0] = matches[0];
        sources[1] = matches[2];
        Wire newWire = { .name=matches[3], .value=0, .srcs=sources, .op=matches[1], .opVal=0, .done=false};
        wireArray[i] = newWire;
      } else {
        sources[0] = matches[0];
        Wire newWire = { .name=matches[3], .value=0, .srcs=sources, .op=matches[1], .opVal=atoi(matches[2]), .done=false};
        wireArray[i] = newWire;
      }
    } else if (matchesNum == 3){
      sources[0] = matches[1];
      Wire newWire = { .name=matches[2], .value=0, .srcs=sources, .op=matches[0], .opVal=0, .done=false};
      wireArray[i] = newWire;
    } else {
      int val = 0;
      int d = false;
      if (isdigit(matches[0][0])){
        sources = NULL;
        val = atoi(matches[0]);
        d = true;
      } else {
        sources[0] = matches[0];
      }
      Wire newWire = { .name=matches[1], .value=val, .srcs=sources, .op="NONE", .opVal=0, .done=d};
      wireArray[i] = newWire;
    }
  }
  return wireArray;
}
