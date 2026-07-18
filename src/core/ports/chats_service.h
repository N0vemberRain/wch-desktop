#pragma once

#include <QObject>

#include <expected>
#include <list>

#include "core/domain/types.h"
#include "core/domain/chat.h"
#include "core/domain/errors.h"

class ChatsService : public QObject {
    Q_OBJECT
public:
    virtual ~ChatsService() = default;

    virtual void getChatsList(const UserID& id) = 0;

signals:
    void getChatsListFinished(std::expected<std::list<Chat>, Error>);
};
