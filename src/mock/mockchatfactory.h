#ifndef MOCKCHATFACTORY_H
#define MOCKCHATFACTORY_H

#include <QString>
#include <memory>
#include <vector>

#include "core/domain/chat.h"

class MockChatFactory
{
public:
    static std::unique_ptr<Chat> create(std::unique_ptr<Chat> chat, const QString& filename);
    static std::vector<Chat> getChatList(const QString& filename);
};

#endif // MOCKCHATFACTORY_H
