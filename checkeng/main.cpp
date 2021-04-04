#include <cstdlib>
#include <QApplication>
#include <QDir>
#include <ctime>
#include "include/program.h"
#include "main_window.h"

#include "login/login.h"
#include "dialogs/add_tasks/add_tasks.h"
#include "dialogs/choose/choose.h"
#include "include/app.h"

inline void addStyle() noexcept {
    QFile styleF(QStringLiteral(":/css/style.css"));
    styleF.open(QFile::ReadOnly);
    qApp->setStyleSheet(QString::fromStdString(styleF.readAll().toStdString()));
}
void init()
{
    QDir dir{program::paths::test1()};
    if(!dir.exists())
        dir.mkpath(program::paths::test1());

    dir.setPath(program::paths::test2());
    if(!dir.exists())
        dir.mkpath(program::paths::test2());
}
int main(int argc, char *argv[])
{

    App a(argc, argv);
    init();
    addStyle();

    MainWindow w;
    w.show();
    return a.exec();
}
