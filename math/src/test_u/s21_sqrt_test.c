#include "s21_math_test.h"

START_TEST(sqrt_test1) {
  ck_assert_double_eq_tol(s21_sqrt(5), sqrt(5), 0.000001);
}
END_TEST

START_TEST(sqrt_test2) {
  ck_assert_double_eq_tol(s21_sqrt(6.6), sqrt(6.6), 0.000001);
}
END_TEST

START_TEST(sqrt_test3) {
  ck_assert_double_eq_tol(s21_sqrt(6), sqrt(6), 0.000001);
}
END_TEST

START_TEST(sqrt_test4) {
  ck_assert_double_eq_tol(s21_sqrt(49), sqrt(49), 0.000001);
}
END_TEST

START_TEST(sqrt_test5) { ck_assert_double_infinite(s21_sqrt(S21_INF)); }
END_TEST

Suite* suite_sqrt(void) {
  Suite* s = suite_create("s_sqrt");
  TCase* tc = tcase_create("tc_sqrt");
  tcase_add_test(tc, sqrt_test1);
  tcase_add_test(tc, sqrt_test2);
  tcase_add_test(tc, sqrt_test3);
  tcase_add_test(tc, sqrt_test4);
  tcase_add_test(tc, sqrt_test5);
  suite_add_tcase(s, tc);
  return s;
}