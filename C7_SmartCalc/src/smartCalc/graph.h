#ifndef GRAPH_H
#define GRAPH_H

#include <qcustomplot.h>

#include <QVector>
#include <QWidget>
namespace Ui {
class graph;
}

class graph : public QWidget {
  Q_OBJECT

 public:
  explicit graph(QWidget *parent = nullptr);
  ~graph();
  void paint(const char *line);

 private:
  Ui::graph *ui;
};

#endif  // GRAPH_H
