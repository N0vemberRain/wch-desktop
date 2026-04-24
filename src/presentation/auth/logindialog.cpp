#include "logindialog.h"
#include "ui_logindialog.h"

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

    const auto [p_user, err] = login_use_case_.execute(username, password);
    if (!err.empty()) {
        ui->errorLabel->setText(QString::fromStdString(err));
        return;
    }

    if (!p_user) {
        ui->errorLabel->setText("user pointer is null");
        return;
    }

    QDialog::accept();
}
