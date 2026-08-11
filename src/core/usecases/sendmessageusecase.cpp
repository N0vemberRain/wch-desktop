#include "sendmessageusecase.h"

#include "core/ports/msgservice.h"
#include "core/domain/session.h"

SendMessageUseCase::SendMessageUseCase(MessageService* srv)
    : srv_{srv}
{
    connect(srv_, &MessageService::requestFinished, this, [this](SendMessageResult res) {
        emit requestFinished(res);
    });
}

void SendMessageUseCase::execute(Message msg) const {
    msg.sender_id = session_->getCurrentUserID();
    msg.sender_name = session_->getCurrentUser().name;

    srv_->sendMessage(msg);
}

void SendMessageUseCase::setSession(std::shared_ptr<Session> s_ptr) {
    assert(s_ptr);
    assert(srv_);

    session_ = s_ptr;

}