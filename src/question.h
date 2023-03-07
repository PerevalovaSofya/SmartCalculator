#ifndef SRC_QUESTION_H_
#define SRC_QUESTION_H_

#include <QWidget>

namespace Ui {
class Question;
}

class Question : public QWidget {
    Q_OBJECT

 public:
    explicit Question(QWidget *parent = nullptr);
    ~Question();
    double variation;

 private slots:
    void on_pushButton_1_clicked();

 private:
    Ui::Question *ui;

 signals:
    void signalQuestion(double);
};

#endif  // SRC_QUESTION_H_
