#include "logindialog.h"
#include "ui_logindialog.h"

#include "login_error_text.h"

LoginDialog::LoginDialog(LoginUseCase& use_case, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    login_use_case_(use_case)
{
    ui->setupUi(this);

//    connect(ui->buttonBox, &QDialogButtonBox::accepted,
//            this, &LoginDialog::onLoginClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::accept() {
    const auto username = ui->loginLineEdit->text().toStdString();
    const auto password = ui->passwordLineEdit->text().toStdString();

    auto res = login_use_case_.execute(username, password);
    if (!res) {
        ui->errorLabel->setText(toQString(res.error()));
        return;
    }

    user_= res.value();
    QDialog::accept();
}
