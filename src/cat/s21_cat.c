#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "files.h"
#include "flags.h"

int main(int argc, char **argv) {
  cat(argc, argv);
  return 0;
}

void cat(int argc, char **argv) {
  Flags *myFlags = getFlags(argc, argv);

  char buffer[BUFFERSIZE];
  int currentFile = optind;
  FILE *fp;

  while (currentFile <= argc) {
    if (currentFile != argc) {
      fp = fopen(argv[currentFile], "rb");
      if (fp == NULL) {
        fprintf(stderr, "%s: %s: No such file or directory", argv[0],
                argv[currentFile]);
        exit(0);
      }
    }

    int lastLineBlank = 0;
    int lineNumber = 1;

    while (fgets(buffer, BUFFERSIZE, (fp == NULL ? stdin : fp))) {
      int length = strlen(buffer);
      buffer[length - 1] = '\0';

      if (myFlags->sflag) {
        length = strlen(buffer);
        int currentLineBlank = (length <= 1) ? 1 : 0;
        if (lastLineBlank && currentLineBlank) {
          continue;
        }
        lastLineBlank = currentLineBlank;
      }

      if (myFlags->bflag) {
        length = strlen(buffer);
        if (length >= 1) {
          char *tmp = strdup(buffer);
          buffer[0] = '\0';
          sprintf(buffer, "%*d\t", 6, lineNumber++);
          strcat(buffer, tmp);
        }
      } else if (myFlags->nflag) {
        char *tmp = strdup(buffer);
        buffer[0] = '\0';
        sprintf(buffer, "%*d\t", 6, lineNumber++);
        strcat(buffer, tmp);
      }

      if (myFlags->eflag) {
        length = strlen(buffer);
        buffer[length] = '$';
        buffer[length + 1] = '\0';
      }

      fprintf(stdout, "%s\n", buffer);
    }

    if (fp != NULL) fclose(fp);
    currentFile++;
  }
  if (myFlags != NULL) free(myFlags);
}
