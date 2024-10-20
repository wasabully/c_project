#include "s21_math.h"

long double s21_log(double x) {
  long double en = x;
  long long int ex = 0;
  double resu = 0;
  double comp;
  if (x == 0) {
    resu = -S21_INF;
  } else if (s21_is_nan(x) || x < 0) {
    resu = S21_NAN;
  } else if (x == S21_INF) {
    resu = S21_INF;
  } else {
    while (en >= EXp) {
      en /= EXp;
      ex++;
    }
    for (int i = 0; i < 1000; i++) {
      comp = resu;
      resu = comp + 2 * (en - s21_exp(comp)) / (en + s21_exp(comp));
    }
  }
  return resu + ex;
}