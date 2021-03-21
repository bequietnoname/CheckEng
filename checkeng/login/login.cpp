
#include <QTimer>
#include <QDate>
#include "login.h"
#include "ui_login.h"

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}
void LoginDialog::onAccepted() noexcept
{
    ui->m_info->setText({});
    if(onChanged())
        return;
    inherited::accept();
}
bool LoginDialog::onChanged() noexcept
{
    auto const is = ui->m_login->text().isEmpty();
    ui->b_login->setDisabled(is);
    return is;
}
QString LoginDialog::name() const noexcept
{
    return ui->m_login->text();
}
LoginDialog::~LoginDialog()
{
}
