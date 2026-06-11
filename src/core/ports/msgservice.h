#ifndef MSGSERVICE_H
#define MSGSERVICE_H

#include "core/domain/message.h"
#include "core/domain/sendmessageresult.h"

class MessageService {
public:
    virtual ~MessageService() = default;

    virtual SendMessageResult sendMessage(const Message& msg) = 0;
};


#endif // MSGSERVICE_H
