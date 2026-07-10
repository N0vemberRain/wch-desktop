#include "sessionmanager.h"
#include "app/appcontext.h"

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
#include <QMessageBox>

int main(int argc, char *argv[])
{
    try {
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("IgorCompany");
    QCoreApplication::setApplicationName("wch-desktop");

    SessionManager session_manager;
    auto session_storage = std::make_unique<QtSessionStorage>();

    auto auth_service = std::make_unique<QtAuthService>();
    auto login_use_case = std::make_unique<LoginUseCase>(*auth_service);

    if (auto session = session_storage->load(); session.has_value()) {
        session_manager.setSession(std::move(session.value()));
    } else {
        LoginDialog dialog{*login_use_case};
        if (dialog.exec() == QDialog::Accepted) {
            session.value().setToken(dialog.getToken());
            session_manager.setSession(std::move(session.value()));
        } else {
            return 0;
        }
    }

    auto ctx = std::make_unique<AppContext>(std::move(auth_service),
                    std::make_unique<QtUsersService>(),
                    std::make_unique<QtMessageService>(),
                    std::move(session_storage),
                   std::move(login_use_case),
                   std::move(session_manager));

    ctx->setupCurrentUserProfile();

    MainWindow w{std::move(ctx)};
    w.show();

    return a.exec();
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Critical error", QString::fromStdString(e.what()));

        return -1;
    }

    ///////////////////////////////////////////////////////////
    // if (!ctx.hasSession()) {
    //     Session session;
    //     // auto send_msgs_uc = std::make_unique<SendMessageUseCase>(
    //     //     msgs_srv.get(), session);
    //     MainWindow w{&ctx.send_msgs_use_case};

    //     LoginDialog dialog(ctx.login_use_case);

    //     if (dialog.exec() == QDialog::Accepted) {
    //         // session.setToken(dialog.getToken());
    //         // sessionManager.setSession(session);
    //         // sessionStorage.save(session);

    //         ctx.setSession(std::move(session));

    //         QtUsersService users_service;
    //         LoadCurrentUserUseCase load_current_user_use_case{&users_service, session};
    //         load_current_user_use_case.execute();

    //         w.show();

    //         return a.exec();
    //     } else {
    //         return 0;
    //     }
    // } else {
    //     // auto send_msgs_uc = std::make_unique<SendMessageUseCase>(
    //     //     msgs_srv.get(), sessionManager.getSession());
    //     QtUsersService users_service;
    //     // LoadCurrentUserUseCase load_current_user_use_case{&users_service, sessionManager.getSession()};
    //     // load_current_user_use_case.execute();
    //     MainWindow w{send_msgs_uc.get()};
    //     w.show();

    //     return a.exec();
    // }
}
