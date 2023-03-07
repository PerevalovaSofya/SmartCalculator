#include "graph.h"

#include "ui_graph.h"

Graph::Graph(QWidget *parent, QString str_out, Controller *controller)
    : QDialog(parent), ui(new Ui::Graph), calc(controller) {
  ui->setupUi(this);
  strOut = str_out;
}

Graph::~Graph() { delete ui; }

void Graph::on_build_graph_clicked() {
  x.clear();
  y.clear();
  std::string str = strOut.toLocal8Bit().data();
  std::list<std::string> polish_notation = calc->parser(str);
  std::string error = calc->getError();
  if (error.empty() == 1) {
    x_step = 0.0002;
    x_start = ui->x_start->value();
    x_end = ui->x_end->value();
    y_start = ui->y_start->value();
    y_end = ui->y_end->value();
    if ((x_end - x_start) > 20)
      x_step = (pow((x_end - x_start), 0.5)) * x_step * 5;
    if (x_start >= x_end || y_start >= y_end) {
      error = "Don't buld";
    }
    ui->widget->xAxis->setRange(x_start, x_end);
    ui->widget->yAxis->setRange(y_start, y_end);
    for (X = x_start; X <= x_end && error.empty() == 1; X += x_step) {
      x.push_back(X);
      double result = 0;
      result = calc->calulation(polish_notation, X);
      error = calc->getError();
      if (error.empty() == 1) {
        y.push_back(result);
      }
    }
    if (error.empty() == 1) {
      ui->widget->addGraph();
      ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
      ui->widget->graph(0)->setScatterStyle(
          QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
      ui->widget->graph(0)->setData(x, y);
      ui->widget->replot();
      ui->widget->setInteraction(QCP::iRangeDrag, true);
      ui->widget->setInteraction(QCP::iRangeZoom, true);
      ui->label->setText("The graph is built");
    }
  }
  if (error.empty() == 0) {
    ui->label->setText("Stop! Invalid data!");
  }
}
