#include "s21_math.h"

long double s21_atan(double x) {
  long double atan = 0.0;
  if (x == 0) {
    atan = 0.0;
  } else if (x == 1) {
    atan = S21_PI / 4;
  } else if (x == -1) {
    atan = -S21_PI / 4;
  } else if (x > -1.0 && x < 1.0) {
    for (int i = 0; i < 5000; i++) {
      atan += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / (1 + (2 * i));
    }
  } else if (s21_is_nan(x)) {
    atan = S21_NAN;
  } else {
    for (int i = 0; i < 7000; i++) {
      atan += s21_pow(-1, i) * s21_pow(x, -1 - (2 * i)) / (1 + (2 * i));
    }
    atan = S21_PI * s21_sqrt(x * x) / (2 * x) - atan;
  }
  return atan;
}