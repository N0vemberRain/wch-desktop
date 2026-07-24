#pragma once

#include <QObject>

#include "core/ports/users_service.h"

class Session;

class LoadCurrentUserUseCase : public QObject
{
    Q_OBJECT
public:
    explicit LoadCurrentUserUseCase(UsersService* srv, const Session& s);

    LoadCurrentUserUseCase(const LoadCurrentUserUseCase&) = delete;
    LoadCurrentUserUseCase& operator=(const LoadCurrentUserUseCase&) = delete;

    void execute();

    inline bool isRunning() const noexcept {
        return is_running_;
    }
signals:
    void loadCurrentUserFinished(std::expected<User, Error>);
    void loadAvatarFinished(std::expected<AvatarData, Error>);
private:
    void onLoadCurrentUserFinished(std::expected<User, Error> res);
    void onGetAvatarFinished(std::expected<AvatarData, Error> res);
private:
    UsersService* srv_;
    const Session& session_;

    bool is_running_ {false};
};

