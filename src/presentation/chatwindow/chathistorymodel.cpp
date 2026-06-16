#include "chathistorymodel.h"

#include <QDebug>

#include "utils.h"

ChatHistoryModel::ChatHistoryModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ChatHistoryModel::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return messages_.size();
}

QVariant ChatHistoryModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= messages_.size()) {
        return {};
    }

    const auto msg = messages_[index.row()];

    switch (role) {
    case Qt::DisplayRole:
    case Roles::ContentRole: return msg.content;
    case Roles::TimestampRole: return msg.timestamp;
    case Roles::IsOutgoingRole: return msg.is_outgoing;
    case Roles::SenderRole: return msg.sender;
    case Roles::StatusRole: return static_cast<int>(msg.status);
    }

    return {};
}

QHash<int, QByteArray> ChatHistoryModel::roleNames() const {
    return {
        {Roles::ContentRole, "content"},
        {Roles::TimestampRole, "timestamp"},
        {Roles::IsOutgoingRole, "is_outgoing"},
        {Roles::SenderRole, "sender"},
        {Roles::StatusRole, "status"},
    };
}

void ChatHistoryModel::addMessage(const MessageItem &msg) noexcept {
    beginInsertRows(QModelIndex(), messages_.size(), messages_.size());
    messages_.append(msg);
    endInsertRows();
}

bool ChatHistoryModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
    qDebug() << "ChatHistoryModel.setData: entering. Role " << role;
    if (!idx.isValid() || idx.row() >= messages_.size()) {
        return false;
    }

    auto& msg = messages_[idx.row()];
    if (role == Roles::ContentRole) {
        qDebug() << "ChatHistoryModel.setData: role == ContentRole";
        msg.content = value.toString();
    } else {
        return false;
    }

    emit dataChanged(idx, idx, {role});
    return true;
}

bool ChatHistoryModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (row < 0 || row + count > messages_.size())
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    for (int i = 0; i < count; ++i)
        messages_.removeAt(row);
    endRemoveRows();

    return true;
}

void ChatHistoryModel::setChatData(std::unique_ptr<Chat> data) {
    Q_ASSERT(data != nullptr);
    chat_ = std::move(data);
    for (const auto& msg : chat_->messages) {
        auto time = toQDateTime(msg.created_at);
        auto msg_item = MessageItem{
            QString::fromStdString(msg.sender_name),
            QString::fromStdString(msg.content),
            time,
            msg.is_outgoing,
        };
        addMessage(msg_item);
    }
}
