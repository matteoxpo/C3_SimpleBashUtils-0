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
        myFlags.bflag = FLAGACTIVATED;  // yes
        break;
      case 'v':
        myFlags.vflag = FLAGACTIVATED;  // no
        break;
      case 'E':
        myFlags.eflag = FLAGACTIVATED;  // yes
        break;
      case 'e':
        myFlags.eflag = FLAGACTIVATED;  // yes
        myFlags.vflag = FLAGACTIVATED;  // yes
        break;
      case 'n':
        myFlags.nflag = FLAGACTIVATED;  // yes
        break;
      case 's':
        myFlags.sflag = FLAGACTIVATED;  // yes
        break;
      case 'T':
        myFlags.Tflag = FLAGACTIVATED;  // yes
        break;
      case 't':
        myFlags.Tflag = FLAGACTIVATED;  // yes
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
      flags->Tflag = FLAGAINCTIVATED;
}