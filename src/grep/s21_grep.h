#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <pcre.h>

#include "file.h"
#include "filesData.h"

#define E_FLAG_ACTIVATED 0b0000000001
#define I_FLAG_ACTIVATED 0b0000000010
#define V_FLAG_ACTIVATED 0b0000000100
#define C_FLAG_ACTIVATED 0b0000001000
#define L_FLAG_ACTIVATED 0b0000010000
#define N_FLAG_ACTIVATED 0b0000100000
#define H_FLAG_ACTIVATED 0b0001000000
#define S_FLAG_ACTIVATED 0b0010000000
#define F_FLAG_ACTIVATED 0b0100000000
#define O_FLAG_ACTIVATED 0b1000000000

#define MATCHED_INDEX_ARR_SIZE 3
#define REG_INDEX_ERROR -21
#define MATCHED 1
#define DIDNT_MATCHED 0

typedef struct s_Grep {
  pcre** regEx;
  int regExCount;
  size_t flags;
  int regOptions;
  int matchedIndexes[MATCHED_INDEX_ARR_SIZE];
} Grep;
void grep(int, char**);
Grep initGrep(int, char**);
void destroyGrep(Grep*);
void findAndSetPattern(Grep* src, FilesData* data);
void fillFlags(Grep*, int, char**);
int addAndCompileRegex(Grep*, char*, int);
pcre* getCompiledRegex(char*, int);
int addCompiledRegex(Grep*, pcre*);
int setMatchedIndex(Grep*, File, int index, int start);

void ActIfVFlagNonActivated(Grep* g, FilesData* d, File* f, int regIndex);

int isEFlagActivated(Grep);
int isIFlagActivated(Grep);
int isVFlagActivated(Grep);
int isCFlagActivated(Grep);
int isLFlagActivated(Grep);
int isNFlagActivated(Grep);
int isHFlagActivated(Grep);
int isSFlagActivated(Grep);
int isFFlagActivated(Grep);
int isOFlagActivated(Grep);

void deactivateFlag(Grep*, int);
#endif  // SRC_GREP_S21_GREP_H_