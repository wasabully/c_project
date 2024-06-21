#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* ---------------- Declaration of global functions ---------------- */
typedef struct {
  int num_nonblank;      // b
  int show_endl;         // e
  int show_nonprinting;  // v
  int num_all;           // n
  int squeeze;           // s
  int show_tab;          // t
} Flags;

void parse_cat_flags(int *argc, char *argv[], Flags *flags);
void collapse(FILE *file);
void print_char_hide(int *ch, Flags *flags);
void cat(int argc, char *argv[], Flags flags);

/* ---------------- main -----------------*/
int main(int argc, char *argv[]) {
  Flags flags = {0};
  parse_cat_flags(&argc, argv, &flags);
  cat(argc, argv, flags);
}

/* ---------------- function definitions ----------------*/
void parse_cat_flags(int *argc, char *argv[], Flags *flags) {
  int opt;
  int long_ingex = 0;
  struct option const long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'}};
  while ((opt = getopt_long(*argc, argv, "bevEnstT", long_options,
                            &long_ingex)) != -1) {
    switch (opt) {
      case 'b':
        flags->num_nonblank = 1;
        break;
      case 'e':
        flags->show_nonprinting = 1;
        flags->show_endl = 1;
        break;
      case 'v':
        flags->show_nonprinting = 1;
        break;
      case 'E':
        flags->show_endl = 1;
        break;
      case 'n':
        flags->num_all = 1;
        break;
      case 's':
        flags->squeeze = 1;
        break;
      case 't':
        flags->show_nonprinting = 1;
        flags->show_tab = 1;
        break;
      case 'T':
        flags->show_tab = 1;
        break;
    }
    if (flags->num_nonblank == 1) {
      flags->num_all = 0;
    }
  }
}
void cat(int argc, char *argv[], Flags flags) {
  char previos_char = '\n';
  int str_count = 1, ch;
  for (; optind < argc; optind++) {
    FILE *file = fopen(argv[optind], "r");
    if (file != NULL) {
      while ((ch = fgetc(file)) != EOF) {
        if (flags.squeeze) {
          if (previos_char == '\n') {
            if (ch == '\n') {
              collapse(file);
            }
          }
        }
        if (flags.num_nonblank && ((previos_char == '\n' && ch != '\n') ||
                                   (str_count == 1 && ch != '\n'))) {
          printf("%6d\t", str_count);
          str_count++;
        }
        if (flags.num_all && (previos_char == '\n' || str_count == 1)) {
          printf("%6d\t", str_count);
          str_count++;
        }
        if (flags.show_tab || flags.show_endl || flags.show_nonprinting) {
          print_char_hide(&ch, &flags);
        }
        previos_char = ch;
        putchar(ch);
      }
      fclose(file);
    } else {
      printf("s21_cat: %s: No such file or directory\n", argv[optind]);
    }
    previos_char = -1;
  }
}
void collapse(FILE *file) {
  int temp_char;
  while ((temp_char = fgetc(file)) == '\n') {
    ;
  }
  ungetc(temp_char, file);
}
void print_char_hide(int *ch, Flags *flags) {
  if (flags->show_endl && *ch == '\n') {
    printf("$");
  }
  if (flags->show_tab && *ch == '\t') {
    printf("^");
    *ch = 'I';
  }

  if (*ch < 32 && *ch != '\n' && *ch != '\t') {
    printf("^");
    *ch += 64;
  }
  if (*ch == 127) {
    printf("^");
    *ch -= 64;
  }
  if (*ch > 127) {
    printf("M-");
    if (*ch >= 160 && *ch < 255) {
      *ch -= 128;
    } else {
      printf("^");
      *ch = *ch - 64;
    }
  }
}