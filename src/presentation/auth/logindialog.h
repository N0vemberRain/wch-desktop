#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "core/usecases/loginusecase.h"
#include "core/domain/user.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(LoginUseCase& use_case, QWidget *parent = nullptr);
    ~LoginDialog() override;

    auto getLoggedUser() noexcept {
        return user_;
    }
public slots:
    void accept() override;

private slots:
    //void onLoginClicked();

private:
    Ui::LoginDialog *ui;

    LoginUseCase& login_use_case_;
    User user_;
};

#endif // LOGINDIALOG_H
