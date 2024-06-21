#include "creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);
  connect(ui->pushButton_ANN, SIGNAL(clicked()), this,
          SLOT(on_pushButton_ANN_clicked()));
  connect(ui->pushButton_DIFF, SIGNAL(clicked()), this,
          SLOT(on_pushButton_DIFF_clicked()));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_ANN_clicked() { calc_credit(); }

void CreditCalc::on_pushButton_DIFF_clicked() { calc_credit(); }

void CreditCalc::calc_credit() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QString sum = ui->sum->text();
  QString procent = ui->procent->text();
  QString deadline = ui->deadline->text();

  if (!(sum.isEmpty() || procent.isEmpty() || deadline.isEmpty())) {
    double sum_number = sum.toDouble();
    double procent_number = procent.toDouble();
    double deadline_number = deadline.toDouble();

    double payment = 0;
    double total = 0;
    double over = 0;

    QString mounth_pay;

    if (button == ui->pushButton_DIFF) {
      payment = calculateDifferentialPayment(sum_number, procent_number,
                                             deadline_number);
      mounth_pay = QString("%L1").arg(payment, 0, 'f', 2);
      total =
          calculateTotalPayments(sum_number, procent_number, deadline_number);
    }
    if (button == ui->pushButton_ANN) {
      payment =
          calculateAnnuityPayment(sum_number, procent_number, deadline_number);
      mounth_pay = QString("%L1").arg(payment, 0, 'f', 2);
      total = payment * deadline_number;
    }

    ui->payment->setText(mounth_pay);
    over = total - sum_number;
    ui->total->setText(QString("%L1").arg(total, 0, 'f', 2));
    ui->over->setText(QString("%L1").arg(over, 0, 'f', 2));
  } else {
    QMessageBox::critical(this, "Fail", "Check fields");
  }
}
