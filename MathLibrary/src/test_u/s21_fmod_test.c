#include "s21_math_test.h"

START_TEST(fmod_test1) {
  ck_assert_double_eq_tol(s21_fmod(5, 5), fmod(5, 5), 0.000001);
}
END_TEST

START_TEST(fmod_test2) {
  ck_assert_double_eq_tol(s21_fmod(6.6, 2.9), fmod(6.6, 2.9), 0.000001);
}
END_TEST

START_TEST(fmod_test3) {
  ck_assert_double_eq_tol(s21_fmod(1.5, 9.6), fmod(1.5, 9.6), 0.000001);
}
END_TEST

START_TEST(fmod_test4) {
  ck_assert_double_eq_tol(s21_fmod(0, 6), fmod(0, 6), 0.000001);
}
END_TEST

START_TEST(fmod_test5) { ck_assert_double_nan(s21_fmod(S21_NAN, 0)); }
END_TEST

START_TEST(fmod_test6) { ck_assert_double_nan(s21_fmod(S21_NINF, 1)); }
END_TEST

START_TEST(fmod_test7) {
  ck_assert_double_eq(s21_fmod(1, S21_INF), fmod(1, S21_INF));
}
END_TEST

Suite* suite_fmod(void) {
  Suite* s = suite_create("s_fmod");
  TCase* tc = tcase_create("tc_fmod");
  tcase_add_test(tc, fmod_test1);
  tcase_add_test(tc, fmod_test2);
  tcase_add_test(tc, fmod_test3);
  tcase_add_test(tc, fmod_test4);
  tcase_add_test(tc, fmod_test5);
  tcase_add_test(tc, fmod_test6);
  tcase_add_test(tc, fmod_test7);
  suite_add_tcase(s, tc);
  return s;
}