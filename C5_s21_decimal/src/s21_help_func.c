#include "s21_help_func.h"

#include "s21_decimal.h"

int s21_truncate_big(s21_big_decimal value, s21_big_decimal* result) {
  int scale = get_big_scale(value);
  for (; scale > 0; scale--) {
    s21_div_big_10(&value);
  }
  set_big_scale(&value, 0);
  *result = value;
  return 0;
}
int s21_round_bank(s21_big_decimal value, s21_big_decimal* result) {
  big_decimal_zeroing(result);
  int scale = get_big_scale(value);
  s21_big_decimal value_cpy = value;
  s21_truncate_big(value, &value_cpy);
  int bit = get_big_bit(value_cpy, 0);
  for (; scale > 0 &&
         (value.bits[3] || value.bits[4] || value.bits[5] || scale > 28);
       scale--) {
    s21_div_big_10(&value);
  }
  s21_big_decimal one = {{1, 0, 0, 0, 0, 0, 0}};
  if (!bit) {
    s21_add_big(value, one, &value);
  }
  *result = value;
  set_big_scale(result, scale);
  return 0;
}
int s21_add_big(s21_big_decimal value_1, s21_big_decimal value_2,
                s21_big_decimal* result) {
  int error = 0, index = 0, count_bit = 0;
  for (; index <= 191; ++index) {
    int count_1 = get_big_bit(value_1, index);
    int count_2 = get_big_bit(value_2, index);
    if (count_1 && count_2) {
      count_bit = bits_all_one(result, index, count_bit);
    }
    if ((count_1 == 0 && count_2) || (count_1 && count_2 == 0)) {
      count_bit = bits_diff(result, index, count_bit);
    }
    if (count_2 == 0 && count_1 == 0) {
      count_bit = bits_all_zero(result, index, count_bit);
    }
  }
  if (count_bit && index == 192) {
    error = 1;
    count_bit = 0;
  }
  if (count_bit) {
    bits_all_one(result, index, count_bit);
  }
  set_big_scale(result, get_big_scale(value_1));
  return error;
}
void s21_sub_big(s21_big_decimal value_1, s21_big_decimal value_2,
                 s21_big_decimal* result) {
  int index = 0, scale = get_big_scale(value_1);
  for (; index <= 191; ++index) {
    int count_1 = get_big_bit(value_1, index);
    int count_2 = get_big_bit(value_2, index);
    if (count_1 && count_2) {
      set_big_bit(result, index, 0);
    }
    if (count_1 == 0 && count_2) {
      int i = index, count = 0;
      for (; i <= 191 && !count; i++) {
        if (get_big_bit(value_1, i)) {
          count = 1;
          set_big_bit(result, index, 1);
          set_big_bit(&value_1, i, 0);
          for (int j = i - 1; j > index; j--) {
            set_big_bit(&value_1, j, 1);
          }
        }
      }
      set_big_bit(result, index, 1);
    }
    if (count_1 && count_2 == 0) {
      set_big_bit(result, index, 1);
    }
    if (count_1 == 0 && count_2 == 0) {
      set_big_bit(result, index, 0);
    }
  }
  set_big_scale(result, scale);
}
int s21_mul_big(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                s21_big_decimal* big_result) {
  s21_big_decimal big_value_2_cpy;
  int error = 0;
  for (int i = 0; i < 192; ++i) {
    if (get_big_bit(big_value_1, i)) {
      big_value_2_cpy = big_value_2;
      for (int j = 0; j < i && !error; j++) {
        error = big_decimal_shift_left(&big_value_2_cpy);
      }
      s21_add_big(*big_result, big_value_2_cpy, big_result);
    }
  }
  return error;
}
int bits_all_one(s21_big_decimal* bits, int index, int count_bit) {
  if (count_bit == 0) {
    set_big_bit(bits, index, 0);
    count_bit = 1;
  } else {
    set_big_bit(bits, index, 1);
  }
  return count_bit;
}
int bits_diff(s21_big_decimal* bits, int index, int count_bit) {
  if (count_bit == 0) {
    set_big_bit(bits, index, 1);
  } else {
    set_big_bit(bits, index, 0);
  }
  return count_bit;
}
int bits_all_zero(s21_big_decimal* bits, int index, int count_bit) {
  if (count_bit == 0) {
    set_big_bit(bits, index, 0);
  } else {
    set_big_bit(bits, index, 1);
  }
  return 0;
}
void s21_normalization(s21_big_decimal* value_1, s21_big_decimal* value_2) {
  int scale_1 = get_big_scale(*value_1);
  int scale_2 = get_big_scale(*value_2);
  int sign_1 = get_big_sign(*value_1);
  int sign_2 = get_big_sign(*value_2);
  if (scale_1 > 28) {
    int diff_1 = scale_1 - 28;
    for (int i = 0; i < diff_1; i++) {
      s21_div_big_10(value_1);
    }
    scale_1 = 28;
    set_big_scale(value_1, 28);
  }
  if (scale_2 > 28) {
    int diff_2 = scale_2 - 28;
    for (int i = 0; i < diff_2; i++) {
      s21_div_big_10(value_2);
    }
    scale_2 = 28;
    set_big_scale(value_2, 28);
  }

  if (scale_1 > scale_2) {
    int diff = scale_1 - scale_2;
    set_big_scale(value_2, scale_1);
    for (int i = 0; i < diff; i++) {
      s21_mul_big_10(value_2);
    }
  } else {
    int diff = scale_2 - scale_1;
    set_big_scale(value_1, scale_2);
    for (int i = 0; i < diff; i++) {
      s21_mul_big_10(value_1);
    }
  }
  if (sign_1) set_big_sign(value_1);
  if (sign_2) set_big_sign(value_2);
}
int s21_mul_big_10(s21_big_decimal* result) {
  s21_big_decimal res_cpy;
  res_cpy = *result;
  int error = 0;
  result->bits[0] = 0b0;
  result->bits[1] = 0b0;
  result->bits[2] = 0b0;
  result->bits[3] = 0b0;
  result->bits[4] = 0b0;
  result->bits[5] = 0b0;
  for (int i = 0; i < 192; ++i) {
    if (get_big_bit(res_cpy, i)) {
      s21_big_decimal mask = {{10, 0, 0, 0, 0, 0, res_cpy.bits[6]}};
      for (int j = 0; j < i; j++) {
        big_decimal_shift_left(&mask);
      }
      error = s21_add_big(*result, mask, result);
      if (error) i = 192;
    }
  }
  return error;
}
int s21_div_10(s21_decimal* result) {
  int remainder = 0;
  for (int i = 95; i >= 0; --i) {
    int bit = get_bit(*result, i);
    int res = (bit + remainder * 2) / 10;
    remainder = (bit + remainder * 2) % 10;
    set_bit(result, i, res);
  }
  return remainder;
}
int s21_div_big_10(s21_big_decimal* result) {
  int remainder = 0;
  for (int i = 191; i >= 0; --i) {
    int bit = get_big_bit(*result, i);
    int res = (bit + remainder * 2) / 10;
    remainder = (bit + remainder * 2) % 10;
    set_big_bit(result, i, res);
  }
  return remainder;
}
int s21_all_zero(s21_decimal value) {
  int zero = 0;
  for (int i = 0; i < 3; ++i) {
    if (value.bits[i] == 0) zero++;
  }
  return zero == 3 ? 1 : 0;
}
int s21_all_big_zero(s21_big_decimal value) {
  int zero = 0;
  for (int i = 0; i < 6; ++i) {
    if (value.bits[i] == 0) zero++;
  }
  return zero == 6 ? 1 : 0;
}
void decimal_zeroing(s21_decimal* value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
}
void big_decimal_zeroing(s21_big_decimal* value) {
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
  value->bits[3] = 0;
  value->bits[4] = 0;
  value->bits[5] = 0;
  value->bits[6] = 0;
}
int big_decimal_shift_left(s21_big_decimal* value) {
  int bit_31 = get_big_bit(*value, 31);
  int bit_63 = get_big_bit(*value, 63);
  int bit_95 = get_big_bit(*value, 95);
  int bit_127 = get_big_bit(*value, 127);
  int bit_159 = get_big_bit(*value, 159);
  int bit_191 = get_big_bit(*value, 191);
  value->bits[0] = value->bits[0] << 1;
  value->bits[1] = value->bits[1] << 1;
  value->bits[2] = value->bits[2] << 1;
  value->bits[3] = value->bits[3] << 1;
  value->bits[4] = value->bits[4] << 1;
  value->bits[5] = value->bits[5] << 1;
  if (bit_31) set_big_bit(value, 32, 1);
  if (bit_63) set_big_bit(value, 64, 1);
  if (bit_95) set_big_bit(value, 96, 1);
  if (bit_127) set_big_bit(value, 128, 1);
  if (bit_159) set_big_bit(value, 160, 1);
  return bit_191;
}
void big_decimal_shift_right(s21_big_decimal* value) {
  int bit_32 = get_big_bit(*value, 32);
  int bit_64 = get_big_bit(*value, 64);
  int bit_96 = get_big_bit(*value, 96);
  int bit_128 = get_big_bit(*value, 128);
  int bit_159 = get_big_bit(*value, 159);
  value->bits[0] = value->bits[0] >> 1;
  value->bits[1] = value->bits[1] >> 1;
  value->bits[2] = value->bits[2] >> 1;
  value->bits[3] = value->bits[3] >> 1;
  value->bits[4] = value->bits[4] >> 1;
  value->bits[5] = value->bits[5] >> 1;
  if (bit_32) set_big_bit(value, 31, 1);
  if (bit_64) set_big_bit(value, 63, 1);
  if (bit_96) set_big_bit(value, 95, 1);
  if (bit_128) set_big_bit(value, 128, 1);
  if (bit_159) set_big_bit(value, 159, 1);
}
void decimal_to_big_decimal(s21_decimal small, s21_big_decimal* big) {
  big->bits[0] = small.bits[0];
  big->bits[1] = small.bits[1];
  big->bits[2] = small.bits[2];
  big->bits[3] = 0;
  big->bits[4] = 0;
  big->bits[5] = 0;
  big->bits[6] = small.bits[3];
}
int big_decimal_to_decimal(s21_big_decimal big, s21_decimal* small) {
  int error = 0;
  int sign = get_big_sign(big);
  int scale = get_big_scale(big);
  if (big.bits[3] || big.bits[4] || big.bits[5] || scale > 28) {
    s21_round_bank(big, &big);
  }
  small->bits[0] = big.bits[0];
  small->bits[1] = big.bits[1];
  small->bits[2] = big.bits[2];
  small->bits[3] = big.bits[6];
  if (big.bits[3] || big.bits[4] || big.bits[5]) {
    error = 1;
    decimal_zeroing(small);
  }
  if (sign && error) {
    error += 1;
  }
  return error;
}
int s21_big_is_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2) {
  int mean;
  if (s21_big_is_less(value_1, value_2) || s21_big_is_equal(value_1, value_2))
    mean = 1;
  else
    mean = 0;
  return mean;
}
int s21_big_is_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  int mean = 0;
  int sign_1 = get_big_sign(value_1);
  int sign_2 = get_big_sign(value_2);
  if (!(s21_all_big_zero(value_1) && s21_all_big_zero(value_2))) {
    s21_normalization(&value_1, &value_2);
    if (sign_1 && sign_2 == 0) mean = 1;
    if (sign_1 && sign_2) {
      set_big_bit(&value_1, 223, 0);
      set_big_bit(&value_2, 223, 0);
      mean = s21_big_is_less(value_2, value_1);
    }
    if (sign_1 == 0 && sign_2 == 0) {
      for (int i = 191; 0 <= i; i--) {
        int bit_1 = get_big_bit(value_1, i);
        int bit_2 = get_big_bit(value_2, i);
        if (bit_1 == 0 && bit_2) {
          mean = 1;
          i = 0;
        }
        if (bit_1 && bit_2 == 0) {
          mean = 0;
          i = 0;
        }
      }
    }
  }
  return mean;
}
int s21_big_is_equal(s21_big_decimal big_value_1, s21_big_decimal big_value_2) {
  int mean = 0;
  if (s21_all_big_zero(big_value_1) && s21_all_big_zero(big_value_2)) {
    mean = 1;
  }
  s21_normalization(&big_value_1, &big_value_2);
  if (big_value_1.bits[0] == big_value_2.bits[0] &&
      big_value_1.bits[1] == big_value_2.bits[1] &&
      big_value_1.bits[2] == big_value_2.bits[2] &&
      big_value_1.bits[3] == big_value_2.bits[3] &&
      big_value_1.bits[4] == big_value_2.bits[4] &&
      big_value_1.bits[5] == big_value_2.bits[5] &&
      get_big_sign(big_value_1) == get_big_sign(big_value_2)) {
    mean = 1;
  }
  return mean;
}
int get_scale(s21_decimal value) {
  int mask = 127 << 16;
  int scale = (value.bits[3] & mask) >> 16;
  return scale;
}
void set_scale(s21_decimal* value, int scale) {
  int sign = get_sign(*value);
  value->bits[3] = 0;
  int mask = scale << 16;
  value->bits[3] = value->bits[3] | mask;
  if (sign) set_sign(value);
}
int get_big_scale(s21_big_decimal value) {
  int mask = 255 << 16;
  int scale = (value.bits[6] & mask) >> 16;
  return scale;
}
void set_big_scale(s21_big_decimal* value, int scale) {
  int sign = get_big_sign(*value);
  value->bits[6] = 0;
  int mask = scale << 16;
  value->bits[6] = value->bits[6] | mask;
  if (sign) set_big_sign(value);
}
int get_bit(s21_decimal value, int index) {
  int bit_compare = 0b1 << index % 32;
  bit_compare = value.bits[index / 32] & bit_compare;
  return bit_compare ? 1 : 0;
}
int get_big_bit(s21_big_decimal value, int index) {
  int bit_compare = 0b1 << index % 32;
  bit_compare = value.bits[index / 32] & bit_compare;
  return bit_compare ? 1 : 0;
}
void set_bit(s21_decimal* value, int index, int bit) {
  int mask = 0b1 << index % 32;
  if (bit)
    value->bits[index / 32] |= mask;
  else
    value->bits[index / 32] &= ~mask;
}
void set_big_bit(s21_big_decimal* value, int index, int bit) {
  unsigned int mask = 0b1 << index % 32;
  if (bit)
    value->bits[index / 32] |= mask;
  else
    value->bits[index / 32] &= ~mask;
}
int get_sign(s21_decimal value) {
  int sign = value.bits[3] & 2147483648;
  return sign ? 1 : 0;
}
void set_sign(s21_decimal* value) {
  value->bits[3] = value->bits[3] | 2147483648;
}
int get_big_sign(s21_big_decimal value) {
  int sign = value.bits[6] & 2147483648;
  return sign ? 1 : 0;
}
void set_big_sign(s21_big_decimal* value) {
  value->bits[6] = value->bits[6] | 2147483648;
}
