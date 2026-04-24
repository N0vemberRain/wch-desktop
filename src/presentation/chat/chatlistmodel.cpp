#include "chatlistmodel.h"

ChatListModel::ChatListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return items_.size();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= items_.size())
        return QVariant();

    const auto& item = items_.at(index.row());
    switch (role) {
    case Roles::Name: return item.name;
    case Roles::LastMessage: return item.last_message;
    case Roles::UnreadCount: return item.unread_count;
        // if no delegate is used
    case Qt::DisplayRole: return item.name + "-" + item.last_message;
    default: return QVariant();
    }
}


QHash<int, QByteArray> ChatListModel::roleNames() const {
    return {
        {Roles::Name, "name"},
        {Roles::LastMessage, "last_message"},
        {Roles::UnreadCount, "unread_count"}
    };
}

void ChatListModel::addChat(const ChatItem &item) {
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(item);
    endInsertRows();
}
