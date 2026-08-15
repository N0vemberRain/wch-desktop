#include "loadparticipantsusecase.h"

#include "core/ports/chats_service.h"
#include "core/usecases/loadparticipantsusecase.h"

LoadParticipantsUseCase::LoadParticipantsUseCase(
    ChatsService* srv,
    QObject *parent
)
    : QObject{parent}
    , srv_{srv}
{
    connect(srv_, &ChatsService::listChatParticipantsFinished, this,
            [this](const auto& res) {
                emit requestFinished(res);
    });
}

void LoadParticipantsUseCase::execute(const ChatID& chat_id) {
    srv_->listChatParticipants(chat_id);
}
