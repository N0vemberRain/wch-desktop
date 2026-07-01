#include "logindialog.h"
#include "ui_logindialog.h"

#include "login_error_text.h"

#include <QMovie>

LoginDialog::LoginDialog(LoginUseCase& use_case, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    login_use_case_(use_case)
{
    ui->setupUi(this);

//    connect(ui->buttonBox, &QDialogButtonBox::accepted,
//            this, &LoginDialog::onLoginClicked);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->spinLoadLable->setMovie(gif);
    ui->spinLoadLable->setScaledContents(true);
    ui->spinLoadLable->hide();
    ui->verticalLayout->setAlignment(ui->spinLoadLable, Qt::AlignCenter);

    connect(&login_use_case_, &LoginUseCase::loginFinished, this, &LoginDialog::onLoginFinished);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::accept() {
    ui->spinLoadLable->show();
    ui->spinLoadLable->movie()->start();
    const auto username = ui->loginLineEdit->text().toStdString();
    const auto password = ui->passwordLineEdit->text().toStdString();

    login_use_case_.execute(username, password);
    setDisabled(true);
}

void LoginDialog::onLoginFinished(LoginUseCase::LoginResult res) {
    if (res.has_value()) {
        token_ = res.value();
    } else {
        ui->errorLabel->setText(toQString(res.error()));
        ui->spinLoadLable->movie()->stop();
        ui->spinLoadLable->hide();
        setDisabled(false);
        return;
    }

    ui->spinLoadLable->movie()->stop();
    setDisabled(false);
    ui->spinLoadLable->hide();

    QDialog::accept();
}
