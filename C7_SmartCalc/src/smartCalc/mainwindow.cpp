#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(expression()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(expression()));

  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_stepen, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui->pushButton_bracketleft, SIGNAL(clicked()), this,
          SLOT(operators()));
  connect(ui->pushButton_bracketright, SIGNAL(clicked()), this,
          SLOT(operators()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(operators()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(AC()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(mod()));

  connect(ui->pushButton_xequals, SIGNAL(clicked()), this, SLOT(X_equals()));

  connect(ui->pushButton_enter, SIGNAL(clicked()), this, SLOT(result()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString text = ui->result->text() + button->text();
  ui->result->setText(text);
}

void MainWindow::expression() {
  QPushButton *button = (QPushButton *)sender();
  QString text = ui->result->text() + button->text() + "(";
  ui->result->setText(text);
}

void MainWindow::operators() {
  QPushButton *button = (QPushButton *)sender();
  QString text = ui->result->text() + button->text();
  ui->result->setText(text);
}
void MainWindow::AC() {
  ui->result->setText("");
  ui->result_X->setText("");
}
void MainWindow::mod() {
  QString text = ui->result->text() + "%";
  ui->result->setText(text);
}

void MainWindow::result() {
  QString line = ui->result->text();
  std::string current_locale_text = line.toStdString();
  const char *line_ptr = current_locale_text.c_str();
  long double result = 0.0;
  int error = SmartCalc(line_ptr, &result);
  if (!error)
    ui->result->setText(QString::number(result, 'g', 10));
  else if (error)
    ui->result->setText("ERROR");
}

void MainWindow::on_pushButton_graph_clicked() {
  QString line = ui->result->text();
  graph *draw = new graph;
  draw->paint(line.toStdString().c_str());
  draw->show();
}
void MainWindow::X_equals() {
  QString line = ui->result->text();
  std::string current_locale_text = line.toStdString();
  const char *line_ptr = current_locale_text.c_str();
  QString line_num = ui->result_X->text();
  std::string current_locale_text_num = line_num.toStdString();
  const char *line_ptr_num = current_locale_text_num.c_str();
  long double x = 0;
  int error = SmartCalc(line_ptr_num, &x);
  if (!error) {
    long double result = 0.0;
    error = SmartCalc_X(line_ptr, &result, x);
    if (!error)
      ui->result->setText(QString::number(result, 'g', 10));
    else
      ui->result->setText("ERROR");
  } else
    ui->result->setText("ERROR");
}

void MainWindow::on_pushButton_CR_clicked() { credit.show(); }
