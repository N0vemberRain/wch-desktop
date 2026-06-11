#ifndef SENDMESSAGEUSECASE_H
#define SENDMESSAGEUSECASE_H

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"
#include "core/ports/msgservice.h"

class SendMessageUseCase
{
public:
    explicit SendMessageUseCase(MessageService& srv);

    SendMessageResult execute(const Message& msg);

private:
    MessageService& srv_;
};

#endif // SENDMESSAGEUSECASE_H
