#pragma once

#include <QObject>

#include <expected>

#include "core/domain/user.h"
#include "core/domain/errors.h"
#include "core/domain/types.h"

class UsersService;

class UpdateProfileUseCase : public QObject
{
    Q_OBJECT
public:
    explicit UpdateProfileUseCase(UsersService* srv);

    void execute(const User& u);
    void execute(const User& u, const AvatarData& av);

signals:
    void requestFinished(std::expected<std::pair<User, AvatarData>, Error>);
private:
    UsersService* srv_;
};

