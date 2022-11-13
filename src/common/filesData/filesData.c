#include "filesData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FilesData initFilesData(int argCount, char** argVector) {
  FilesData myFilesData;

  myFilesData.currentFileIndex = 0;
  int index = optind;
  int count = argCount - index;
  myFilesData.filesCount = count;

  myFilesData.fileNames = (char**)calloc(count, sizeof(char*));
  for (int i = 0; i < count; i++) {
    myFilesData.fileNames[i] = strdup(argVector[index]);
    index++;
  }
  if (count > 0) myFilesData.currentFileName = myFilesData.fileNames[0];
  myFilesData.del = destroyFilesData;
  // printFilesData(myFilesData);
  return myFilesData;
}

int isAllFilesDone(FilesData data) {
  return data.currentFileIndex >= data.filesCount;
}

void destroyFilesData(FilesData* data) {
  if (data->fileNames != NULL) {
    for (int i = 0; i < (int)data->filesCount; i++)
      if (data->fileNames[i] != NULL) free(data->fileNames[i]);
    free(data->fileNames);
  }
}

int doStepToNextFile(FilesData* data) {
  int res = 1;
  data->currentFileIndex++;
  if (data->currentFileIndex > data->filesCount) res = CURRENTFILEINDEXERROR;
  if (!isAllFilesDone(*data)) {
    data->currentFileName = data->fileNames[data->currentFileIndex];
  }
  return res;
}

void printFilesData(FilesData d) {
  for (int i = 0; i < d.filesCount; i++) {
    printf("file #%d -- %s\n", i + 1, d.fileNames[i]);
  }
}