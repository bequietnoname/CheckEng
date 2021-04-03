#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QVBoxLayout>
#include "main_window.h"
#include "ui_main_window.h"
#include "dialogs/about/about.h"
#include <QDirIterator>
#include <QDebug>
#include <QToolButton>
#include <QInputDialog>
#include <QMessageBox>
#include "include/program.h"
#include "dialogs/add_tasks/add_tasks.h"
#include "include/context.h"
#include "dialogs/test1/test1.h"
#include "login/login.h"
#include "dialogs/test2/test2.h"
#include "dialogs/add_tasks2/add_tasks2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadFiles();
    load();
}
MainWindow::~MainWindow()
{
    save();
    delete ui;
}
void MainWindow::onAboutClick()
{
   AboutDialog dlg;
   dlg.exec();
}
void MainWindow::setName(QString const& name) noexcept
{
    m_name=name;
}
void MainWindow::onStart()
{

}
void MainWindow::save() noexcept
{
    auto const& group = QStringLiteral("dialogs/main/");
    QSettings settings;
    settings.beginGroup(group);
    settings.setValue(QStringLiteral("state"), saveState());
    settings.setValue(QStringLiteral("geometry"), saveGeometry());
    settings.endGroup();
}
void MainWindow::load() noexcept
{
    auto const& group = QStringLiteral("dialogs/main/");
    QSettings settings;
    settings.beginGroup(group);
    restoreState(settings.value(QStringLiteral("state")).toByteArray());
    restoreGeometry(settings.value(QStringLiteral("geometry")).toByteArray());
    settings.endGroup();
}
void MainWindow::onAddNewTasksClicked() noexcept
{
    AddTasksDialog dlg;
    dlg.exec();

    loadFiles();
}
void MainWindow::loadFiles() noexcept
{
    gt::removeChildren(ui->w_tasks);
    auto lay = new QVBoxLayout(ui->w_tasks);
    loadTasks1(lay);
    loadTasks2(lay);
}
void MainWindow::loadTasks1(QVBoxLayout* lay) noexcept
{
    QDirIterator it(program::paths::test1(), {}, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    int cx = 1;
    while (it.hasNext()) {
        auto const& name = it.next();
        auto const& filename = QFileInfo(name).fileName()[0] != QChar('{')
            ? QFileInfo(name).fileName()
            : GT_STR("Text Task %1").arg(cx++);
        auto w = new QWidget();
        auto v = new QHBoxLayout(w);
        auto btn = new QPushButton(filename);
        QObject::connect(btn, &QToolButton::clicked, [name] () {
            LoginDialog login;
            if(login.exec() != LoginDialog::Accepted)
                return;

            Test1Dialog dlg(name, login.name());
            dlg.exec();
        });
        v->addWidget(btn);

        auto btn1 = new QToolButton();
        btn1->setText(GT_STR("Edit"));
        QObject::connect(btn1, &QToolButton::clicked, [cx, name, this] () {
            bool ok;
            auto const& text = QInputDialog::getText(nullptr, program::productName(),
                                                      tr("Enter a new name:"), QLineEdit::Normal,
                                                      GT_STR("Text Task %1").arg(cx), &ok);

            if (ok && !text.isEmpty()) {
                QFile::rename(name, GT_STR("%1/%2").arg(QFileInfo(name).absolutePath()).arg(text));
                this->loadFiles();
            }
        });
        v->addWidget(btn1);

        auto btn2 = new QToolButton();
        btn2->setText(GT_STR("Delete"));
        QObject::connect(btn2, &QToolButton::clicked, [name, this] () {
            int ret = QMessageBox::information(nullptr, program::productName(),
                                           tr("Do you really want to delete test?"),
                                            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if (ret == QMessageBox::Yes) {
                QFile::remove(name);
                this->loadFiles();
            }
        });
        v->addWidget(btn2);
        lay->addWidget(w);
    }
}
void MainWindow::loadTasks2(QVBoxLayout* lay) noexcept
{
    QDirIterator it(program::paths::test2(), {}, QDir::AllDirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

    int cx = 1;
    while (it.hasNext()) {
        auto const& name = it.next();
        auto const& filename = QFileInfo(name).fileName()[0] != QChar('{')
            ? QFileInfo(name).fileName()
            : GT_STR("Audio Task %1").arg(cx++);
        auto w = new QWidget();
        auto v = new QHBoxLayout(w);
        auto btn = new QPushButton(filename);
        QObject::connect(btn, &QToolButton::clicked, [name] () {
            LoginDialog login;
            if(login.exec() != LoginDialog::Accepted)
                return;

            Test2Dialog dlg(name, login.name());
            dlg.exec();
        });
        v->addWidget(btn);

        auto btn1 = new QToolButton();
        btn1->setText(GT_STR("Edit"));
        QObject::connect(btn1, &QToolButton::clicked, [cx, name, this] () {
            bool ok;
            auto const& text = QInputDialog::getText(nullptr, program::productName(),
                                                      tr("Enter a new name:"), QLineEdit::Normal,
                                                      GT_STR("Audio Task %1").arg(cx), &ok);
            if (ok && !text.isEmpty()) {
                QDir().rename(name, GT_STR("%1/%2").arg(QFileInfo(name).absolutePath()).arg(text));
                this->loadFiles();
            }
        });
        v->addWidget(btn1);

        auto btn2 = new QToolButton();
        btn2->setText(GT_STR("Delete"));
        QObject::connect(btn2, &QToolButton::clicked, [name, this] () {
            int ret = QMessageBox::information(nullptr, program::productName(),
                                           tr("Do you really want to delete test?"),
                                            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if (ret == QMessageBox::Yes) {
                QDir(name).removeRecursively();
                this->loadFiles();
            }
        });
        v->addWidget(btn2);
        lay->addWidget(w);
    }
}
void MainWindow::onAddNewAudioClicked() noexcept
{
    AddTasks2Dialog dlg;
    dlg.exec();

    loadFiles();
}
