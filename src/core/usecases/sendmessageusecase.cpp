#include "sendmessageusecase.h"

SendMessageUseCase::SendMessageUseCase(MessageService* srv, Session* s)
    : srv_{srv},
    session_{s}
{
    connect(srv_, &MessageService::requestFinished, this, [this](SendMessageResult res) {
        emit requestFinished(res);
    });
}

SendMessageResult SendMessageUseCase::execute(Message msg) {
    if (msg.content.empty()) {
        return {false, "empty message", {}};
    }

    msg.sender_id = session_->getCurrentUserID();
    msg.sender_name = session_->getCurrentUser().name;

    return srv_->sendMessage(msg);
}
