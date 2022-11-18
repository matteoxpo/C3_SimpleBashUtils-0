#ifndef SRC_CAT_FILE_FILE_H_
#define SRC_CAT_FILE_FILE_H_

#include <getopt.h>
#include <stdio.h>

#include "filesData.h"

#define ERRORR_MESSAGE_ON 1
#define ERRORR_MESSAGE_OFF 0

typedef struct s_File {
  char* fileName;
  FILE* fileStream;

  // cat
  char currentSymbol;
  char pervSymbol;
  char prevPervSymbol;

  // grep

  char* lineFromFile;
  size_t sizeOfAllocedMemOfLine;
  int numLineInFile;

} File;

File initFile(char*, int);
int openFile(File*, int);
void closeFile(File*);
void resetFile(File*);

int isFileOpened(File);
int readingSymbolFromFile(File*);
int isLastTwoLineEmpty(File);
int isCurrLineNotEmpty(File);
int isNewLine(File);
int isCurrSymbolEntry(File);
void printChangedNotation(File);
int isCurSymEqTab(File);

void resetLineFromfile(File*);
int readLineFromFile(File*);

char* getWordFromFile(File f);
#endif  // SRC_CAT_FILE_FILE_H_
