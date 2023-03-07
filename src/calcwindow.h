#ifndef SRC_CALCWINDOW_H_
#define SRC_CALCWINDOW_H_

#include <QMainWindow>
#include <QVector>
#include <iostream>
#include <string>

#include "controller.h"
#include "graph.h"
#include "model.h"
#include "question.h"
#include "stack.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcWindow;
}
QT_END_NAMESPACE

class CalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CalcWindow(Controller *controller, QWidget *parent = nullptr);
  ~CalcWindow();

 private:
  Ui::CalcWindow *ui;
  Question *question;
  std::string str;
  Controller *calc;

 private slots:
  void calculution(double a);
  void digits_numbers();
  void digits_funct();
  void on_pushButton_ac_clicked();
  void on_pushButton_equl_clicked();
  void on_pushButton_back_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_mul_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_graph_clicked();
  void on_pushButton_x_clicked();

 public slots:
  void slotQuestion(double a);
};

#endif  // SRC_CALCWINDOW_H_
