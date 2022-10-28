#ifndef SRC_CAT_FLAGS_H_
#define SRC_CAT_FLAGS_H_

#define FLAGACTIVATED 1
#include <getopt.h>
#include <stdio.h>

static struct option const long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {"show-ends", no_argument, NULL, 'E'},
    {"show-tabs", no_argument, NULL, 'T'},
    {"show-all", no_argument, NULL, 'A'},
};

typedef struct flags {
  unsigned short bflag, eflag, nflag, sflag, vflag;
} Flags;
Flags* getFlags(int argCount, char** argVector);
void defaultFlags(Flags* flags);

#endif  // SRC_CAT_FLAGS_H_