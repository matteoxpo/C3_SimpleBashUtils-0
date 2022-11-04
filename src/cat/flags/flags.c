#include "flags.h"

#include <stdio.h>
#include <stdlib.h>

Flags getFlags(int argCount, char** argVector) {
  Flags myFlags;
  defaultFlags(&myFlags);
  myFlags.binFlags = 0;
  int opt;
  while ((opt = getopt_long(argCount, argVector, "benstvTE?", long_options,
                            NULL)) != -1) {
    switch (opt) {
      case 'b':
        myFlags.binFlags |= B_FLAG_ACTIVATED;
        break;
      case 'v':
        myFlags.binFlags |= V_FLAG_ACTIVATED;
        break;
      case 'E':
        myFlags.binFlags |= E_FLAG_ACTIVATED;
        break;
      case 'e':
        myFlags.binFlags |= E_FLAG_ACTIVATED;
        myFlags.binFlags |= V_FLAG_ACTIVATED;
        break;
      case 'n':
        myFlags.binFlags |= N_FLAG_ACTIVATED;
        break;
      case 's':
        myFlags.binFlags |= S_FLAG_ACTIVATED;
        break;
      case 'T':
        myFlags.binFlags |= T_FLAG_ACTIVATED;
        break;
      case 't':
        myFlags.binFlags |= T_FLAG_ACTIVATED;
        myFlags.binFlags |= V_FLAG_ACTIVATED;
        break;
      case '?':
        printf("usage: cat [-bens] [file ...]\n");
        break;
    }
  }
  return myFlags;
}
void defaultFlags(Flags* f) { f->binFlags = 0; }

int isBFlagActivated(Flags f) { return f.binFlags & B_FLAG_ACTIVATED; }
int isEFlagActivated(Flags f) { return f.binFlags & E_FLAG_ACTIVATED; }
int isNFlagActivated(Flags f) { return f.binFlags & N_FLAG_ACTIVATED; }
int isSFlagActivated(Flags f) { return f.binFlags & S_FLAG_ACTIVATED; }
int isTFlagActivated(Flags f) { return f.binFlags & T_FLAG_ACTIVATED; }
int isVFlagActivated(Flags f) { return f.binFlags & V_FLAG_ACTIVATED; }