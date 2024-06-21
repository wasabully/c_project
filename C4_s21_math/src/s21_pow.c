#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 1;
  if (base == 1 && (exp == S21_INF || exp == S21_NINF)) {
    result = 1.0;
  } else if (base == 1 && exp == S21_NAN) {
    result = 1.0;
  } else if (exp == (long int)exp) {
    if (exp >= 0) {
      for (int i = 1; i <= exp; i++) result *= base;
    } else {
      base = 1 / base;
      exp *= -1;
      for (int i = 1; i <= exp; i++) result *= base;
    }
  } else {
    if (base == 0) {
      result = 0;
      if (exp < 0) result = S21_INF;
    } else {
      result = s21_exp(exp * s21_log(base));
    }
  }
  return result;
}