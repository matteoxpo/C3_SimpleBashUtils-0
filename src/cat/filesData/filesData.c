#include "filesData.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FilesData initFilesData(int argCount, char** argVector, int index) {
  FilesData myFilesData;

  myFilesData.flags = getFlags(argCount, argVector);

  myFilesData.currentFileIndex = 0;

  int count = argCount - index;
  myFilesData.filesCount = count;

  myFilesData.fileNames = (char**)calloc(count, sizeof(char*));
  for (int i = 0; i < count; i++) {
    myFilesData.fileNames[i] = strdup(argVector[index]);
    index++;
  }
  if (count > 0) myFilesData.currentFileName = myFilesData.fileNames[0];
  myFilesData.del = destroyFilesData;

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

void doStepToNextFile(FilesData* data) {
  data->currentFileIndex++;
  if (!isAllFilesDone(*data)) {
    data->currentFileName = data->fileNames[data->currentFileIndex];
  }
}