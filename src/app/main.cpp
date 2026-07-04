#include "sessionmanager.h"

#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"
#include "infrastructure/network/qtauthservice.h"

#include "core/usecases/loginusecase.h"
#include "core/usecases/sendmessageusecase.h"
#include "core/usecases/loadcurrentuserusecase.h"
#include "core/domain/session.h"

#include "infrastructure/network/qtmessageservice.h"
#include "infrastructure/network/qtusersservice.h"
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
            sessionStorage.save(session);

            QtUsersService users_service;
            LoadCurrentUserUseCase load_current_user_use_case{&users_service, session};
            load_current_user_use_case.execute();

            w.show();

            return a.exec();
        } else {
            return 0;
        }
    } else {
        auto send_msgs_uc = std::make_unique<SendMessageUseCase>(
            msgs_srv.get(), sessionManager.getSession());
        QtUsersService users_service;
        LoadCurrentUserUseCase load_current_user_use_case{&users_service, sessionManager.getSession()};
        load_current_user_use_case.execute();
        MainWindow w{send_msgs_uc.get()};
        w.show();

        return a.exec();
    }
}
