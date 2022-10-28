#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_
#include <stdio.h>

char *readfromFile(FILE *fs, unsigned int dataSize);
FILE *openFile(char *path);
// char *allocMemory(int n);
void clearMemory(char *str);
#endif  // SRC_COMMON_H_