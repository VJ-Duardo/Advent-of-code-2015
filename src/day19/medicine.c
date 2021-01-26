#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <stdbool.h>

#include "day19/medicine.h"
#include "utils/utils.h"


int main(void){
  char* input = getFileContent((char*)"src/day19/molecule.txt");
  int lines = 0;
  char** lineArray = getSplitArray(input, "\n =>", &lines);
  lines--;

  char* molecule = lineArray[lines];
  int newSize = 0;
  Rep** reps = createReps(lineArray, lines, &newSize);
  
  printf("%d\n", doAllReplacements(reps, molecule, newSize));
  printf("%d\n", doMoleculeFabrication(reps, newSize, molecule, 0)); 

  return 0;
}



Rep** createReps(char** lines, int size, int* newSize){
  Rep** reps = (Rep**) malloc(size*sizeof(Rep*));
  for (int i=0, j=0; i < size; i+=2, j++){
    Rep* rep = (Rep*) malloc(sizeof(Rep));
    rep->from = lines[i];
    rep->to = lines[i+1];
    reps[j] = rep;
    (*newSize)++;
  }
  return reps;
}


static char** getNewMolecules(char* molecule, char* match, char* replacement, int* count){
  regex_t regex;
  size_t maxMatches = strlen(molecule);
  size_t subMatches = 1;
  regmatch_t matchArray[subMatches];

  regcomp(&regex, match, REG_EXTENDED);

  char* cursor = (char*) malloc(strlen(molecule)+1);
  strcpy(cursor, molecule);
  int c = 0;
  char** newMolecules = (char**) NULL;
  for (int i = 0; i < maxMatches; i++) {
    if (regexec(&regex, cursor, subMatches, matchArray, 0)){
      break;
    }

    unsigned int offset = matchArray[0].rm_eo;

    char* newMolecule = (char*) malloc(strlen(molecule)+strlen(replacement)+1);
    strcpy(newMolecule, molecule);
    strcpy(newMolecule+matchArray[0].rm_so+c, replacement);
    strcpy(newMolecule+matchArray[0].rm_so+strlen(replacement)+c, molecule+matchArray[0].rm_eo+c);

    newMolecules = realloc(newMolecules, (i+1)*sizeof(char*));
    newMolecules[i] = newMolecule;
    c += offset;
    cursor += offset;
    (*count)++;
  }
  free(cursor-c);

  regfree(&regex);
  return newMolecules;
}


int doAllReplacements(Rep** replacements, char* molecule, int size){
  char** molecules = (char**) NULL;
  int result = 0;
  int newMols = 0;
  for(int i=0; i < size; i++){
    char** newMolecules = getNewMolecules(molecule, replacements[i]->from, replacements[i]->to, &newMols);
    for (int j =0; j<newMols; j++){
      bool duplicate = false;
      for (int k=0; k< result; k++){
        if (!strcmp(newMolecules[j], molecules[k])){
          duplicate = true;
          break;
        }
      }
      if (!duplicate){
        molecules = realloc(molecules, (result+1)*sizeof(char*));
        molecules[result++] = newMolecules[j];
      } else {
        free(newMolecules[j]);
      }
    }
    newMols = 0;
  }

  for (int i=0;i < result; free(molecules[i++]));
  free(molecules);
  return result;
}



int doMoleculeFabrication(Rep** replc, int size, char* molecule, int count){
  if (!strcmp(molecule, "e")){
    return count;
  }
  for (int i=0; i < size; i++){
    int matches = 0;
    char** newMolecules = getNewMolecules(molecule, replc[i]->to, replc[i]->from, &matches);
    for (int j=0; j< matches; j++){
      int r = doMoleculeFabrication(replc, size, newMolecules[j], count+1);
      free(newMolecules[j]);
      if (r >0){
        for (int k=j+1; k < matches; free(newMolecules[k++]));
        free(newMolecules);
        return r;
      }
    }
    free(newMolecules);
  }
  return 0;
}