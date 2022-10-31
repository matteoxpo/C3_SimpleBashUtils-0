#include "file.h"

#include "filesData.h"

File initFile(char* fName) {
  File newFile;

  newFile.currentLine = 1;
  newFile.currentLineSize = 0;
  newFile.currentSymbol = '0';
  newFile.pervSymbol = '0';
  newFile.prevPervSymbol = '0';

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

int isLastTwoStrEmpty(File f) {
  return (f.currentSymbol == '\n' && f.pervSymbol == '\n' &&
          f.prevPervSymbol == '\n');
}