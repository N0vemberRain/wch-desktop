#pragma once

#include "core/ports/users_service.h"

#include <memory>

#include <QGrpcCallOptions>

#include "users_client.grpc.qpb.h"

class QGrpcChannelOptions;
class QGrpcHttp2Channel;
class QGrpcCallReply;
class QGrpcStatus;

class QtUsersService : public UsersService
{
public:
    QtUsersService();
    ~QtUsersService() = default;

    void getUser(const UserID& user_id) override;
    void updateUser(const User& u) override;
    void addOption(const std::string& key, const std::string& value, const std::string& key_param="") override;
    void requestAvatar(const UserID& user_id) override;
private slots:
    void onGetUserFinished(const QGrpcStatus& status);
    void onUpdateUserFinished(const QGrpcStatus& status);
    void onGetAvatarFinished(const QGrpcStatus& status);
private:
    Error errorHandle(const QGrpcStatus& s);

    using Response = users::v1::GetUserResponse;
    using Client = users::v1::UsersService::Client;
    using GetAvatarResponse = users::v1::GetAvatarResponse;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;
    std::unique_ptr<QGrpcCallReply> reply_;

    QGrpcCallOptions options_;
};

