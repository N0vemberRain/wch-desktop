#include "qtmessageservice.h"

#include <QUrl>

#include <QMessageBox>

QtMessageService::QtMessageService()
{
    channel_ = std::make_shared<QGrpcHttp2Channel>(QUrl{"http://localhost:5051"});

    client_ = std::make_unique<Client>();
    if (!client_->attachChannel(channel_)) {
        QMessageBox::warning(nullptr, "QtMessageService", "can't attach to the msgs channel");
    }
}

void QtMessageService::sendMessage(const Message& msg) {
    msgs::v1::SendMessageRequest request;
    request.setSenderId(QString::fromStdString(msg.sender_id));
    request.setChatId(QString::fromStdString(msg.chat_id));
    request.setContent(QString::fromStdString(msg.content));

    auto reply = client_->SendMessage(request);
    auto raw_reply = reply.get();
    replies_.push_back(std::move(reply));
    connect(raw_reply, &QGrpcCallReply::finished, this, [raw_reply, this](const QGrpcStatus& status) {
        if (!status.isOk()) {
            QMessageBox::warning(nullptr, "QtMessageService", status.message());
            removeReply(raw_reply);
            return;
        }
        auto data = raw_reply->read<msgs::v1::MessageResponse>();
        if (data.has_value()) {
            SendMessageResult res;
            Message msg;
            auto in_msg = data.value().msg();
            msg.content = in_msg.content().toStdString();
            msg.chat_id = in_msg.chatId().toStdString();
            res.message = msg;

            removeReply(raw_reply);
            emit requestFinished(res);
        } else {
            QMessageBox::warning(nullptr, "QtMessageService", "data is empty");
        }
    }, Qt::SingleShotConnection);
}

void QtMessageService::removeReply(QGrpcCallReply* reply) {
    std::erase_if(replies_, [reply](const std::unique_ptr<QGrpcCallReply>& r) {
        if (r.get() == reply) {
            return true;
        }

        return false;
    });
}