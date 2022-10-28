#ifndef SRC_CAT_FILES_H_
#define SRC_CAT_FILES_H_
#define BUFFERSIZE 4096

#include <getopt.h>
#include <stdio.h>

typedef struct filesData {
  unsigned int filesCount;
  unsigned int currentFile;
  char** fileNames;
  char buffer[BUFFERSIZE];
} filesData;

filesData* init(int argc, char** argv, int optind);

#endif  // SRC_CAT_FILES_H_