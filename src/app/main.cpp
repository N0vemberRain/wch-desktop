#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"
#include "infrastructure/network/qtauthservice.h"

#include "core/usecases/loginusecase.h"
#include "core/usecases/sendmessageusecase.h"

#include "infrastructure/network/qtmessageservice.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtAuthService auth_service;
    LoginUseCase login_use_case(auth_service);

    LoginDialog dialog(login_use_case);

    auto msgs_srv = std::make_unique<QtMessageService>();
    auto send_msgs_uc = std::make_unique<SendMessageUseCase>(msgs_srv.get());

    MainWindow w{send_msgs_uc.get()};
    if (dialog.exec() == QDialog::Accepted) {
        w.show();
    }
    return a.exec();
}
