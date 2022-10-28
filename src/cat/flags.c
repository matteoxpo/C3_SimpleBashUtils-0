#include "flags.h"

#include <stdio.h>
#include <stdlib.h>

Flags *getFlags(int argCount, char **argVector) {
  Flags *myFlags = (Flags *)calloc(1, sizeof(Flags));
  int opt;
  while ((opt = getopt_long(argCount, argVector, "benstv?", long_options,
                            NULL)) != -1) {
    switch (opt) {
      case 'b':
        myFlags->bflag = FLAGACTIVATED;
        break;
      case 'e':
        myFlags->eflag = FLAGACTIVATED;
        break;
      case 'n':
        myFlags->nflag = FLAGACTIVATED;
        break;
      case 's':
        myFlags->sflag = FLAGACTIVATED;
        break;
      case 't':
      case 'v':
        myFlags->vflag = FLAGACTIVATED;
        break;
      case '?':
        printf("usage: cat [-bens] [file ...]\n");
    }
  }
  return myFlags;
}