#ifndef SRC_CAT_FILES_H_
#define SRC_CAT_FILES_H_

#include <getopt.h>
#include <stdio.h>

#include "flags.h"

typedef struct FilesData {
  Flags flags;

  unsigned int filesCount;
  char** fileNames;

  unsigned int currentFileIndex;
  char* currentFileName;
} FilesData;

FilesData initFilesData(int argc, char** argv, int index);
void destroyFilesData(FilesData data);
int isAllFilesDone(FilesData data);
void doStepToNextFile(FilesData* data);

#endif  // SRC_CAT_FILES_H_