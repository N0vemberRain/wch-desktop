#pragma once

#include <memory>

#include <QAbstractListModel>
#include <QVector>
#include <QHash>
#include <QByteArray>

#include "messageitem.h"
#include "core/domain/chat.h"

class QModelIndex;
class QVariant;

class ChatHistoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = Qt::UserRole + 1,
        TimestampRole,
        IsOutgoingRole,
        SenderRole,
        StatusRole,
        SenderIDRole,
    };

    explicit ChatHistoryModel(QObject *parent = nullptr);
    ~ChatHistoryModel() = default;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addMessage(const MessageItem& msg) noexcept;
    bool setData(const QModelIndex& idx, const QVariant& value, int role) override;
    bool removeRows(int role, int count, const QModelIndex& parent = QModelIndex()) override;

    void setChatData(std::unique_ptr<Chat> data);
    QString getID() const {
        return QString::fromStdString(chat_->id);
    }

    auto getUnreadCount() const noexcept {
        return chat_->unread_count;
    }
    void setUnreadCount(int unread) noexcept {
        chat_->unread_count = unread;
    }
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<MessageItem> messages_;

    std::unique_ptr<Chat> chat_;
};
