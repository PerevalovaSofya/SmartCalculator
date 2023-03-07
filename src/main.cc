#include <QApplication>

#include "calcwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Model model;
  Controller calc(&model);
  CalcWindow w(&calc);
  w.show();
  return a.exec();
}
