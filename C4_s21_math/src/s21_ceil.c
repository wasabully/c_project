#include "s21_math.h"

long double s21_ceil(double x) {
  long double result = (long long int)x;
  if (s21_is_nan(x)) {
    result = x;
  } else {
    if (result < x) {
      result++;
    }
  }
  return result;
}