#include "flags.h"

#include <stdio.h>
#include <stdlib.h>

Flags getFlags(int argCount, char** argVector) {
  Flags myFlags;
  defaultFlags(&myFlags);
  int opt;
  while ((opt = getopt_long(argCount, argVector, "benstv?", long_options,
                            NULL)) != -1) {
    switch (opt) {
      case 'b':
        myFlags.bflag = FLAGACTIVATED;
        break;
      case 'e':
        myFlags.eflag = FLAGACTIVATED;
        break;
      case 'n':
        myFlags.nflag = FLAGACTIVATED;
        break;
      case 's':
        myFlags.sflag = FLAGACTIVATED;
        break;
      case 't':
      case 'v':
        myFlags.vflag = FLAGACTIVATED;
        break;
      case '?':
        printf("usage: cat [-bens] [file ...]\n");
    }
  }
  return myFlags;
}
void defaultFlags(Flags* flags) {
  flags->bflag = flags->eflag = flags->nflag = flags->sflag = flags->vflag =
      FLAGAINCTIVATED;
}