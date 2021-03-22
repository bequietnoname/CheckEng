#include <QFile>
#include <QDebug>
#include "one_of_three.h"
#include "ui_one_of_three.h"
#include "include/context.h"
#include "dialogs/finish/finish.h"

OneOfThreeWidget::OneOfThreeWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::OneOfThreeWidget)
{
    gt::create(ui, parent);
 //   ui->setupUi(this);
}
OneOfThreeWidget::~OneOfThreeWidget()
{
    delete ui;
}
void OneOfThreeWidget::start(QString const& name)
{
    m_name = name;

    QFile file("tests/1/test1.txt");
    if(!file.open(QIODevice::ReadOnly |QIODevice::Text)) {
        qDebug()<< "don't open file";
        return;
    }
    QString q, a1, a2, a3;
    bool newtask = true;
    int cx = 0;

    while(!file.atEnd()) {
        auto str = file.readLine().trimmed();
        if(str.isEmpty())
            continue;

        if(str[0] != char('-')){
            newtask = true;
            q = str;
            cx = 0;
        }
        else if(str[0] == char('-')) {
            str = str.mid(1);
            if(cx == 0)
                a1 = str;
            else if(cx == 1)
                a2 = str;
            else {
                a3 = str;
                m_tasks.push_back(Task(q, a1, a2 ,a3));
            }
            ++cx;
        }
    }

    m_index = 0;
    m_right = 0;

    nextTask();
}
void OneOfThreeWidget::nextTask()
{
    if(m_index >= m_tasks.size()) {
        FinishDialog dlg(m_name, m_right, m_tasks.size());
        dlg.exec();

        return;
    }
    auto task = m_tasks[m_index];
    ui->l_question->setText(task.question());
    randomize(task.answer1(), task.answer2(), task.answer3());
}
void OneOfThreeWidget::answer(QPushButton* btn)
{
    if(m_index >= m_tasks.size())
        return;

    auto task = m_tasks[m_index];
    if(task.answer1() == btn->text())
        ++m_right;
    ++m_index;
    nextTask();
}
void OneOfThreeWidget::onFirstAnswerClick()
{
    // answer(ui->pb_first);
}
void OneOfThreeWidget::onSecondAnswerClick()
{
    // answer(ui->pb_second);
}
void OneOfThreeWidget::onThirdAnswerClick()
{
   //  answer(ui->pb_third);
}
void OneOfThreeWidget::randomize(QString const& first, QString const& second, QString const& third)
{
     /* QVector<QPushButton*> V{ui->pb_first, ui->pb_second, ui->pb_third};
     int x = rand()%3;
     V[x]->setText(first);
     V.remove(x);
     x = rand()%2;
     V[x]->setText(second);
     V.remove(x);
     V[0]->setText(third); */
}
