#ifndef SRC_CAT_FILES_H_
#define SRC_CAT_FILES_H_

#define BUFFERSIZE 4096

#include <getopt.h>
#include <stdio.h>

typedef struct filesData {
  unsigned int filesCount;
  unsigned int currentFileIndex;
  FILE* currentFile;
  char** fileNames;
  char buffer[BUFFERSIZE];
} filesData;

filesData init(int argc, char** argv, int optind);
int openFile(filesData* data);
void destroy(filesData data);
int isAllFilesDone(filesData data);
void closeCurrentFile(filesData* data);
int readingFromFile(filesData* data);
#endif  // SRC_CAT_FILES_H_