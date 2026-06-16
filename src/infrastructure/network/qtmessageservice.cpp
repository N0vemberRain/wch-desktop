#include "qtmessageservice.h"

#include <QMessageBox>


QtMessageService::QtMessageService()
{
    channel_ = std::make_shared<QGrpcHttp2Channel>(QUrl{"http://localhost:5051"});

    client_ = std::make_unique<Client>();
    if (!client_->attachChannel(channel_)) {
        QMessageBox::warning(nullptr, "QtMessageService", "can't attach to the msgs channel");
    }
}

SendMessageResult QtMessageService::sendMessage(const Message& msg) {
    msgs::v1::SendMessageRequest request;
    request.setSenderId(QString::fromStdString(msg.sender_id));
    request.setChatId(QString::fromStdString(msg.chat_id));
    request.setContent(QString::fromStdString(msg.content));

    auto reply = client_->SendMessage(request);
    connect(reply.get(), &QGrpcCallReply::finished, this, [&reply, this]() {
        auto data = reply->read<msgs::v1::MessageResponse>();
        if (data.has_value()) {
            SendMessageResult res;
            Message msg;
            auto in_msg = data.value().msg();
            msg.content = in_msg.content().toStdString();
            msg.chat_id = in_msg.chatId().toStdString();
            res.message = msg;
            emit requestFinished(res);
        } else {
            QMessageBox::warning(nullptr, "QtMessageService", "data is empty");
        }
    });
    return {};
}