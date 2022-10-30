#ifndef SRC_CAT_FILES_H_
#define SRC_CAT_FILES_H_

#include <getopt.h>
#include <stdio.h>

typedef struct filesData {
  unsigned int filesCount;
  unsigned int currentFileIndex;
  FILE* currentFile;
  char** fileNames;
  char currentSymbol;
} filesData;

filesData init(int argc, char** argv, int optind);
int openFile(filesData* data);
void destroy(filesData data);
int isAllFilesDone(filesData data);
void closeCurrentFile(filesData* data);
int readingFromFile(filesData* data);
#endif  // SRC_CAT_FILES_H_