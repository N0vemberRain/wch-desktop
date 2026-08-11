#pragma once

#include <QObject>

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"

class MessageService;
class Session;

class SendMessageUseCase : public QObject {
    Q_OBJECT
public:
    explicit SendMessageUseCase(MessageService* srv);
    void setSession(std::shared_ptr<Session> s_ptr);

    void execute(Message msg) const;

signals:
    void requestFinished(SendMessageResult res);

private:
    MessageService* srv_;
    std::shared_ptr<Session> session_;
};
