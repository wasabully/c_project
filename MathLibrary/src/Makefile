CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11

all: clean s21_math.a test gcov_report

test:
	$(CC) $(CFLAGS) --coverage test_u/*.c *.c -o test -lcheck -lm
	./test

s21_math.a:
	$(CC) $(CFLAGS) *.c -c
	ar rc s21_math.a *.o
	ranlib s21_math.a

gcov_report:
	lcov -t "s21_math_test" -o fizzbuzz.info -c -d .
	genhtml -o report fizzbuzz.info

clean:
	rm -rf test *.gcda *.gcno *.o *.info test_u/*.gcno report