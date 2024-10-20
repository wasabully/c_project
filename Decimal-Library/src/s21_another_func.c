#include "s21_decimal.h"
#include "s21_help_func.h"
int s21_floor(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value), scale = get_scale(value), error = 0;
  if (result) {
    s21_truncate(value, result);
    if (sign && scale) {
      set_bit(result, 127, 0);
      s21_decimal one = {{1, 0, 0, 0}};
      error = s21_add(*result, one, result);
      set_sign(result);
    }
  } else {
    error = 1;
  }
  return error;
}
int s21_round(s21_decimal value, s21_decimal *result) {
  int sign = get_sign(value), scale = get_scale(value), error = 0;
  set_bit(&value, 127, 0);
  if (result) {
    int rem = 0;
    s21_truncate(value, result);
    for (int i = 0; i < scale; i++) {
      rem = s21_div_10(&value);
    }
    if (rem >= 5) {
      s21_decimal one = {{1, 0, 0, 0}};
      error = s21_add(*result, one, result);
    }
    if (sign) set_sign(result);
  } else {
    error = 1;
  }
  return error;
}
int s21_truncate(s21_decimal value, s21_decimal *result) {
  int scale = get_scale(value);
  for (; scale > 0; scale--) {
    s21_div_10(&value);
  }
  set_scale(&value, 0);
  *result = value;
  return 0;
}
int s21_negate(s21_decimal value, s21_decimal *result) {
  unsigned int mask = 2147483648;
  *result = value;
  result->bits[3] = value.bits[3] ^ mask;
  return 0;
}