#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <creditcalc.h>
#include <graph.h>
#include <locale.h>

#include <QMainWindow>
#include <QMessageBox>
#include <QWindow>
extern "C" {
#include <../s21_calc.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  CreditCalc credit;
 private slots:
  void digits_numbers();
  void expression();
  void operators();
  void AC();
  void result();
  void X_equals();
  void on_pushButton_graph_clicked();
  void on_pushButton_CR_clicked();
  void mod();
};
#endif  // MAINWINDOW_H
