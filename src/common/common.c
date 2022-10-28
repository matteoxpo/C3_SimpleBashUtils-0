#include "common.h"

#include <stdio.h>

char *readfromFile(FILE *fs, unsigned int dataSize) {
  char *reader = (char *)calloc(dataSize, sizeof(char));
}
#include <stdio.h>

// char *allocMemory(int n) { char *newString = (char *)calloc(n, sizeof(char));
// }
FILE *openFile(char *path) {}

void clearMemory(char *str) {
  if (str != NULL) free(str);
}