#include "appcontroller.h"

#include "app/appcontext.h"

AppController::AppController(std::shared_ptr<AppContext> ctx, QObject *parent)
    : QObject{parent}
    , ctx_{ctx}
{}

void AppController::run() {
    ctx_->loadSession();
    if (ctx_->hasSession()) {
        showMainWindow();
    } else {
        showLogin();
    }
}

void AppController::showLogin() {
    login_dialog_ = std::make_unique<LoginDialog>(ctx_->getLoginUC());

    if (login_dialog_->exec() != QDialog::Accepted) {
        qApp->quit();
        return;
    }

    Session s;
    s.setToken(login_dialog_->getToken());
    ctx_->setSession(std::make_shared<Session>(s));

    login_dialog_.reset();
    showMainWindow();
}

void AppController::showMainWindow()
{
    main_window_ = std::make_unique<MainWindow>(ctx_);

    connect(
        main_window_.get(),
        &MainWindow::logoutRequested,
        this,
        [this]() {
            ctx_->clearSession();
            main_window_.reset();
            showLogin();
        }
        );

    main_window_->show();
}