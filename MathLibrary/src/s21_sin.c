#include "s21_math.h"

long double s21_sin(double x) {
  x = s21_fmod(x, 2 * S21_PI);
  double sum = 0.0;
  double term = x;
  int sign = 1;
  for (int n = 1; n <= 100; n += 2) {
    sum += sign * term;
    sign *= -1;
    term *= (x * x) / ((n + 1) * (n + 2));
  }
  return sum;
}