#include "file.h"

#include <stdlib.h>
#include <string.h>

#include "filesData.h"
File initFile(char* fName, int mode) {
  File newFile;

  newFile.fileStream = NULL;
  newFile.currentSymbol = '\n';
  newFile.pervSymbol = 0;
  newFile.prevPervSymbol = 0;

  newFile.lineFromFile = NULL;
  newFile.sizeOfAllocedMemOfLine = 0;
  newFile.numLineInFile = 0;

  newFile.fileName = fName;

  openFile(&newFile, mode);

  return newFile;
}

int openFile(File* f, int mode) {
  int res = 1;
  if (f->fileStream != NULL) resetFile(f);

  f->fileStream = fopen(f->fileName, "rb");
  if (f->fileStream == NULL) {
    if (mode)
      fprintf(stderr, "s21: %s: No such file or directory\n", f->fileName);
    res = 0;
  }
  return res;
}

void closeFile(File* f) {
  if (f->fileStream != NULL) {
    fclose(f->fileStream);
    f->fileStream = NULL;
  }
}

void resetFile(File* f) {
  closeFile(f);
  if (f->lineFromFile != NULL) {
    free(f->lineFromFile);
    f->lineFromFile = NULL;
  }
}

int isFileOpened(File f) { return f.fileStream != NULL; }

int readingSymbolFromFile(File* f) {
  int res = 1;
  f->prevPervSymbol = f->pervSymbol;
  f->pervSymbol = f->currentSymbol;
  if ((f->currentSymbol = fgetc(f->fileStream)) == EOF) res = 0;
  return res;
}

int isLastTwoLineEmpty(File f) {
  return (f.currentSymbol == '\n' && f.pervSymbol == '\n' &&
          f.prevPervSymbol == '\n');
}

int isCurrLineNotEmpty(File f) {
  return f.pervSymbol == '\n' && f.currentSymbol != '\n';
}

int isNewLine(File f) { return f.pervSymbol == '\n'; }

int isCurrSymbolEntry(File f) { return f.currentSymbol == '\n'; }

void printChangedNotation(File f) {
  char c = f.currentSymbol & 127;
  if ((c >= 0 && c <= 8) || (c >= 11 && c <= 31)) {
    if (f.currentSymbol < 0) fprintf(stdout, "M-");
    c += 64;
    fprintf(stdout, "^%c", c);
  } else if (c == 127) {
    fprintf(stdout, "^?");
  } else if ((c > 31 && c < 127) || c == '\n' || c == '\t') {
    fprintf(stdout, "%c", f.currentSymbol);
  }
}

int isCurSymEqTab(File f) { return f.currentSymbol == '\t'; }

char* getWordFromFile(File f) {
  char* reg = NULL;
  size_t lineSize = 0;
  while (1) {
    getline(&reg, &lineSize, f.fileStream);
    if (reg[0] == EOF || reg[strlen(reg)] == EOF) {
      free(reg);
      reg = NULL;
      break;
    } else {
    }
  }

  return reg;
}

void resetLineFromfile(File* f) {
  if (f->lineFromFile != NULL) {
    free(f->lineFromFile);
    f->lineFromFile = NULL;
  }
}

int readLineFromFile(File* f) {
  f->numLineInFile++;
  int res = -1;
  if (f->fileStream != NULL)
    res = (getline(&(f->lineFromFile), &(f->sizeOfAllocedMemOfLine),
                   f->fileStream) != -1);

  return res;
}