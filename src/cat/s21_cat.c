#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "filesData.h"
#include "flags.h"

int main(int argc, char **argv) {
  cat(argc, argv);
  return 0;
}

void cat(int argc, char **argv) {
  FilesData myFilesData = initFilesData(argc, argv, optind);

  while (!isAllFilesDone(myFilesData)) {
    File myFile = initFile(myFilesData.currentFileName);
    if (!openFile(&myFile)) return;

    // int lastLineBlank = 0;
    // int lineNumber = 1;

    while (readingFromFile(&myFile)) {
      // int length = strlen(myFilesData.buffer);
      // myFilesData.buffer[length - 1] = '\0';

      // if (myFilesData.flags.sflag) {
      //   length = strlen(myFilesData.buffer);
      //   int currentLineBlank = (length <= 1) ? 1 : 0;
      //   if (lastLineBlank && currentLineBlank) {
      //     continue;
      //   }
      //   lastLineBlank = currentLineBlank;
      // }

      // if (myFlags.bflag) {
      //   length = strlen(myFilesData.buffer);
      //   if (length >= 1) {
      //     char *tmp = strdup(myFilesData.buffer);
      //     myFilesData.buffer[0] = '\0';
      //     sprintf(myFilesData.buffer, "%*d\t", 6, lineNumber++);
      //     strcat(myFilesData.buffer, tmp);
      //   }
      // } else if (myFlags.nflag) {
      //   char *tmp = strdup(myFilesData.buffer);
      //   myFilesData.buffer[0] = '\0';
      //   sprintf(myFilesData.buffer, "%*d\t", 6, lineNumber++);
      //   strcat(myFilesData.buffer, tmp);
      // }

      // if (myFlags.eflag) {
      //   length = strlen(myFilesData.buffer);
      //   myFilesData.buffer[length] = '$';
      //   myFilesData.buffer[length + 1] = '\0';
      // }
      fprintf(stdout, "%c", myFile.currentSymbol);
    }

    doStepToNextFile(&myFilesData);
    closeFile(myFile);
  }
  myFilesData.del(&myFilesData);
}
