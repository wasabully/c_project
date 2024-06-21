#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* ---------------- Declaration of global functions ---------------- */
typedef struct {
  int eFlag;
  int iFlag;
  int vFlag;
  int cFlag;
  int lFlag;
  int nFlag;
  int hFlag;
  int sFlag;
  int fFlag;
  int oFlag;
  int countFiles;
} Flags;

void parseArguments(int *argc, char *argv[], char pattern[], Flags *flags);
int matchRegex(int count, int *result, regex_t regex, int length, char *argv[],
               int *stopper, int *countN, char *line, Flags flags);
void printMatchingLine(char *argv[], int *stopper, int *countN, char *line,
                       Flags flags);
void printOnlyCount(char *argv[], int *count, Flags flags);
void printVFlag(char *argv[], char *line, Flags flags);
void processFiles(int argc, char *argv[], char pattern[], Flags flags);