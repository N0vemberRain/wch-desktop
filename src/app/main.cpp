#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"
#include "infrastructure/network/qtauthservice.h"

#include "core/usecases/loginusecase.h"
#include "core/usecases/sendmessageusecase.h"
#include "core/domain/session.h"

#include "infrastructure/network/qtmessageservice.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QtAuthService auth_service;
    LoginUseCase login_use_case(auth_service);

    LoginDialog dialog(login_use_case);

    auto session = std::make_unique<Session>();

    auto msgs_srv = std::make_unique<QtMessageService>();
    auto send_msgs_uc = std::make_unique<SendMessageUseCase>(msgs_srv.get(), session.get());

    MainWindow w{send_msgs_uc.get()};
    if (dialog.exec() == QDialog::Accepted) {
        session->setCurrentUser(dialog.getLoggedUser());
        w.show();
    }
    return a.exec();
}
