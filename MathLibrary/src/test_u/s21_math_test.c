#include "s21_math_test.h"

void run_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;
  run_test(suite_abs(), &fail);
  run_test(suite_acos(), &fail);
  run_test(suite_asin(), &fail);
  run_test(suite_atan(), &fail);
  run_test(suite_ceil(), &fail);
  run_test(suite_cos(), &fail);
  run_test(suite_exp(), &fail);
  run_test(suite_fabs(), &fail);
  run_test(suite_floor(), &fail);
  run_test(suite_fmod(), &fail);
  run_test(suite_log(), &fail);
  run_test(suite_pow(), &fail);
  run_test(suite_sin(), &fail);
  run_test(suite_sqrt(), &fail);
  run_test(suite_tan(), &fail);
  return (fail == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}