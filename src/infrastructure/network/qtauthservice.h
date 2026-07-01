#pragma once

#include <string>
#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>

#include "core/ports/authservice.h"
#include "auth_client.grpc.qpb.h"


class QtAuthService : public AuthService
{
public:
    QtAuthService();

    void login(const std::string& name, const std::string& password) override;

private slots:
    void onLoginFinished(const QGrpcStatus& reply);
private:
    using Client = auth::v1::AuthService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;

    std::vector<std::unique_ptr<QGrpcCallReply>> replies_;
    std::unique_ptr<QGrpcCallReply> reply_;
};
