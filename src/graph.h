#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_
#include <QDialog>
#include <QMessageBox>
#include <QWidget>
#include <cmath>

#include "controller.h"
#include "model.h"
#include "stack.h"

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  Graph(QWidget *parent, QString abc, Controller *controller);
  ~Graph();
  double x_start, x_end, x_step, X, y_start, y_end;
  int N;
  QVector<double> x, y;

 private slots:
  void on_build_graph_clicked();

 private:
  Ui::Graph *ui;
  QString strOut;
  Controller *calc;
};

#endif  // SRC_GRAPH_H_
