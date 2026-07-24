#pragma once

#include <QObject>

#include <expected>

#include "core/domain/user.h"
#include "core/domain/types.h"
#include "core/domain/errors.h"

class UsersService : public QObject {
    Q_OBJECT
public:
    virtual ~UsersService() = default;

    using CurrentUserResult = std::expected<User, Error>;

    virtual void getUser(const UserID& user_id) = 0;
    virtual void updateUser(const User& u) = 0;
    virtual void updateUser(const User& u, const std::vector<std::byte>& avatar_data) = 0;
    // add an option to grpc request, e.g. key - authorization, value - token, key_param = Bearer
    virtual void addOption(const std::string& key, const std::string& value, const std::string& key_param="") = 0;
    virtual void requestAvatar(const UserID& user_id) = 0;
signals:
    void loadCurrentUserFinished(std::expected<User, Error>);
    void currentUserChanged(std::expected<User, Error>);
    void getAvatarFinished(std::expected<AvatarData, Error>);
};