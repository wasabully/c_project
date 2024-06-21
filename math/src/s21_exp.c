#include "s21_math.h"

long double s21_exp(double x) {
  long double rez = 1, y = 1;
  long double i = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  int exitLoop = 0;
  while (!exitLoop) {
    rez *= x / i;
    i++;
    y += rez;
    if (y > MAX_LONG_DOUBLE) {
      y = S21_INF;
      exitLoop = 1;
    } else if (s21_fabs(rez) <= S21_EPS) {
      exitLoop = 1;
    }
  }
  y = flag == 1 ? y > MAX_LONG_DOUBLE ? 0 : 1. / y : y;
  return y = y > MAX_LONG_DOUBLE ? S21_INF : y;
}