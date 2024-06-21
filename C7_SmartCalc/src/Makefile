CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
OBJ = s21_stack.c s21_calc.c s21_creditcalc.c s21_calc_X.c
OBJ_TEST = s21_test/main.c s21_test/s21_test.c
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lcheck
endif

all: install

s21_calc.a:
	@$(CC) $(CFLAGS) -c $(OBJ)
	@ar rcs $@ $(OBJ)
	@rm -rf *.o
	@ranlib s21_calc.a

install:
	@mkdir build
	@mkdir calculator
	@cd build/ && qmake  ../SmartCalc/smartCalc.pro && make -j6
	@cp -rf build/smartCalc.app calculator
	@make clean

uninstall:
	@rm -rf calculator

dvi:
	@$(OPEN_CMD) dvi.md

dist:
	@mkdir dist
	@cp -R smartCalc s21_test *.c *.h Makefile dist
	@cp -R dvi.md dist
	@cd dist && tar cvzf smartCalc_v1.0.tgz *
	@cd dist && rm -rf s21_test smartCalc *.c *.h Makefile dvi.md
	@rm -rf calculator

test: clean
	@$(CC) $(CFLAGS) --coverage $(OBJ) $(OBJ_TEST) -o test $(ADD_LIB)
	@./test

test_leaks: clean
	@$(CC) $(CFLAGS) $(OBJ) $(OBJ_TEST) -o test $(ADD_LIB)
	@leaks -atExit -- ./test

gcov_report: test
	@lcov -t "s21_SmartCalc_test" -o fizzbuzz.info -c -d .
	@genhtml -o report fizzbuzz.info
	@$(OPEN_CMD) -a "Google Chrome" report/src/index.html

style:
	@clang-format -style=Google -n *.c *.h s21_test/*.c s21_test/*.h SmartCalc/*.cpp SmartCalc/*.h
	@cppcheck --enable=all --suppress=missingIncludeSystem $(OBJ) s21_test/*.c s21_test/*.h

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM test report build* 

.PHONY: install uninstall dvi dest test test_leaks gcov_report style clean
