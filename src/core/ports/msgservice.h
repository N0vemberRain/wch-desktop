#ifndef MSGSERVICE_H
#define MSGSERVICE_H

#include <QObject>

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"

class MessageService : public QObject {
    Q_OBJECT
public:
    virtual ~MessageService() = default;

    virtual SendMessageResult sendMessage(const Message& msg) = 0;

signals:
    void requestFinished(SendMessageResult res);
};


#endif // MSGSERVICE_H
