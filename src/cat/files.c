#include "files.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

filesData* init(int argCount, char** argVector, int index) {
  filesData* myFilesData = (filesData*)calloc(1, sizeof(filesData));

  myFilesData->currentFile = 0;

  int count = argCount - index;
  myFilesData->filesCount = count;

  myFilesData->fileNames = (char*)calloc(count, sizeof(char*));
  for (int i = 0; i < count; i++) {
    myFilesData->fileNames[i] =
        (char*)calloc(strlen(argVector[index]), sizeof(char));
    strcpy(myFilesData->fileNames[i], argVector[index]);
    index++;
  }
}