#pragma once

#include <QObject>

#include <string>
#include <expected>

// #include "core/domain/user.h"
#include "core/domain/token.h"
#include "auth_error.h"


class AuthService : public QObject {
    Q_OBJECT
public:
    using LoginResult = std::expected<Token, AuthError>;

    virtual ~AuthService() = default;

    virtual void login(const std::string& name,
                       const std::string& password) = 0;

signals:
    void loginFinished(AuthService::LoginResult res);
};
