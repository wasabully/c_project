#include "s21_math.h"

long double s21_cos(double x) {
  x = s21_fmod(x, 2 * S21_PI);
  double sum = 0.0;
  int sign = 1;
  double term = 1.0;

  for (int n = 0; n <= 1000; n += 2) {
    sum += sign * term;
    sign *= -1;
    term *= (x * x) / ((n + 1) * (n + 2));
  }

  return sum;
}