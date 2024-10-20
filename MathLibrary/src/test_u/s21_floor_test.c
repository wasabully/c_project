#include "s21_math_test.h"

START_TEST(floor_test1) {
  ck_assert_double_eq_tol(s21_floor(5), floor(5), 0.000001);
}
END_TEST

START_TEST(floor_test2) { ck_assert_ldouble_nan(s21_floor(S21_NAN)); }
END_TEST

START_TEST(floor_test3) {
  ck_assert_double_eq_tol(s21_floor(8.5), floor(8.5), 0.000001);
}
END_TEST

START_TEST(floor_test4) {
  ck_assert_double_eq_tol(s21_floor(-1.3), floor(-1.3), 0.000001);
}
END_TEST

START_TEST(floor_test5) { ck_assert_double_infinite(s21_floor(S21_INF)); }
END_TEST

START_TEST(floor_test6) { ck_assert_double_infinite(s21_floor(S21_NINF)); }
END_TEST

Suite* suite_floor(void) {
  Suite* s = suite_create("s_floor");
  TCase* tc = tcase_create("tc_floor");
  tcase_add_test(tc, floor_test1);
  tcase_add_test(tc, floor_test2);
  tcase_add_test(tc, floor_test3);
  tcase_add_test(tc, floor_test4);
  tcase_add_test(tc, floor_test5);
  tcase_add_test(tc, floor_test6);
  suite_add_tcase(s, tc);
  return s;
}