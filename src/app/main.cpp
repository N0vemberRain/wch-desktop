#include "sessionmanager.h"

#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"
#include "infrastructure/network/qtauthservice.h"

#include "core/usecases/loginusecase.h"
#include "core/usecases/sendmessageusecase.h"
#include "core/domain/session.h"

#include "infrastructure/network/qtmessageservice.h"
#include "infrastructure/utils/qtsessionstorage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("IgorCompany");
    QCoreApplication::setApplicationName("wch-desktop");

    SessionManager sessionManager;
    QtSessionStorage sessionStorage;

    if (auto session = sessionStorage.load(); session.has_value()) {
        sessionManager.setSession(session.value());
    }

    QtAuthService auth_service;
    LoginUseCase login_use_case(auth_service);

    auto msgs_srv = std::make_unique<QtMessageService>();

    if (!sessionManager.hasSession()) {
        Session session;
        auto send_msgs_uc = std::make_unique<SendMessageUseCase>(
            msgs_srv.get(), session);
        MainWindow w{send_msgs_uc.get()};

        LoginDialog dialog(login_use_case);

        if (dialog.exec() == QDialog::Accepted) {
            session.setToken(dialog.getToken());
            sessionManager.setSession(session);
            w.show();
        } else {
            return 0;
        }
    } else {
        auto send_msgs_uc = std::make_unique<SendMessageUseCase>(
            msgs_srv.get(), sessionManager.getSession());
        MainWindow w{send_msgs_uc.get()};
        w.show();
    }
    return a.exec();
}
