#include "s21_math_test.h"

START_TEST(fabs_test1) {
  ck_assert_double_eq_tol(s21_fabs(0.9), fabs(0.9), 0.000001);
}
END_TEST

START_TEST(fabs_test2) {
  ck_assert_double_eq_tol(s21_fabs(1.5), fabs(1.5), 0.000001);
}
END_TEST

START_TEST(fabs_test3) {
  ck_assert_double_eq_tol(s21_fabs(-0.5), fabs(-0.5), 0.000001);
}
END_TEST

START_TEST(fabs_test4) { ck_assert_double_infinite(s21_fabs(S21_INF)); }
END_TEST

START_TEST(fabs_test5) {
  ck_assert_double_eq_tol(s21_fabs(-13.2), fabs(-13.2), 0.000001);
}
END_TEST

Suite* suite_fabs(void) {
  Suite* s = suite_create("s_fabs");
  TCase* tc = tcase_create("tc_fabs");
  tcase_add_test(tc, fabs_test1);
  tcase_add_test(tc, fabs_test2);
  tcase_add_test(tc, fabs_test3);
  tcase_add_test(tc, fabs_test4);
  tcase_add_test(tc, fabs_test5);
  suite_add_tcase(s, tc);
  return s;
}