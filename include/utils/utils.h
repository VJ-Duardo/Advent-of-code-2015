#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
extern "C" {
#endif


char* getFileContent(char* path);
char** getSplitArray(char* input, const char* del, int* size);


#ifdef __cplusplus
}
#endif

#endif
