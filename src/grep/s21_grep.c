
#include "s21_grep.h"

#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  grep(argc, argv);
  return 0;
}

void grep(int argCount, char** argVector) {
  Grep myGrep = initGrep(argCount, argVector);
  destroyGrep(&myGrep);
}

Grep initGrep(int argCount, char** argVector) {
  Grep newGrep;
  newGrep.regEx = malloc(sizeof(pcre*));
  newGrep.regExCount = newGrep.flags = 0;
  fillFlags(&newGrep, argCount, argVector);

  return newGrep;
}
void destroyGrep(Grep* src) {
  for (int i = 0; i < src->regExCount; i++)
    if (src->regEx[i] != NULL) free(src->regEx[i]);
  if (src->regEx != NULL) free(src->regEx);
}

int fillFlags(Grep* src, int argCount, char** argVector) {
  int opt;
  while ((opt = getopt(argCount, argVector, "e:ivclnsf:o?")) != -1) {
    switch (opt) {
      case 'e':
        src->flags |= E_FLAG_ACTIVATED;  // !
        addAndCompileRegex(src, optarg);
        break;
      case 'f':
        src->flags |= F_FLAG_ACTIVATED;  // !
        addAndCompileRegex(src, optarg);
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
int addAndCompileRegex(Grep* src, char* reg) {
  int res = 1;
  pcre* compiledReg = getCompileRegex(reg);
  if (compiledReg == NULL || addCompiledRegex(src, compiledReg)) res = 0;

  return res;
}

pcre* getCompileRegex(char* reg) {
  pcre* regCompiled = NULL;
  const char* error = NULL;
  int erroffset;
  regCompiled = pcre_compile(reg, 0, &error, &erroffset, NULL);

  // ! add error check
  return regCompiled;
}

int addCompiledRegex(Grep* src, pcre* compiledReg) {
  int res = 1;
  size_t count = src->regExCount;
  if (realloc(src, count + 1)) {
    src->regEx[count] = compiledReg;
    src->regExCount++;
  } else {
    res = 0;
  }
  return res;
}
