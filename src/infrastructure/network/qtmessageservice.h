#ifndef QTMESSAGESERVICE_H
#define QTMESSAGESERVICE_H

#include "msgs_client.grpc.qpb.h"

#include "core/ports/msgservice.h"
// #include "core/domain/message.h"

#include <memory>
#include <QtGrpc/QGrpcChannelOptions>
#include <QtGrpc/QGrpcHttp2Channel>

class QtMessageService : public MessageService
{
public:
    QtMessageService();
    virtual ~QtMessageService() = default;

    virtual SendMessageResult sendMessage(const Message& msg) override;

private:
    using Client = msgs::v1::MessagesService::Client;

    std::shared_ptr<QGrpcHttp2Channel> channel_;
    std::unique_ptr<Client> client_;
};

#endif // QTMESSAGESERVICE_H
