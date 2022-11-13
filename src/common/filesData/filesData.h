#ifndef SRC_CAT_FILESDATA_FILESDATA_H_
#define SRC_CAT_FILESDATA_FILESDATA_H_

#include <getopt.h>
#include <stdio.h>

#define CURRENTFILEINDEXERROR 3

typedef struct s_FilesData {
  int filesCount;
  char** fileNames;

  int currentFileIndex;
  char* currentFileName;

  void (*del)(struct s_FilesData* self);
} FilesData;

FilesData initFilesData(int argc, char** argv);
void destroyFilesData(FilesData* data);

int isAllFilesDone(FilesData data);
int doStepToNextFile(FilesData* data);

void printFilesData(FilesData d);

#endif  // SRC_CAT_FILESDATA_FILESDATA_H_