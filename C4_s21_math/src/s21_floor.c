#include "s21_math.h"

long double s21_floor(double x) {
  long double res = (long long int)x;
  if (s21_is_nan(x)) {
    res = x;
  } else if (x == S21_INF) {
    res = S21_INF;
  } else if (x == S21_NINF) {
    res = S21_NINF;
  } else if (res != x) {
    if (x < 0) {
      res -= 1;
    }
  }
  return res;
}
