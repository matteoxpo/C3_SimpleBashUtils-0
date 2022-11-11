
#include "s21_grep.h"

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "file.h"
#include "filesData.h"

int main(int argc, char** argv) {
  grep(argc, argv);
  return 0;
}

void grep(int argCount, char** argVector) {
  Grep myGrep = initGrep(argCount, argVector);
  FilesData myFilesData = initFilesData(argCount, argVector);
  if (!isEFlagActivated(myGrep)) {
    findAndSetPattern(&myGrep, &myFilesData);
    delPatternFromFiles(&myFilesData);
    deactivateFlag(&myGrep, E_FLAG_ACTIVATED);
  }

  while (!isAllFilesDone(myFilesData)) {
    File myFile =
        initFile(myFilesData.currentFileName, isSFlagActivated(myGrep));
    if (!openFile(&myFile, !isSFlagActivated(myGrep))) {
      doStepToNextFile(&myFilesData);
      continue;
    }
    int matchedCount = 0;
    int matchedL = 0;
    while (readLineFromFile(&myFile)) {
      for (int i = 0; i < myGrep.regExCount; i++) {
        //
        int isMatched = setMatchedIndex(&myGrep, myFile, i, 0) > 0;
        //
        if (isMatched && !isVFlagActivated(myGrep)) {
          //
          if (isLFlagActivated(myGrep)) matchedL = 1;
          //
          if (isOFlagActivated(myGrep))
            printSubExpressions(&myGrep, &myFile, i);
          matchedCount++;

          // if (isNFlagActivated(myGrep))
        } else if (!isMatched && isVFlagActivated(myGrep)) {
          // something else lol
          matchedCount++;
        }

        if (!isLFlagActivated(myGrep) && !isLFlagActivated(myGrep) &&
            !isOFlagActivated(myGrep) && !isCFlagActivated(myGrep) &&
            isMatched) {
          printFileName(myFilesData, isHFlagActivated(myGrep));
          myFile.lineFromFile[strlen(myFile.lineFromFile) - 1] == '\n'
              ? printf("%s", myFile.lineFromFile)
              : printf("%s\n", myFile.lineFromFile);
        }
      }
      resetLineFromfile(&myFile);
    }
    if (matchedCount != 0 && !isLFlagActivated(myGrep) &&
        isCFlagActivated(myGrep)) {
      printFileName(myFilesData, isHFlagActivated(myGrep));
      printf("%d\n", matchedCount);
    }
    if (matchedL) {
      printf("%s\n", myFile.fileName);
    }

    resetFile(&myFile);
    doStepToNextFile(&myFilesData);
  }
  destroyGrep(&myGrep);
  myFilesData.del(&myFilesData);
}

Grep initGrep(int argCount, char** argVector) {
  Grep newGrep;
  newGrep.matchedIndexes[0] = newGrep.matchedIndexes[1] =
      newGrep.matchedIndexes[2] = -1;
  newGrep.regEx = malloc(sizeof(pcre*));
  newGrep.regExCount = newGrep.flags = 0;
  fillFlags((&newGrep), argCount, argVector);

  return newGrep;
}

void destroyGrep(Grep* src) {
  for (int i = 0; i < src->regExCount; i++)
    if (src->regEx[i] != NULL) free(src->regEx[i]);
  if (src->regEx != NULL) free(src->regEx);
}

int setMatchedIndex(Grep* src, File f, int index, int start) {
  int res = REG_INDEX_ERROR;
  if (index > -1 && index < src->regExCount)
    res = pcre_exec(src->regEx[index], NULL, f.lineFromFile,
                    strlen(f.lineFromFile), start, 0, src->matchedIndexes,
                    MATCHED_INDEX_ARR_SIZE);
  return res;
}

void findAndSetPattern(Grep* src, FilesData* data) {
  addAndCompileRegex(src, data->currentFileName, src->regOptions);
  doStepToNextFile(data);
}

void printSubExpressions(Grep* g, File* f, int regIndex) {
  int start = g->matchedIndexes[0];
  int end = g->matchedIndexes[1];
  while (start != end) {
    printSubStr(start, end, f->lineFromFile, isNFlagActivated(*g),
                isOFlagActivated(*g), *f);
    setMatchedIndex(g, *f, regIndex, end);
    start = g->matchedIndexes[0];
    end = g->matchedIndexes[1];
  }
}

void printFileName(FilesData data, int isHActivaed) {
  if (data.filesCount > 1 && !isHActivaed)
    printf("%s:", data.fileNames[data.currentFileIndex]);
}

void printSubStr(int start, int end, char* str, int isNAcivated,
                 int isOActivated, File f) {
  if (isOActivated) {
    printf("%s:", f.fileName);
  }
  if (isNAcivated) {
    printf("%d:", f.numLineInFile);
  }

  for (int i = start; i < end; i++) {
    printf("%c", str[i]);
  }
  printf("\n");
}

void fillFlags(Grep* src, int argCount, char** argVector) {
  int opt;
  src->regOptions = 0;
  while ((opt = getopt_long(argCount, argVector, "e:ivclnshf:o?", NULL,
                            NULL)) != -1) {
    switch (opt) {
      case 'i':
        src->flags |= I_FLAG_ACTIVATED;
        src->regOptions |= PCRE_CASELESS;
        break;
      case 's':
        src->flags |= S_FLAG_ACTIVATED;
        break;
      case '?':
        printf("!!!\n");
    }
  }
  optind = 1;
  while ((opt = getopt_long(argCount, argVector, "e:ivclnshf:o?", NULL,
                            NULL)) != -1) {
    switch (opt) {
      case 'e':
        src->flags |= E_FLAG_ACTIVATED;
        addAndCompileRegex(src, optarg, src->regOptions);
        break;
      case 'f':
        src->flags |= F_FLAG_ACTIVATED;
        File myFile = initFile(optarg, !isSFlagActivated(*src));
        if (isFileOpened(myFile)) {
          char* reg = getFirstWordFromFile(myFile);
          if (reg != NULL) {
            addAndCompileRegex(src, reg, src->regOptions);
            free(reg);
          } else if (!(isSFlagActivated(*src))) {
            printf("%s: Empty file\n", reg);
          }
          closeFile(&myFile);
        }
        break;
      case 'i':
        src->flags |= I_FLAG_ACTIVATED;
        break;
      case 'v':
        src->flags |= V_FLAG_ACTIVATED;
        break;
      case 'c':
        src->flags |= C_FLAG_ACTIVATED;
        break;
      case 'l':
        src->flags |= L_FLAG_ACTIVATED;
        break;
      case 'n':
        src->flags |= N_FLAG_ACTIVATED;
        break;
      case 'h':
        src->flags |= H_FLAG_ACTIVATED;
        break;
      case 's':
        src->flags |= S_FLAG_ACTIVATED;
        break;
      case 'o':
        src->flags |= O_FLAG_ACTIVATED;
        break;
      case '?':
        printf("!!!\n");
    }
  }

  if (isVFlagActivated(*src) && isOFlagActivated(*src))
    deactivateFlag(src, O_FLAG_ACTIVATED);
}

int addAndCompileRegex(Grep* src, char* reg, int options) {
  int res = 1;
  pcre* compiledReg = getCompiledRegex(reg, options);
  if (compiledReg == NULL || addCompiledRegex(src, compiledReg)) res = 0;

  return res;
}

pcre* getCompiledRegex(char* reg, int options) {
  pcre* regCompiled = NULL;
  const char* error = NULL;
  int erroffset;
  regCompiled = pcre_compile(reg, options, &error, &erroffset, NULL);
  // ! add error check
  return regCompiled;
}

int addCompiledRegex(Grep* src, pcre* compiledReg) {
  int res = 1;
  size_t count = src->regExCount;
  if (src != NULL) {
    src->regEx = realloc(src->regEx, (count + 1) * sizeof(pcre*));
    if (src->regEx != NULL) {
      src->regEx[count] = compiledReg;
      src->regExCount++;
    } else {
      res = 0;
    }
  }
  return res;
}

int isEFlagActivated(Grep g) { return g.flags & E_FLAG_ACTIVATED; }
int isIFlagActivated(Grep g) { return g.flags & I_FLAG_ACTIVATED; }
int isVFlagActivated(Grep g) { return g.flags & V_FLAG_ACTIVATED; }
int isCFlagActivated(Grep g) { return g.flags & C_FLAG_ACTIVATED; }
int isLFlagActivated(Grep g) { return g.flags & L_FLAG_ACTIVATED; }
int isNFlagActivated(Grep g) { return g.flags & N_FLAG_ACTIVATED; }
int isHFlagActivated(Grep g) { return g.flags & H_FLAG_ACTIVATED; }
int isSFlagActivated(Grep g) { return g.flags & S_FLAG_ACTIVATED; }
int isFFlagActivated(Grep g) { return g.flags & F_FLAG_ACTIVATED; }
int isOFlagActivated(Grep g) { return g.flags & O_FLAG_ACTIVATED; }

void delPatternFromFiles(FilesData* data) {
  if (data->fileNames[0] != NULL) {
    free(data->fileNames[0]);
    for (int i = 0; i < data->filesCount - 1; i++)
      data->fileNames[i] = data->fileNames[i + 1];

    data->filesCount--;
    data->currentFileName = data->fileNames[0];
    data->currentFileIndex = 0;
  }
}

void deactivateFlag(Grep* g, int flagActivatedValue) {
  g->flags &= ~flagActivatedValue;
}