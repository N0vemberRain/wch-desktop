#pragma once

#include <QObject>

#include <expected>

#include "core/domain/user.h"
#include "core/domain/user_summary.h"
#include "core/domain/types.h"
#include "core/domain/errors.h"
#include "core/domain/users_search_filter.h"

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
    virtual void requestAvatars(const std::list<UserID>& ids) = 0;

    virtual void searchUsers(const UsersSearchFilter& filter) = 0;
signals:
    void loadCurrentUserFinished(std::expected<User, Error>);
    void currentUserChanged(std::expected<User, Error>);
    void getAvatarFinished(std::expected<AvatarData, Error>);
    void getAvatarsFinished(std::expected<std::list<AvatarData>, Error>);
    void searchUsersFinished(std::expected<std::list<UserSummary>, Error> res);

};