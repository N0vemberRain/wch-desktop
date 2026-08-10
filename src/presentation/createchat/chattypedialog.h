#pragma once

#include <QDialog>

#include "core/domain/chat.h"

namespace Ui {
class ChatTypeDialog;
}

class ChatTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatTypeDialog(QWidget *parent = nullptr);
    ~ChatTypeDialog();

    Chat::Type getChosenType() const noexcept;
private:
    Ui::ChatTypeDialog *ui;
};

