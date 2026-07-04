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
    void addOption(const std::string& key, const std::string& value, const std::string& key_param="") override;
private slots:
    void onGetUserFinished(const QGrpcStatus& status);
private:
    using Response = users::v1::GetUserResponse;
    using Client = users::v1::UsersService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;
    std::unique_ptr<QGrpcCallReply> reply_;

    QGrpcCallOptions options_;
};

