#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int bflag = 0, eflag = 0, nflag = 0, sflag = 0;
  int opt;

  while ((opt = getopt(argc, argv, "bens?")) != -1) {
    switch (opt) {
      case 'b':
        bflag++;
        break;
      case 'e':
        eflag++;
        break;
      case 'n':
        nflag++;
        break;
      case 's':
        sflag++;
        break;
      case '?':
        printf("usage: cat [-bens] [file ...]\n");
        exit(1);
    }
  }

  const int bufferSize = 4096;
  char buffer[bufferSize];
  int currentFile = optind;
  FILE *fp;

  while (currentFile <= argc) {
    if (currentFile != argc) {
      fp = fopen(argv[currentFile], "rb");
      if (fp == NULL) {
        fprintf(stderr, "%s: %s: No such file or directory", argv[0],
                argv[currentFile]);
        exit(1);
      }
    }

    int lastLineBlank = 0;
    int lineNumber = 1;

    while (fgets(buffer, bufferSize, (fp == NULL ? stdin : fp))) {
      int length = strlen(buffer);
      buffer[length - 1] = '\0';

      if (sflag) {
        length = strlen(buffer);
        int currentLineBlank = (length <= 1) ? 1 : 0;
        if (lastLineBlank && currentLineBlank) {
          continue;
        }
        lastLineBlank = currentLineBlank;
      }

      if (bflag) {
        length = strlen(buffer);
        if (length >= 1) {
          char *tmp = strdup(buffer);
          buffer[0] = '\0';
          sprintf(buffer, "%*d\t", 6, lineNumber++);
          strcat(buffer, tmp);
        }
      }

      else if (nflag) {
        char *tmp = strdup(buffer);
        buffer[0] = '\0';
        sprintf(buffer, "%*d\t", 6, lineNumber++);
        strcat(buffer, tmp);
      }

      if (eflag) {
        length = strlen(buffer);
        buffer[length] = '$';
        buffer[length + 1] = '\0';
      }

      fprintf(stdout, "%s\n", buffer);
    }

    fclose(fp);
    currentFile++;
  }

  return 0;
}