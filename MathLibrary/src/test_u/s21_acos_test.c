#include "s21_math_test.h"

START_TEST(acos_test1) {
  ck_assert_double_eq_tol(s21_acos(0.9), acos(0.9), 0.000001);
}
END_TEST

START_TEST(acos_test2) {
  ck_assert_double_eq_tol(s21_acos(0), acos(0), 0.000001);
}
END_TEST

START_TEST(acos_test3) {
  ck_assert_double_eq_tol(s21_acos(-0.5), acos(-0.5), 0.000001);
}
END_TEST

START_TEST(acos_test4) {
  ck_assert_double_eq_tol(s21_acos(1), acos(1), 0.000001);
}
END_TEST

START_TEST(acos_test5) {
  ck_assert_double_eq_tol(s21_acos(-1), acos(-1), 0.000001);
}
END_TEST

Suite* suite_acos(void) {
  Suite* s = suite_create("s_acos");
  TCase* tc = tcase_create("tc_acos");
  tcase_add_test(tc, acos_test1);
  tcase_add_test(tc, acos_test2);
  tcase_add_test(tc, acos_test3);
  tcase_add_test(tc, acos_test4);
  tcase_add_test(tc, acos_test5);
  suite_add_tcase(s, tc);
  return s;
}