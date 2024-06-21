#include "s21_math_test.h"

START_TEST(asin_test1) {
  ck_assert_double_eq_tol(s21_asin(0.9), asin(0.9), 0.000001);
}
END_TEST

START_TEST(asin_test2) {
  ck_assert_double_eq_tol(s21_asin(0), asin(0), 0.000001);
}
END_TEST

START_TEST(asin_test3) {
  ck_assert_double_eq_tol(s21_asin(-0.5), asin(-0.5), 0.000001);
}
END_TEST

START_TEST(asin_test4) {
  ck_assert_double_eq_tol(s21_asin(1), asin(1), 0.000001);
}
END_TEST

START_TEST(asin_test5) {
  ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 0.000001);
}
END_TEST

START_TEST(asin_test6) {
  ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 0.000001);
}
END_TEST

Suite* suite_asin(void) {
  Suite* s = suite_create("s_asin");
  TCase* tc = tcase_create("tc_asin");
  tcase_add_test(tc, asin_test1);
  tcase_add_test(tc, asin_test2);
  tcase_add_test(tc, asin_test3);
  tcase_add_test(tc, asin_test4);
  tcase_add_test(tc, asin_test5);
  tcase_add_test(tc, asin_test6);
  suite_add_tcase(s, tc);
  return s;
}