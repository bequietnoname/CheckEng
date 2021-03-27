#pragma once
#include "choose_pch.h"
#include "choose_global.h"
#include <QVBoxLayout>

namespace Ui {
    class Choose;
}

class CHOOSE_DIALOG_SHARED_EXPORT ChooseDialog final: public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ChooseDialog)

 public:
    using class_name = ChooseDialog;
    using inherited  = QDialog;

 public:
    explicit ChooseDialog(QWidget* parent = nullptr);
    ~ChooseDialog() override;

 private slots:
    void onAddNewTasksClicked() noexcept;
    void onAddNewAudioClicked() noexcept;
    void loadFiles() noexcept;
    void loadTasks1(QVBoxLayout* lay) noexcept;
    void loadTasks2(QVBoxLayout* lay) noexcept;

 private:
    Ui::Choose* ui = nullptr;
};
