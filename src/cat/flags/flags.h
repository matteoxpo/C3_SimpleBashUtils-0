#ifndef SRC_CAT_FLAGS_FLAGS_H_
#define SRC_CAT_FLAGS_FLAGS_H_

#define FLAGACTIVATED 1
#define FLAGAINCTIVATED 0
// cat
#define B_FLAG_ACTIVATED 0b0000000001
#define E_FLAG_ACTIVATED 0b0000000010
#define N_FLAG_ACTIVATED 0b0000000100
#define S_FLAG_ACTIVATED 0b0000001000
#define T_FLAG_ACTIVATED 0b0000010000
#define V_FLAG_ACTIVATED 0b0000100000

// grep
#define E_FLAG_ACTIVATED 0b0000000001  // yes
#define I_FLAG_ACTIVATED 0b0000000010  // yes
#define V_FLAG_ACTIVATED 0b0000000100
#define C_FLAG_ACTIVATED 0b0000001000  // yes(partly)
#define L_FLAG_ACTIVATED 0b0000010000  // partly
#define N_FLAG_ACTIVATED 0b0000100000  // partly
#define H_FLAG_ACTIVATED 0b0001000000
#define S_FLAG_ACTIVATED 0b0010000000
#define F_FLAG_ACTIVATED 0b0100000000
#define O_FLAG_ACTIVATED 0b1000000000  // partly

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

typedef struct s_flags {
  // unsigned short bflag, eflag, nflag, sflag, vflag, Tflag;
  size_t binFlags;
} Flags;
Flags getFlags(int, char**);
void defaultFlags(Flags*);
int isBFlagActivated(Flags);
int isEFlagActivated(Flags);
int isNFlagActivated(Flags);
int isSFlagActivated(Flags);
int isTFlagActivated(Flags);
int isVFlagActivated(Flags);
#endif  // SRC_CAT_FLAGS_FLAGS_H_
