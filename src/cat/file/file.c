#include "file.h"

#include "filesData.h"

File initFile(char* fName) {
  File newFile;

  newFile.currentLine = 1;
  newFile.currentLineSize = 0;
  newFile.currentSymbol = '\n';
  newFile.pervSymbol = '\n';
  newFile.prevPervSymbol = '\n';

  newFile.fileName = fName;

  openFile(&newFile);

  return newFile;
}

int openFile(File* f) {
  int res = 1;
  f->fileStream = fopen(f->fileName, "rb");
  if (f->fileStream == NULL) {
    fprintf(stderr, "%s: No such file or directory\n", f->fileName);
    res = 0;
  }
  //   fseek(f->fileStream, 0, SEEK_END);
  //   if (ftell(f->fileStream) == 0) {
  //     res = 0;
  //   } else
  //     fseek(f->fileStream, 0, SEEK_SET);
  return res;
}

void closeFile(File f) {
  if (f.fileStream != NULL) fclose(f.fileStream);
  f.fileStream = NULL;
}

int readingFromFile(File* f) {
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

int isCurrLineEmpty(File f) {
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