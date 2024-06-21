#include "s21_grep.h"
/* ---------------- main -----------------*/
int main(int argc, char *argv[]) {
  char pattern[4096];
  Flags flags = {0};
  parseArguments(&argc, argv, pattern, &flags);
  processFiles(argc, argv, pattern, flags);
  return 0;
}
/* ---------------- function definitions ----------------*/
void parseArguments(int *argc, char *argv[], char pattern[], Flags *flags) {
  int opt;
  while ((opt = getopt_long(*argc, argv, "e:ivclnhs", 0, 0)) != -1) {
    switch (opt) {
      case 'e':
        flags->eFlag = 1;
        if (!pattern[0]) {
          strcat(pattern, optarg);
        } else {
          strcat(pattern, "|");
          strcat(pattern, optarg);
        }
        break;
      case 'i':
        flags->iFlag = 1;
        break;
      case 'v':
        flags->vFlag = 1;
        break;
      case 'c':
        flags->cFlag = 1;
        break;
      case 'l':
        flags->lFlag = 1;
        break;
      case 'n':
        flags->nFlag = 1;
        break;
      case 'h':
        flags->hFlag = 1;
        break;
      case 's':
        flags->sFlag = 1;
        break;
    }
  }
  if (flags->eFlag && optind + 1 < *argc) {
    flags->countFiles = 1;
  }
  if (optind + 2 < *argc) {
    flags->countFiles = 1;
  }
  if (flags->lFlag) {
    flags->vFlag = 0;
  }
}

void processFiles(int argc, char *argv[], char pattern[], Flags flags) {
  char line[4096];
  int flag = REG_EXTENDED, length = 0, count = 0, stopper = 0, countN = 1,
      result = 0;
  regex_t regex;
  if (flags.iFlag) {
    flag = REG_ICASE;
  }
  if (flags.eFlag) {
    regcomp(&regex, pattern, flag);
  } else {
    regcomp(&regex, argv[optind], flag);
    optind++;
  }
  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "r");
    if (file != NULL) {
      while (fgets(line, 4095, file) != NULL && stopper == 0) {
        count = matchRegex(count, &result, regex, length, argv, &stopper,
                           &countN, line, flags);
        countN++;
      }
      if (flags.cFlag) {
        printOnlyCount(argv, &count, flags);
      }
      stopper = 0;
      countN = 1;
      fclose(file);
    }
    if (file == NULL && flags.sFlag == 0) {
      printf("s21_grep: %s: No such file or directory\n", argv[optind]);
    }
  }
  regfree(&regex);
}

int matchRegex(int count, int *result, regex_t regex, int length, char *argv[],
               int *stopper, int *countN, char *line, Flags flags) {
  *result = regexec(&regex, line, 0, NULL, 0);
  length = strlen(line);
  if (line[length - 1] == '\n') {
    line[length - 1] = '\0';
  }
  if (*result) {
    printVFlag(argv, line, flags);
  }
  if (!(*result) && flags.vFlag == 0) {
    if (flags.lFlag) {
      printf("%s\n", argv[optind]);
      *stopper = 1;
    }
    if (*stopper == 0) {
      printMatchingLine(argv, stopper, countN, line, flags);
    }
    count++;
  }
  if (flags.vFlag && *result) {
    count++;
  }
  return count;
}

void printMatchingLine(char *argv[], int *stopper, int *countN, char *line,
                       Flags flags) {
  if (flags.nFlag && *stopper == 0) {
    if (flags.countFiles) {
      printf("%s:", argv[optind]);
    }
    printf("%d:%s\n", *countN, line);
  }
  if (flags.hFlag && flags.cFlag == 0) {
    printf("%s\n", line);
  }
  if (flags.countFiles && !flags.cFlag && !flags.nFlag && !flags.hFlag) {
    printf("%s:", argv[optind]);
  }
  if (!flags.cFlag && !flags.nFlag && !flags.hFlag && flags.oFlag == 0) {
    printf("%s\n", line);
  }
}

void printOnlyCount(char *argv[], int *count, Flags flags) {
  if (flags.countFiles && flags.hFlag == 0) {
    printf("%s:", argv[optind]);
  }
  printf("%d\n", *count);
  *count = 0;
}

void printVFlag(char *argv[], char *line, Flags flags) {
  if (flags.vFlag) {
    if (flags.countFiles && flags.cFlag == 0) {
      printf("%s:", argv[optind]);
    }
    if (flags.cFlag == 0) {
      printf("%s\n", line);
    }
  }
}