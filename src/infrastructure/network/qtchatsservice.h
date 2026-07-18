#pragma once

#include "core/ports/chats_service.h"

#include <QGrpcCallOptions>

#include <memory>

#include "chats_client.grpc.qpb.h"
#include "core/domain/errors.h"

class QGrpcHttp2Channel;
class QGrpcCallReply;
class QGrpcStatus;

class QtChatsService : public ChatsService
{
public:
    QtChatsService();
    ~QtChatsService() override = default;

    void getChatsList(const UserID& id) override;

private slots:
    void onGetChatsListFinished(const QGrpcStatus& s);

private:
    Error errorHandle(const QGrpcStatus& s);

    using GetChatsResponse = chats::v1::GetChatsResponse;
    using Client = chats::v1::ChatsService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;
    std::unique_ptr<QGrpcCallReply> reply_;

    QGrpcCallOptions options_;
};
