#pragma once

#include <QObject>

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"

class MessageService;
class Session;

class SendMessageUseCase : public QObject {
    Q_OBJECT
public:
    explicit SendMessageUseCase(MessageService* srv, const Session& s);

    void execute(Message msg) const;

signals:
    void requestFinished(SendMessageResult res);

private:
    MessageService* srv_;
    const Session& session_;
};
