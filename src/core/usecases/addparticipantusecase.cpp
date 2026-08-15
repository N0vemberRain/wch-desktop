#include "addparticipantusecase.h"

#include "core/ports/chats_service.h"

AddParticipantUseCase::AddParticipantUseCase(ChatsService* srv, QObject *parent)
    : QObject{parent}
    , srv_(srv)
{
    connect(srv_, &ChatsService::addParticipantFinished, this, [this](auto res) {
        emit requestFinished(res);
    });
}

void AddParticipantUseCase::execute(const ChatID& chat_id, const UserID& user_id, ChatParticipant::Role role) {
    srv_->addParticipant(chat_id, user_id, role);
}
