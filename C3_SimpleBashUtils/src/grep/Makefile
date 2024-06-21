CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: clean s21_grep

s21_grep:
	${CC} ${CFLAGS} s21_grep.c -o s21_grep

clean:
	rm -fr s21_grep

rebuild: clean all