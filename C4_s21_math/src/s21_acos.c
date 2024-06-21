#include "s21_math.h"

long double s21_acos(double x) {
  long double res = (long long int)x;
  if (x == 1) {
    res = 0;
  } else if (x == -1) {
    res = S21_PI;
  } else if (x < 1 && x > -1) {
    res = S21_PI / 2. - s21_asin(x);
  } else {
    res = S21_NAN;
  }
  return res;
}