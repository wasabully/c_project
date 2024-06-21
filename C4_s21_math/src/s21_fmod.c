#include "s21_math.h"

long double s21_fmod(double x, double y) {
  long double res = 0;
  if (y == S21_INF || y == -S21_INF) {
    if (x == y) {
      res = 0;
    } else {
      res = x;
    }
  } else if (y == 0 || y == S21_NAN || x == S21_NAN || x == S21_INF ||
             x == S21_NINF || x == -S21_INF) {
    res = S21_NAN;
  } else if (x == 0) {
    res = 0;
  } else {
    long long int mod = 0;
    mod = x / y;
    res = (long double)x - mod * (long double)y;
  }
  return res;
}