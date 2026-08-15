#pragma once

#include <QObject>
#include <expected>

#include "core/domain/chat_participant.h"
#include "core/domain/errors.h"

class ChatsService;

class LoadParticipantsUseCase : public QObject
{
    Q_OBJECT
public:
    explicit LoadParticipantsUseCase(ChatsService* srv, QObject *parent = nullptr);

    void execute(const ChatID& chat_id);

signals:
    void requestFinished(std::expected<std::list<ChatParticipant>, Error> res);


private:
    ChatsService* srv_;
};

