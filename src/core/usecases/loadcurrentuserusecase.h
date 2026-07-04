#pragma once

#include <QObject>

#include "core/ports/users_service.h"

class Session;

class LoadCurrentUserUseCase : public QObject
{
    Q_OBJECT
public:
    explicit LoadCurrentUserUseCase(UsersService* srv, const Session& s);

    void execute();
signals:
    void loadCurrentUserFinished(UsersService::CurrentUserResult);

private:
    void onLoadCurrentUserFinished(UsersService::CurrentUserResult);
private:
    UsersService* srv_;
    const Session& session_;
};

