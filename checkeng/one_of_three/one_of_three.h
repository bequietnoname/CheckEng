#pragma once
#include <QWidget>
#include "task.h"
#include <QPushButton>

namespace Ui {
    class OneOfThree;
}

class OneOfThree: public QWidget
{
    Q_OBJECT

public:
   using tasts_t = QList<Task>;

public:
    explicit OneOfThree(QWidget *parent = nullptr);
    ~OneOfThree();

private:
   void answer(QPushButton* btn);
   void nextTask();
   void randomize(QString const& first, QString const& second, QString const& third);

private:
    void onFirstAnswerClick();
    void onSecondAnswerClick();
    void onThirdAnswerClick();

private:
   Ui::OneOfThree* ui = nullptr;
   tasts_t m_tasks;
   int m_index;
   int m_right = 0;
};

