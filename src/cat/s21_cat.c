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
  Flags flags = getFlags(argc, argv);
  FilesData myFilesData = initFilesData(argc, argv);

  while (!isAllFilesDone(myFilesData)) {
    File myFile = initFile(myFilesData.currentFileName, ERRORR_MESSAGE_ON);
    if (!openFile(&myFile, ERRORR_MESSAGE_ON)) {
      doStepToNextFile(&myFilesData);
      continue;
    }
    int lineNumber = 1;
    while (readingSymbolFromFile(&myFile)) {
      if (isSFlagActivated(flags) && isLastTwoLineEmpty(myFile)) continue;

      if (isBFlagActivated(flags) && isCurrLineEmpty(myFile))
        fprintf(stdout, "%*d\t", 6, lineNumber++);
      else if (isNFlagActivated(flags) && isNewLine(myFile))
        fprintf(stdout, "%*d\t", 6, lineNumber++);

      if (isEFlagActivated(flags) && isCurrSymbolEntry(myFile))
        fprintf(stdout, "$");

      if (isTFlagActivated(flags) && isCurSymEqTab(myFile)) {
        fprintf(stdout, "^|");
        continue;
      }

      if (isVFlagActivated(flags))
        printChangedNotation(myFile);
      else
        fprintf(stdout, "%c", myFile.currentSymbol);
    }

    doStepToNextFile(&myFilesData);
    closeFile(myFile);
  }
  myFilesData.del(&myFilesData);
}
