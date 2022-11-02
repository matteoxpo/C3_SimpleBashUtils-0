#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <pcre.h>

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

typedef struct s_Grep {  // MAIN
  /* data */
  pcre** regEx;
  size_t regExCount;
  size_t flags;

} Grep;

Grep initGrep(int, char**);
void destoryGrep(Grep*);
int fillFlags(Grep*, int, char**);
int addAndCompileRegex(Grep*, char*);
pcre* getCompileRegex(char*);
int addCompiledRegex(Grep*, pcre*);
#endif  // SRC_GREP_S21_GREP_H_