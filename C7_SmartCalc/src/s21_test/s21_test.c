#include "s21_test.h"

START_TEST(Smart_calc) {
  long double result = 0;
  char input_str[1024] = "tan(250)-cos(45)+2^(sin(52))*5";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, tan(250) - cos(45) + pow(2, sin(52)) * 5,
                           1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_2) {
  long double result = 0;
  char input_str[1024] = "acos(-1)*2^2^2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, acos(-1) * pow(2, pow(2, 2)), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_3) {
  long double result = 0;
  char input_str[1024] = "2 / 6 * 5 % 3 + 10 - 9";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, 2.0 / 6.0 * fmod(5, 3) + 10 - 9, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_4) {
  long double result = 0;
  char input_str[1024] = "-5 + cos(10) * sin(1) / tan(1)";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, -5 + cos(10) * sin(1) / tan(1), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_5) {
  long double result = 0;
  char input_str[1024] = "0/1";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, 0, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_6) {
  long double result = 0;
  char input_str[1024] = "5mod3*10/15+6+atan(5)";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, fmod(5, 3) * 10.0 / 15.0 + 6 + atan(5),
                           1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_7) {
  long double result = 0;
  char input_str[1024] = "asin(-1)+2^2+2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, asin(-1) + pow(2, 2) + 2, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_8) {
  long double result = 0;
  char input_str[1024] = "(sqrt(5) + 5) % 3";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, fmod((sqrt(5) + 5), 3), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_9) {
  long double result = 0;
  char input_str[1024] = "2^3^2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, pow(2, pow(3, 2)), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_10) {
  long double result = 0;
  char input_str[1024] = "2 - +3";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, 2 - 3, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_11) {
  long double result = 0;
  char input_str[1024] = "sin(5)^2+cos(5)^2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, pow(sin(5), 2) + pow(cos(5), 2), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_12) {
  long double result = 0;
  char input_str[1024] = "2++2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, 4, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_13) {
  long double result = 0;
  char input_str[1024] = "2+2*2-2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, 2 + 2 * 2 - 2, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_14) {
  long double result = 0;
  char input_str[1024] = "cos(5.25)+sin(2.5)+tan(55.5)";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, cos(5.25) + sin(2.5) + tan(55.5), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_15) {
  long double result = 0;
  char input_str[1024] = "log(5)^4+5/1";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, pow(log10l(5), 4) + 5.0 / 1.0, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_16) {
  long double result = 0;
  char input_str[1024] = "-2mod9 + 3mod4";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, -2 % 9 + 3 % 4, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_17) {
  long double result = 0;
  char input_str[1024] = "(sin(1)+cos(2))*(2^3)+1";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, (sin(1) + cos(2)) * (pow(2, 3)) + 1, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_18) {
  long double result = 0;
  char input_str[1024] = "sqrt(4)+2^2^2+1337.1337/sin(1)";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(
      result, sqrt(4) + pow(2, pow(2, 2)) + 1337.1337 / sin(1), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_19) {
  long double result = 0;
  char input_str[1024] = "((ln(10)*2)+2)/2";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(result, ((log(10) * 2) + 2) / 2.0, 1e-7);
  ck_assert_int_eq(error, 0);
}

START_TEST(Smart_calc_20) {
  long double result = 0;
  char input_str[1024] = "(5mod3+sqrt(5))+sin(10)+(tan(1)+log(1))";
  int error = SmartCalc(input_str, &result);
  ck_assert_ldouble_eq_tol(
      result, (5 % 3 + sqrt(5)) + sin(10) + (tan(1) + log(1)), 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_21) {
  long double result = 0;
  char input_str[1024] = "sin()+1";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_22) {
  long double result = 0;
  char input_str[1024] = "tan(5.4444)+sin";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_23) {
  long double result = 0;
  char input_str[1024] = "1wer+1sdf";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_24) {
  long double result = 0;
  char input_str[1024] = "asig(5)+atin(5)";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_25) {
  long double result = 0;
  char input_str[1024] = "2//2";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_26) {
  long double result = 0;
  char input_str[1024] = "((2+2)";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_27) {
  long double result = 0;
  char input_str[1024] = "4rep+4fgs";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_28) {
  long double result = 0;
  char input_str[1024] = "2/0";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -2);
}
END_TEST

START_TEST(Smart_calc_29) {
  long double result = 0;
  char input_str[1024] = "2 2";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_30) {
  long double result = 0;
  char input_str[1024] = "abvgd+zhgre";
  int error = SmartCalc(input_str, &result);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_31) {
  int error = popValueStack(NULL, NULL);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_32) {
  ValueNode *ValueNode = NULL;
  long double value;
  int error = popValueStack(&ValueNode, &value);
  ck_assert_int_eq(error, -1);
}
END_TEST

// SmartCalc_X
START_TEST(Smart_calc_X1) {
  long double result = 0;
  char input_str[1024] = "+1+x";
  long double x = 5.5;
  int error = SmartCalc_X(input_str, &result, x);
  ck_assert_ldouble_eq_tol(result, 6.5, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_X2) {
  long double result = 0, x = 2;
  char input_str[1024] = "2 x";
  int error = SmartCalc_X(input_str, &result, x);
  ck_assert_int_eq(error, -1);
}
END_TEST

START_TEST(Smart_calc_X3) {
  long double result = 0;
  char input_str[1024] = "sin(x)^2+cos(x)^2";
  long double x = 5;
  int error = SmartCalc_X(input_str, &result, x);
  ck_assert_ldouble_eq_tol(result, 1, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(Smart_calc_X4) {
  long double result = 0;
  char input_str[1024] = "(x+x)*x";
  long double x = 10;
  int error = SmartCalc_X(input_str, &result, x);
  ck_assert_ldouble_eq_tol(result, 200, 1e-7);
  ck_assert_int_eq(error, 0);
}
END_TEST

// CREDIT
START_TEST(creditcalc_1) {
  double result = calculateAnnuityPayment(100000, 5, 12);
  int test_result = fabsl(result - (8560.748179)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_result, 0);
}
END_TEST

START_TEST(creditcalc_2) {
  double result = calculateAnnuityPayment(100000, 12, 5);
  int test_result = fabsl(result - (20604)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_result, 1);
}
END_TEST

START_TEST(creditcalc_3) {
  double result = calculateDifferentialPayment(113410, 24, 7);
  int test_result = fabsl(result - (8333.333333)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_result, 1);
}
END_TEST

START_TEST(creditcalc_4) {
  double result = calculateTotalPayments(100000, 5, 12);
  int test_result = fabsl(result - (102708.333333)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_result, 0);
}
END_TEST

START_TEST(creditcalc_5) {
  double result = calculateTotalPayments(113410, 24, 7);
  int test_result = fabsl(result - (122483)) < 1e-4 ? 0 : 1;
  ck_assert_int_eq(test_result, 1);
}
END_TEST

Suite *test_calculator() {
  Suite *s = suite_create("Smart_calc");
  TCase *o = tcase_create("Smart_calc");
  suite_add_tcase(s, o);
  tcase_add_test(o, Smart_calc);
  tcase_add_test(o, Smart_calc_2);
  tcase_add_test(o, Smart_calc_3);
  tcase_add_test(o, Smart_calc_4);
  tcase_add_test(o, Smart_calc_5);
  tcase_add_test(o, Smart_calc_6);
  tcase_add_test(o, Smart_calc_7);
  tcase_add_test(o, Smart_calc_8);
  tcase_add_test(o, Smart_calc_9);
  tcase_add_test(o, Smart_calc_10);
  tcase_add_test(o, Smart_calc_11);
  tcase_add_test(o, Smart_calc_12);
  tcase_add_test(o, Smart_calc_13);
  tcase_add_test(o, Smart_calc_14);
  tcase_add_test(o, Smart_calc_15);
  tcase_add_test(o, Smart_calc_16);
  tcase_add_test(o, Smart_calc_17);
  tcase_add_test(o, Smart_calc_18);
  tcase_add_test(o, Smart_calc_19);
  tcase_add_test(o, Smart_calc_20);
  tcase_add_test(o, Smart_calc_21);
  tcase_add_test(o, Smart_calc_22);
  tcase_add_test(o, Smart_calc_23);
  tcase_add_test(o, Smart_calc_24);
  tcase_add_test(o, Smart_calc_25);
  tcase_add_test(o, Smart_calc_26);
  tcase_add_test(o, Smart_calc_27);
  tcase_add_test(o, Smart_calc_28);
  tcase_add_test(o, Smart_calc_29);
  tcase_add_test(o, Smart_calc_30);
  tcase_add_test(o, Smart_calc_31);
  tcase_add_test(o, Smart_calc_32);
  tcase_add_test(o, Smart_calc_X1);
  tcase_add_test(o, Smart_calc_X2);
  tcase_add_test(o, Smart_calc_X3);
  tcase_add_test(o, Smart_calc_X4);
  tcase_add_test(o, creditcalc_1);
  tcase_add_test(o, creditcalc_2);
  tcase_add_test(o, creditcalc_3);
  tcase_add_test(o, creditcalc_4);
  tcase_add_test(o, creditcalc_5);
  suite_add_tcase(s, o);
  return s;
}
