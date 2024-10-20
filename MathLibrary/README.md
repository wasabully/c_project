# s21_math.h

Реализация собственной версии математической библиотеки math на языке C.

### Реализованный функционал:
| N   | Function                                   | Description                                                        |
| --- | ------------------------------------------ | ------------------------------------------------------------------ |
| 1   | `int abs(int x)`                           | вычисляет абсолютное значение целого числа                         |
| 2   | `long double acos(double x)`               | вычисляет арккосинус                                               |
| 3   | `long double asin(double x)`               | вычисляет арксинус                                                 |
| 4   | `long double atan(double x)`               | вычисляет арктангенс                                               |
| 5   | `long double ceil(double x)`               | возвращает ближайшее целое число, не меньшее заданного значения    |
| 6   | `long double cos(double x)`                | вычисляет косинус                                                  |
| 7   | `long double exp(double x)`                | возвращает значение e, возведенное в заданную степень              |
| 8   | `long double fabs(double x)`               | вычисляет абсолютное значение числа с плавающей точкой             |
| 9   | `long double floor(double x)`              | возвращает ближайшее целое число, не превышающее заданное значение |
| 10  | `long double fmod(double x, double y)`     | остаток операции деления с плавающей точкой                        |
| 11  | `long double log(double x)`                | вычисляет натуральный логарифм                                     |
| 12  | `long double pow(double base, double exp)` | возводит число в заданную степень                                  |
| 13  | `long double sin(double x)`                | вычисляет синус                                                    |
| 14  | `long double sqrt(double x)`               | вычисляет квадратный корень                                        |
| 15  | `long double tan(double x)`                | вычисляет тангенс                                                  |


### Запуск программы:
Цель all компилирует и архивирует библиотеку s21_math.a.

Цель test собирает и запускает тесты, используя собранную библиотеку.

Цель clean удаляет временные файлы и папки, созданные в процессе сборки и тестирования.

Цель gcov_report генерирует отчет о покрытии кода тестами с использованием gcov и lcov.

Цель valgrind проверяет проект на утечки памяти и другие проблемы с помощью инструмента valgrind.

Команды make используются для запуска указанных целей: all, clean, test, valgrind и gcov_report.

## Участники

| <center> Участник команды </center>
|--------------------------------------------|
| [<img src="src/images/wasabully.jpeg" width="300" height="500">](https://github.com/wasabully)<br /><center>bessacoc</center> |
| [<img src="src/images/atlasiro.jpeg" width="400" height="400">](https://github.com/atlasir0)<br /><center>atlasiro</center> |
| [<img src="src/images/renaultd.jpeg" width="300" height="400">](https://github.com/Momzh228)<br /><center>renaultd</center> |

