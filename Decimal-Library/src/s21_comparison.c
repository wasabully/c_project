#include "s21_decimal.h"
#include "s21_help_func.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0}, big_value_2 = {0};
  decimal_to_big_decimal(value_1, &big_value_1);
  decimal_to_big_decimal(value_2, &big_value_2);
  int mean = s21_big_is_less(big_value_1, big_value_2);
  return mean;
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int mean;
  if (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2))
    mean = 1;
  else
    mean = 0;
  return mean;
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int mean;
  if (s21_is_less(value_2, value_1))
    mean = 1;
  else
    mean = 0;
  return mean;
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int mean;
  if (s21_is_less(value_2, value_1) || s21_is_equal(value_1, value_2))
    mean = 1;
  else
    mean = 0;
  return mean;
}
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_big_decimal big_value_1 = {0}, big_value_2 = {0};
  decimal_to_big_decimal(value_1, &big_value_1);
  decimal_to_big_decimal(value_2, &big_value_2);
  int mean = s21_big_is_equal(big_value_1, big_value_2);
  return mean;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return (!s21_is_equal(value_1, value_2));
}
