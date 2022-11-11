
#include "s21_grep.h"

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
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

  if ((!isEFlagActivated(myGrep))) {
    addAndCompileRegex(&myGrep, myFilesData.currentFileName, myGrep.regOptions);
    doStepToNextFile(&myFilesData);
  }
  while (!isAllFilesDone(myFilesData)) {
    File myFile =
        initFile(myFilesData.currentFileName, isSFlagActivated(myGrep));

    if (!openFile(&myFile, !isSFlagActivated(myGrep))) {
      doStepToNextFile(&myFilesData);
      continue;
    }

    char* lineFromFile = NULL;
    size_t sizeOfLine = 0;
    int mass[1026];
    while (getline(&lineFromFile, &sizeOfLine, myFile.fileStream) != -1) {
      //
      int count = 0;
      for (int i = 0; i < myGrep.regExCount; i++) {
        count = pcre_exec(myGrep.regEx[i], NULL, lineFromFile, sizeOfLine, 0, 0,
                          mass, 1026);
        if (count > 0) {
          printf("%s", lineFromFile);
        }
      }
    }
    closeFile(myFile);
    doStepToNextFile(&myFilesData);
  }
  destroyGrep(&myGrep);
  myFilesData.del(&myFilesData);
}

Grep initGrep(int argCount, char** argVector) {
  Grep newGrep;
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

void fillFlags(Grep* src, int argCount, char** argVector) {
  int opt;
  src->regOptions = 0;
  while ((opt = getopt_long(argCount, argVector, "e:ivclnsf:o?", NULL, NULL)) !=
         -1) {
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
  while ((opt = getopt_long(argCount, argVector, "e:ivclnsf:o?", NULL, NULL)) !=
         -1) {
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
          closeFile(myFile);
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
