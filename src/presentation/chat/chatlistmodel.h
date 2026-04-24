#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>
#include <QString>
#include <QVector>

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    struct ChatItem {
        QString name;
        QString last_message;
        int unread_count;
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
    };

    void addChat(const ChatItem& item);

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<ChatItem> items_;
};

#endif // CHATLISTMODEL_H
