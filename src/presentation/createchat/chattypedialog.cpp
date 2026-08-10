#include "chattypedialog.h"
#include "ui_chattypedialog.h"

ChatTypeDialog::ChatTypeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatTypeDialog)
{
    ui->setupUi(this);
}

ChatTypeDialog::~ChatTypeDialog()
{
    delete ui;
}

Chat::Type ChatTypeDialog::getChosenType() const noexcept {
    if (ui->directButton->isChecked()) {
        return Chat::Type::Direct;
    }
    if (ui->groupButton->isChecked()) {
        return Chat::Type::Group;
    }

    return Chat::Type::Unknown;
}