#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <pcre.h>

#include "file.h"
#include "filesData.h"

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

#define MATCHED_INDEX_ARR_SIZE 3
#define REG_INDEX_ERROR -21

typedef struct s_Grep {
  pcre** regEx;
  int regExCount;
  size_t flags;
  int regOptions;
  int matchedIndexes[MATCHED_INDEX_ARR_SIZE];
} Grep;
void grep(int, char**);
Grep initGrep(int, char**);
void setOptions(Grep* src, int argCount, char** argVector);

void destroyGrep(Grep*);
void findAndSetPattern(Grep* src, FilesData* data);
void fillFlags(Grep*, int, char**);
int addAndCompileRegex(Grep*, char*, int);
pcre* getCompiledRegex(char*, int);
int addCompiledRegex(Grep*, pcre*);
int setMatchedIndex(Grep*, File, int index, int start);

void printSubExpressions(Grep* g, File* f, FilesData d, int regIndex);
void printSubStr(int start, int end, char* str, Grep g, FilesData d, File f);

void printFileName(FilesData data, int isHActivaed);
void delPatternFromFiles(FilesData* data);
void setRegFromFile(Grep* src, char* fileName);
int printMatchedline(Grep g, File f, FilesData d);
int isMatchedOnceInLine(Grep g, File f);

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