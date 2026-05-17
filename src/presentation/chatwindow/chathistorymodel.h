#ifndef CHATHISTORYMODEL_H
#define CHATHISTORYMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include <memory>

#include "core/domain/chat.h"
#include "core/domain/message.h"
#include "messageitem.h"

class ChatHistoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = Qt::UserRole + 1,
        TimestampRole,
        IsOutgoingRole,
        SenderRole,
    };

    explicit ChatHistoryModel(QObject *parent = nullptr);

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
protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<MessageItem> messages_;

    std::unique_ptr<Chat> chat_;
};

#endif // CHATHISTORYMODEL_H
