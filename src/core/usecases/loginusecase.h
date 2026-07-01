#pragma once

#include <QObject>

#include <string>
#include <expected>

#include "core/ports/authservice.h"
#include "login_error.h"


class LoginUseCase : public QObject
{
    Q_OBJECT
public:
    using LoginResult = std::expected<Token, LoginError>;

    explicit LoginUseCase(AuthService& s);

    void execute(const std::string& name, const std::string& password);
signals:
    void loginFinished(LoginUseCase::LoginResult);
private:
    AuthService& auth_service_;
};