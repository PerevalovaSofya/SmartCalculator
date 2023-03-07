#include "calcwindow.h"

#include "graph.h"
#include "question.h"
#include "ui_calcwindow.h"

CalcWindow::CalcWindow(Controller *controller, QWidget *parent)

    : QMainWindow(parent), ui(new Ui::CalcWindow), calc(controller) {
  ui->setupUi(this);
  connect(ui->pushButton_0, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_start, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_end, SIGNAL(clicked()), SLOT(digits_numbers()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), SLOT(digits_funct()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), SLOT(digits_funct()));
}

CalcWindow::~CalcWindow() { delete ui; }

void CalcWindow::on_pushButton_graph_clicked() {
  Graph window(nullptr, ui->result_show->text(), calc);
  window.setModal(true);
  window.exec();
}

void CalcWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void CalcWindow::digits_funct() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text() + button->text() + "(";
  ui->result_show->setText(new_label);
}

void CalcWindow::on_pushButton_ac_clicked() { ui->result_show->setText(""); }

void CalcWindow::on_pushButton_equl_clicked() {
  QString d = ui->result_show->text();
  str = d.toLocal8Bit().data();
  size_t pos = str.find('x');
  if (pos != std::string::npos) {
    question = new Question;
    question->show();
    connect(question, &Question::signalQuestion, this,
            &CalcWindow::slotQuestion);
  } else {
    calculution(0);
  }
}

void CalcWindow::calculution(double a) {
  std::list<std::string> polish_notation = calc->parser(str);
  std::string error = calc->getError();
  if (error.empty() == 1) {
    double result = 0;
    result = calc->calulation(polish_notation, a);
    error = calc->getError();
    if (error.empty() == 1) {
      QString qresult = QString::number(result, 'g', 6);
      ui->result_show->setText(qresult);
    }
  }
  if (error.empty() == 0) {
    QString qerror = QString::fromLocal8Bit(error.c_str());
    ui->result_show->setText(qerror);
  }
}

void CalcWindow::on_pushButton_back_clicked() {
  QString str = ui->result_show->text();
  str = str.left(str.count() - 1);
  ui->result_show->setText(str);
}

void CalcWindow::on_pushButton_pow_clicked() {
  ui->result_show->setText(ui->result_show->text() + "^");
}

void CalcWindow::on_pushButton_mul_clicked() {
  ui->result_show->setText(ui->result_show->text() + "*");
}

void CalcWindow::on_pushButton_div_clicked() {
  ui->result_show->setText(ui->result_show->text() + "/");
}
void CalcWindow::on_pushButton_x_clicked() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label = ui->result_show->text() + button->text();
  ui->result_show->setText(new_label);
}

void CalcWindow::slotQuestion(double a) { calculution(a); }
