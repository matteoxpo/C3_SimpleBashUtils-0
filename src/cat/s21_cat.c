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
  FilesData myFilesData = initFilesData(argc, argv);

  while (!isAllFilesDone(myFilesData)) {
    File myFile = initFile(myFilesData.currentFileName, ERRORR_MESSAGE_ON);
    if (!openFile(&myFile, ERRORR_MESSAGE_ON)) {
      doStepToNextFile(&myFilesData);
      continue;
    }
    int lineNumber = 1;
    while (readingFromFile(&myFile)) {
      if (myFilesData.flags.sflag && isLastTwoLineEmpty(myFile)) continue;

      if (myFilesData.flags.bflag && isCurrLineEmpty(myFile))
        fprintf(stdout, "%*d\t", 6, lineNumber++);
      else if (myFilesData.flags.nflag && isNewLine(myFile))
        fprintf(stdout, "%*d\t", 6, lineNumber++);

      if (myFilesData.flags.eflag && isCurrSymbolEntry(myFile))
        fprintf(stdout, "$");

      if (myFilesData.flags.Tflag && isCurSymEqTab(myFile)) {
        fprintf(stdout, "^|");
        continue;
      }

      if (myFilesData.flags.vflag)
        printChangedNotation(myFile);
      else
        fprintf(stdout, "%c", myFile.currentSymbol);
    }

    doStepToNextFile(&myFilesData);
    closeFile(myFile);
  }
  myFilesData.del(&myFilesData);
}
