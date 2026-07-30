#include "mockchatfactory.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QDebug>

#include "utils.h"

std::unique_ptr<Chat> MockChatFactory::create(const QString& chat_id,
                                              const QString& chat_name,
                                              const QString& filename) {
    QFile file{filename};
    if (!file.open(QFile::ReadOnly)) {
        return nullptr;
    }

    auto json = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json, &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << err.errorString();
        return nullptr;
    }

    QJsonObject root = doc.object();
    QJsonArray msgs = root["msgs"].toArray();

    auto chat = std::make_unique<Chat>();

    chat->id = chat_id.toStdString();
    chat->name = chat_name.toStdString();

    for (const QJsonValue value : msgs)
    {
        QJsonObject obj = value.toObject();

        Message msg;

        msg.id =
            obj["id"].toString().toStdString();

        msg.chat_id =
            obj["chatId"].toString().toStdString();

        msg.sender_id =
            obj["senderId"].toString().toStdString();

        msg.content =
        obj["content"].toString().toStdString();

        auto time_str =
            obj["createdAt"].toString();
        auto timestamp = QDateTime::fromString(time_str, Qt::DateFormat::ISODateWithMs);
        msg.created_at = fromQDateTime(timestamp);
        // fake outgoing flag for testing
        msg.is_outgoing = obj["outgoing"].toBool();
        if (!msg.is_outgoing) {
            msg.sender_name = obj["senderName"].toString().toStdString();
        }

        chat->messages.push_back(std::move(msg));
    }

    return chat;
}

std::vector<Chat> MockChatFactory::getChatList(const QString& filename) {
    QFile file{filename};
    if (!file.open(QFile::ReadOnly)) {
        return {};
    }

    auto json = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json, &err);
    if (err.error != QJsonParseError::NoError) {
        qDebug() << err.errorString();
        return {};
    }

    QJsonObject root = doc.object();
    QJsonArray chats = root["chats"].toArray();

    std::vector<Chat> res;

    for (const auto value : chats) {
        QJsonObject obj = value.toObject();
        Chat chat;
        chat.id = obj["id"].toString().toStdString();
        chat.name = obj["name"].toString().toStdString();
        chat.type = obj["type"].toString() == "group" ?
                    Chat::Type::Group :
                    Chat::Type::Direct;
        chat.avatar = obj["avatar"].toString().toStdString();
        chat.unread_count = obj["unread_count"].toInt();
        chat.last_message = obj["last_message"].toString().toStdString();

        res.push_back(chat);
    }

    return res;
}
