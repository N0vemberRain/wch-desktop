#pragma once

#include "msgs_client.grpc.qpb.h"

#include "core/ports/msgservice.h"
#include "core/domain/message.h"

#include <memory>
#include <vector>
#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>

class QtMessageService : public MessageService
{
public:
    QtMessageService();
    virtual ~QtMessageService() = default;

    virtual void sendMessage(const Message& msg) override;

signals:

private:
    void removeReply(QGrpcCallReply* reply);

    using Client = msgs::v1::MessagesService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;

    std::vector<std::unique_ptr<QGrpcCallReply>> replies_;
};
