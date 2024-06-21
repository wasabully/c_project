#include "s21_math.h"

long double s21_asin(double x) {
  double res = 0;
  if (x == 1) {
    res = (S21_PI / 2);
  } else if (x == -1) {
    res = -S21_PI / 2;
  } else if (x < -1.0 || x > 1.0) {
    return S21_NAN;
  } else {
    double square_term = 1.0 - x * x;
    double sqrt_term = s21_sqrt(square_term);
    res = s21_atan(x / sqrt_term);
  }
  return res;
}