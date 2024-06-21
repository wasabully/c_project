#ifndef S21_HELP_DECIMAL_H
#define S21_HELP_DECIMAL_H
#include <math.h>
#include <stdio.h>

#include "s21_decimal.h"

typedef struct {
  unsigned int bits[7];
} s21_big_decimal;

int s21_round_bank(s21_big_decimal value, s21_big_decimal *result);
int s21_mul_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);
int bits_all_one(s21_big_decimal *bits, int index, int count_bit);
int bits_diff(s21_big_decimal *bits, int index, int count_bit);
int bits_all_zero(s21_big_decimal *bits, int index, int count_bit);
void s21_normalization(s21_big_decimal *value_1, s21_big_decimal *value_2);
int s21_big_is_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2);
int s21_mul_big_10(s21_big_decimal *result);
int s21_div_10(s21_decimal *result);
int s21_div_big_10(s21_big_decimal *result);
int s21_all_zero(s21_decimal value);
int big_decimal_shift_left(s21_big_decimal *value);
void big_decimal_shift_right(s21_big_decimal *value);
void save_bit(s21_decimal *value, int index);
int s21_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal *result);
void s21_sub_big(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal *result);
int s21_big_is_less(s21_big_decimal value_1, s21_big_decimal value_2);
void decimal_to_big_decimal(s21_decimal small, s21_big_decimal *big);
int big_decimal_to_decimal(s21_big_decimal big, s21_decimal *small);
int s21_big_is_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);
void decimal_zeroing(s21_decimal *value);
void big_decimal_zeroing(s21_big_decimal *value);
int s21_all_big_zero(s21_big_decimal value);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
int get_big_scale(s21_big_decimal value);
void set_big_scale(s21_big_decimal *value, int scale);
int get_bit(s21_decimal value, int index);
void set_bit(s21_decimal *value, int index, int bit);
int get_big_bit(s21_big_decimal value, int index);
void set_big_bit(s21_big_decimal *value, int index, int bit);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value);
int get_big_sign(s21_big_decimal value);
void set_big_sign(s21_big_decimal *value);

#endif
