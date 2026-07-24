#pragma once

#include <QObject>

#include <expected>

#include "core/domain/user.h"
#include "core/domain/errors.h"

class UsersService;

class UpdateProfileUseCase : public QObject
{
    Q_OBJECT
public:
    explicit UpdateProfileUseCase(UsersService* srv);

    void execute(const User& u);
    void execute(const User& u, const std::vector<std::byte>& avatar_bytes);

signals:
    void requestFinished(std::expected<User, Error>);
private:
    UsersService* srv_;
};

