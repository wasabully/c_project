#include "s21_math_test.h"

START_TEST(pow_test1) {
  ck_assert_double_eq_tol(s21_pow(5, 0), pow(5, 0), 0.000001);
}
END_TEST

START_TEST(pow_test2) {
  ck_assert_double_eq_tol(s21_pow(6.6, 1.3), pow(6.6, 1.3), 0.000001);
}
END_TEST

START_TEST(pow_test3) {
  ck_assert_double_eq_tol(s21_pow(1, 1), pow(1, 1), 0.000001);
}
END_TEST

START_TEST(pow_test4) {
  ck_assert_double_eq_tol(s21_pow(1, 1), pow(1, 1), 0.000001);
}
END_TEST

START_TEST(pow_test5) {
  ck_assert_double_eq_tol(s21_pow(2, 32), pow(2, 32), 0.000001);
}
END_TEST

START_TEST(pow_test6) {
  ck_assert_double_eq_tol(s21_pow(1, S21_INF), pow(1, S21_INF), 0.000001);
}
END_TEST

START_TEST(pow_test7) {
  ck_assert_ldouble_eq_tol(pow(10, 1), s21_pow(10, 1), 0.000001);
}
END_TEST

Suite* suite_pow(void) {
  Suite* s = suite_create("s_pow");
  TCase* tc = tcase_create("tc_pow");
  tcase_add_test(tc, pow_test1);
  tcase_add_test(tc, pow_test2);
  tcase_add_test(tc, pow_test3);
  tcase_add_test(tc, pow_test4);
  tcase_add_test(tc, pow_test5);
  tcase_add_test(tc, pow_test6);
  tcase_add_test(tc, pow_test7);
  suite_add_tcase(s, tc);
  return s;
}