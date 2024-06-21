CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
OBJ = s21_matrix.c s21_matrix_help.c s21_matrix_arithmetic.c s21_matrix_another.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck
endif

all: s21_matrix.a test clean

test: clean
	@$(CC) $(CFLAGS) --coverage $(OBJ) unit_test/*.c -o test $(ADD_LIB)
	@./test

s21_matrix.a:
	@$(CC) $(CFLAGS) *.c -c
	@ar rc s21_matrix.a *.o
	@ranlib s21_matrix.a

gcov_report: test
	@lcov -t "s21_matrix_test" -o fizzbuzz.info -c -d .
	@genhtml -o report fizzbuzz.info
	@open -a "Google Chrome" report/src/index.html

style:
	@clang-format -style=Google -i *.c *.h unit_test/*.c unit_test/*.h

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM test

.PHONY:	s21_matrix.a test gcov_report