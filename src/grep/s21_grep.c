
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
    int isMathedInLine = 0;
    while (readLineFromFile(&myFile)) {
      for (int i = 0; i < myGrep.regExCount; i++) {
        int isMatched = setMatchedIndex(&myGrep, myFile, i, 0) > 0;

        isMathedInLine = isMatchedOnceInLine(myGrep, myFile) > 0;
        // printf("matched == %d\n", isMathedInLine);

        if ((isMatched && !isVFlagActivated(myGrep)) ||
            (!isMathedInLine && isVFlagActivated(myGrep))) {
          //
          if (isLFlagActivated(myGrep)) matchedL = 1;
          //
          if (!isCFlagActivated(myGrep)) {
            if (isNFlagActivated(myGrep) && !isOFlagActivated(myGrep) &&
                !isLFlagActivated(myGrep)) {
            }
            //
            if (isOFlagActivated(myGrep) && !isLFlagActivated(myGrep)) {
              printSubExpressions(&myGrep, &myFile, myFilesData, i);
            }
          }

          if (!isVFlagActivated(myGrep) || (isVFlagActivated(myGrep)))
            if (printMatchedline(myGrep, myFile, myFilesData)) {
              break;
            }
          matchedCount++;
        }
      }

      resetLineFromfile(&myFile);
    }

    if (!isLFlagActivated(myGrep) && isCFlagActivated(myGrep)) {
      printFileName(myFilesData, isHFlagActivated(myGrep));
      printf("%d\n", matchedCount);
    }

    if (isNFlagActivated(myGrep))
      if (!isVFlagActivated(myGrep) ||
          (isVFlagActivated(myGrep) && (isMathedInLine)))
        printf("%d:", myFile.numLineInFile);

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

void printSubExpressions(Grep* g, File* f, FilesData d, int regIndex) {
  int start = g->matchedIndexes[0];
  int end = g->matchedIndexes[1];
  while (start != -1 && end != -1) {
    printSubStr(start, end, f->lineFromFile, *g, d, *f);
    setMatchedIndex(g, *f, regIndex, end);

    start = g->matchedIndexes[0];
    end = g->matchedIndexes[1];
    printf("\n");
  }
}
int isMatchedOnceInLine(Grep g, File f) {
  int matchedIndexesV[MATCHED_INDEX_ARR_SIZE];

  int isMatched =
      pcre_exec(g.regEx[0], NULL, f.lineFromFile, strlen(f.lineFromFile), 0, 0,
                matchedIndexesV, MATCHED_INDEX_ARR_SIZE);

  for (int j = 0; j < g.regExCount; j++) {
    int start = matchedIndexesV[0];
    int end = matchedIndexesV[1];
    while (start != -1 && end != -1) {
      if (isMatched > 0) break;
      isMatched =
          pcre_exec(g.regEx[j], NULL, f.lineFromFile, strlen(f.lineFromFile),
                    end, 0, matchedIndexesV, MATCHED_INDEX_ARR_SIZE);

      start = matchedIndexesV[0];
      end = matchedIndexesV[1];
    }
  }
  return isMatched;
}

int printMatchedline(Grep g, File f, FilesData d) {
  int res = 0;
  if (!isLFlagActivated(g) && !isLFlagActivated(g) && !isOFlagActivated(g) &&
      !isCFlagActivated(g)) {
    printFileName(d, isHFlagActivated(g));
    f.lineFromFile[strlen(f.lineFromFile) - 1] == '\n'
        ? printf("%s", f.lineFromFile)
        : printf("%s\n", f.lineFromFile);
    res = 1;
  }
  return res;
}

void printFileName(FilesData data, int isHActivaed) {
  if (data.filesCount > 1 && !isHActivaed)
    printf("%s:", data.fileNames[data.currentFileIndex]);
}

void printSubStr(int start, int end, char* str, Grep g, FilesData d, File f) {
  printFileName(d, isHFlagActivated(g));
  if (isNFlagActivated(g)) printf("%d:", f.numLineInFile);
  for (int i = start; i < end; i++) printf("%c", str[i]);
}

void fillFlags(Grep* src, int argCount, char** argVector) {
  setOptions(src, argCount, argVector);

  int opt;
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
        setRegFromFile(src, optarg);
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

void setOptions(Grep* src, int argCount, char** argVector) {
  int opt = 0;
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
}

void setRegFromFile(Grep* src, char* fileName) {
  File myFile = initFile(fileName, !isSFlagActivated(*src));
  if (isFileOpened(myFile)) {
    char* reg = fileName;
    size_t lineSize = 0;
    while (getline(&reg, &lineSize, myFile.fileStream) > 0) {
      if (reg == NULL) break;
      if (reg[0] == '\n') continue;
      if (reg[strlen(reg) - 1] == '\n') reg[strlen(reg) - 1] = '\0';
      addAndCompileRegex(src, reg, src->regOptions);
      free(reg);
      reg = NULL;
    }
  }
  closeFile(&myFile);
}