#pragma once

#include <QObject>

#include <optional>

#include "core/domain/chat_participant.h"
#include "core/domain/types.h"
#include "core/domain/errors.h"

class ChatsService;

class AddParticipantUseCase : public QObject
{
    Q_OBJECT
public:
    explicit AddParticipantUseCase(ChatsService* srv, QObject *parent = nullptr);

    void execute(const ChatID& chat_id, const UserID& user_id, ChatParticipant::Role role);
signals:
    void requestFinished(std::optional<Error> error);

private:
    ChatsService* srv_;
};

