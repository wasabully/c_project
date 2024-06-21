#include "graph.h"

#include "mainwindow.h"
#include "ui_graph.h"

graph::graph(QWidget* parent) : QWidget(parent), ui(new Ui::graph) {
  ui->setupUi(this);
  setFixedSize(width(), height());
  setAttribute(Qt::WA_DeleteOnClose);
  ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
void graph::paint(const char* str) {
  QVector<double> x, y;
  for (long double i = -1000; i < 1000; i += 0.1) {
    long double result = 0.0;
    SmartCalc_X(str, &result, i);
    x.push_back(i);
    y.push_back(result);
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(-10, 10);
  ui->widget->yAxis->setRange(-2.5, 2.5);
  ui->widget->replot();
}

graph::~graph() { delete ui; }
