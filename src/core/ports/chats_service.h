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
    virtual void addOption(const std::string& key,
                           const std::string& value,
                           const std::string& key_param="") = 0;
    virtual void updateChatInfo(const Chat& c,
                                const std::vector<std::byte>& av_data) = 0;
signals:
    void getChatsListFinished(std::expected<std::list<Chat>, Error>);
    void updateChatInfoFinished(std::expected<Chat, Error>);
};
