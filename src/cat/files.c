#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

filesData init(int argCount, char** argVector, int index) {
  filesData myFilesData;

  myFilesData.currentFileIndex = 0;

  int count = argCount - index;
  myFilesData.filesCount = count;

  myFilesData.fileNames = (char**)calloc(count, sizeof(char*));
  for (int i = 0; i < count; i++) {
    myFilesData.fileNames[i] = strdup(argVector[index]);
    index++;
  }
  return myFilesData;
}

int openFile(filesData* data) {
  int res = 1;
  if (data->currentFileIndex != data->filesCount) {
    data->currentFile = fopen(data->fileNames[data->currentFileIndex], "rb");
    if (data->currentFile == NULL) {
      fprintf(stderr, "%s: No such file or directory\n",
              data->fileNames[data->currentFileIndex]);
      res = 0;
    }
  }
  return res;
}

void destroy(filesData data) {
  if (data.currentFile != NULL) fclose(data.currentFile);
  if (data.fileNames != NULL) {
    for (int i = 0; i < (int)data.filesCount; i++)
      if (data.fileNames[i] != NULL) free(data.fileNames[i]);
    free(data.fileNames);
  }
}

int isAllFilesDone(filesData data) {
  return data.currentFileIndex >= data.filesCount;
}
void closeCurrentFile(filesData* data) {
  if (data->currentFile != NULL) fclose(data->currentFile);
  data->currentFile = NULL;
}

int readingFromFile(filesData* data) {
  int res = 1;
  if (fgets(data->buffer, BUFFERSIZE,
            (data->currentFile != NULL ? data->currentFile : stdin)) == NULL)
    res = 0;
  return res;
}