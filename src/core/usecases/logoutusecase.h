#pragma once

#include <QObject>

class AuthService;

class LogoutUseCase : public QObject
{
    Q_OBJECT
public:
    explicit LogoutUseCase(AuthService* srv_, QObject *parent = nullptr);

    void execute();
signals:

private:
    AuthService* srv_;
};
