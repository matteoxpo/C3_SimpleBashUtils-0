#ifndef SRC_CAT_FILESDATA_FILESDATA_H_
#define SRC_CAT_FILESDATA_FILESDATA_H_

#include <getopt.h>
#include <stdio.h>

#include "flags.h"

typedef struct s_FilesData {
  Flags flags;

  unsigned int filesCount;
  char** fileNames;

  unsigned int currentFileIndex;
  char* currentFileName;

  void (*del)(struct s_FilesData* self);
} FilesData;

FilesData initFilesData(int argc, char** argv, int index);
void destroyFilesData(FilesData* data);

int isAllFilesDone(FilesData data);
void doStepToNextFile(FilesData* data);

#endif  // SRC_CAT_FILESDATA_FILESDATA_H_