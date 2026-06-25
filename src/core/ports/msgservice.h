#pragma once

#include <QObject>

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"

class MessageService : public QObject {
    Q_OBJECT
public:
    virtual ~MessageService() = default;

    virtual void sendMessage(const Message& msg) = 0;

signals:
    void requestFinished(SendMessageResult res);
};
