#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QVector>
#include <QPixmap>

#include "core/domain/chat.h"

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct ChatItem {
        QString name;
        QString last_message;
        int unread_count;
        QPixmap avatar;
        QString id;
        Chat::Type type;
    };

    explicit ChatListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Custom roles
    enum Roles {
        Name = Qt::UserRole + 1,
        LastMessage,
        UnreadCount,
        Avatar = Qt::UserRole + 4,
        Id = Qt::UserRole + 5,
        Type = Qt::UserRole + 6,
    };

    void addChat(const ChatItem& item);
    void updateChat(ChatItem item);
    void updateAvatarForChat(const QString& chat_id, QPixmap a) noexcept;

    void setUnreadMessagesCount(const QString& chat_id, int unread);
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<ChatItem> items_;
};
