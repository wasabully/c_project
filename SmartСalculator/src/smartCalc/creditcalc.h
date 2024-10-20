#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QMessageBox>
#include <QPushButton>
#include <QWidget>
extern "C" {
#include <../s21_calc.h>
}  // Включаем заголовочный файл для функций расчета

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_pushButton_ANN_clicked();
  void on_pushButton_DIFF_clicked();
  void calc_credit();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
