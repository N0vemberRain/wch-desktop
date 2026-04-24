#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "core/usecases/loginusecase.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(LoginUseCase& use_case, QWidget *parent = nullptr);
    ~LoginDialog() override;

public slots:
    void accept() override;

private slots:
    //void onLoginClicked();

private:
    Ui::LoginDialog *ui;

    LoginUseCase& login_use_case_;
};

#endif // LOGINDIALOG_H
