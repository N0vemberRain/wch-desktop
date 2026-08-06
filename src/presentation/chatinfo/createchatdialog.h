#pragma once

#include <QDialog>

// #include <expected>

// #include "core/domain/chat.h"
// #include "core/domain/errors.h"

class CreateChatUseCase;

namespace Ui {
class CreateChatDialog;
}

class CreateChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateChatDialog(CreateChatUseCase& uc, QWidget *parent = nullptr);
    ~CreateChatDialog();

private slots:
    void onAvatarClicked();
    void onSaveClicked();
private:
    void startLoadAnim();
    void stopLoadAnim();

    Ui::CreateChatDialog *ui;

    CreateChatUseCase& uc_;

    QString avatar_path_;
};

