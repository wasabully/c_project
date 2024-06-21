#define S21_PI 3.14159265358979324
#define S21_NPI -3.14159265358979324
#define EXp 2.7182818284590452353602874713527
#define MAX_LONG_DOUBLE 1.79769313486231571e+308
#define S21_ln10 2.30258509299404590109
#define S21_INF 1.0 / 0.0
#define S21_NINF -1.0 / 0.0
#define S21_NAN 0.0 / 0.0
#define S21_EPS 1e-17
#define s21_is_nan(x) (x != x)

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
