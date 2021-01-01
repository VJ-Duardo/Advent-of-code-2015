#ifndef PAPER_H
#define PAPER_H

#define DIMENSIONS 3

char* getFileContent(char* path);
int** getPresentsArray(char** input, int size);
char** getSplitArray(char* input, const char* del, int* size);
void getNeededUtils(int** presents, int size, int* area, int* ribbon);

#endif
