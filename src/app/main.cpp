#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"
#include "infrastructure/network/qtauthservice.h"
#include "core/usecases/loginusecase.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtAuthService auth_service;
    LoginUseCase login_use_case(auth_service);

    LoginDialog dialog(login_use_case);
    MainWindow w;
    if (dialog.exec() == QDialog::Accepted) {
        w.show();
    }
    return a.exec();
}
