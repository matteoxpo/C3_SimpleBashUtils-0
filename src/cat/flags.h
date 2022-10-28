#ifndef SRC_CAT_FLAGS_H_
#define SRC_CAT_FLAGS_H_

#define FLAGACTIVATED 1

typedef struct flags {
  int bflag, eflag, nflag, sflag, vflag;
} Flags;
Flags* getFlags(const int argv, const char* argc[]);
void defaultFlags(Flags* flags);
#endif  // SRC_CAT_FLAGS_H_