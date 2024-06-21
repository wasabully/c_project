#include "s21_math_test.h"

START_TEST(ceil_test1) {
  ck_assert_double_eq_tol(s21_ceil(0.9), ceil(0.9), 0.000001);
}
END_TEST

START_TEST(ceil_test2) {
  ck_assert_double_eq_tol(s21_ceil(0), ceil(0), 0.000001);
}
END_TEST

START_TEST(ceil_test3) {
  ck_assert_double_eq_tol(s21_ceil(-0.5), ceil(-0.5), 0.000001);
}
END_TEST

START_TEST(ceil_test4) {
  ck_assert_double_eq_tol(s21_ceil(-13.2), ceil(-13.2), 0.000001);
}
END_TEST

Suite* suite_ceil(void) {
  Suite* s = suite_create("s_ceil");
  TCase* tc = tcase_create("tc_ceil");
  tcase_add_test(tc, ceil_test1);
  tcase_add_test(tc, ceil_test2);
  tcase_add_test(tc, ceil_test3);
  tcase_add_test(tc, ceil_test4);
  suite_add_tcase(s, tc);
  return s;
}