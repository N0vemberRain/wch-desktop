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
    return {};
}