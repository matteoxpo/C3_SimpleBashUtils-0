#ifndef SRC_CAT_FILE_FILE_H_
#define SRC_CAT_FILE_FILE_H_

#include <getopt.h>
#include <stdio.h>

#include "filesData.h"

typedef struct s_File {
  char* fileName;
  FILE* fileStream;
  unsigned int currentLine;
  unsigned int currentLineSize;

  char currentSymbol;
  char pervSymbol;
  char prevPervSymbol;

} File;

File initFile(char* fName);
int openFile(File* f);
void closeFile(File f);
int readingFromFile(File* f);
int isLastTwoLineEmpty(File f);
int isCurrLineEmpty(File f);
int isNewLine(File f);
int isCurrSymbolEntry(File f);
void printChangedNotation(File f);
#endif  // SRC_CAT_FILE_FILE_H_