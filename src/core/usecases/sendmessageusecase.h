#ifndef SENDMESSAGEUSECASE_H
#define SENDMESSAGEUSECASE_H

#include <QObject>

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"
#include "core/ports/msgservice.h"
#include "core/domain/session.h"

class SendMessageUseCase : public QObject {
    Q_OBJECT
public:
    explicit SendMessageUseCase(MessageService* srv, Session* s);

    SendMessageResult execute(Message msg);

signals:
    void requestFinished(SendMessageResult res);

private:
    MessageService* srv_;
    Session* session_;
};

#endif // SENDMESSAGEUSECASE_H
