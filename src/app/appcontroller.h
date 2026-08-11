#pragma once

#include <QObject>

#include <memory>

#include "presentation/main/mainwindow.h"
#include "presentation/auth/logindialog.h"

class AppContext;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(std::shared_ptr<AppContext> ctx, QObject *parent = nullptr);

    void run();
signals:


private:
    void showLogin();
    void showMainWindow();

    std::shared_ptr<AppContext> ctx_;
    std::unique_ptr<LoginDialog> login_dialog_;
    std::unique_ptr<MainWindow> main_window_;
};

