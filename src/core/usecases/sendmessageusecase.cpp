#include "sendmessageusecase.h"

#include "core/ports/msgservice.h"
#include "core/domain/session.h"

SendMessageUseCase::SendMessageUseCase(MessageService* srv, const Session& s)
    : srv_{srv},
    session_{s}
{
    connect(srv_, &MessageService::requestFinished, this, [this](SendMessageResult res) {
        emit requestFinished(res);
    });
}

void SendMessageUseCase::execute(Message msg) const {
    msg.sender_id = session_.getCurrentUserID();
    msg.sender_name = session_.getCurrentUser().name;

    srv_->sendMessage(msg);
}
