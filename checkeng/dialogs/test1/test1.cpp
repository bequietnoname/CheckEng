#include "test1.h"
#include "ui_test1.h"

Test1Dialog::Test1Dialog(QString const& name, int right, int total, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Test1)
{
    ui->setupUi(this);
    ui->m_name->setText(name);
    ui->m_correct->setText(QString::number(right));
    ui->m_total->setText(QString::number(total));
    ui->m_incorrect->setText(QString::number(total-right));
    ui->m_percent->setText(QStringLiteral("%1%").arg(right*100 / total));
}
Test1Dialog::~Test1Dialog()
{
    delete ui;
}
