#include "chatlistmodel.h"

#include <ranges>

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
    case Roles::Avatar: return item.avatar;
    case Roles::Id: return item.id;
    case Roles::Type: return Chat::typeToInt(item.type);
        // if no delegate is used
    case Qt::DisplayRole: return item.name + "-" + item.last_message;
    default: return QVariant();
    }
}


QHash<int, QByteArray> ChatListModel::roleNames() const {
    return {
        {Roles::Name, "name"},
        {Roles::LastMessage, "last_message"},
        {Roles::UnreadCount, "unread_count"},
        {Roles::Avatar, "avatar"},
        {Roles::Id, "id"},
        {Roles::Type, "type"},
    };
}

void ChatListModel::addChat(const ChatItem &item) {
    beginInsertRows(QModelIndex(), items_.size(), items_.size());
    items_.append(item);
    endInsertRows();
}

void ChatListModel::updateChat(ChatItem chat) {
    auto it = std::ranges::find_if(items_, [&](const auto& item) {
        return item.id == chat.id ? true : false;
    });

    if (it == items_.end())
        return;

    *it = std::move(chat);

    const auto row = std::distance(items_.begin(), it);
    auto idx = index(row);

    emit dataChanged(idx, idx, {Name, LastMessage, UnreadCount, Avatar, Id, Type});
}

void ChatListModel::updateAvatarForChat(const QString& chat_id, QPixmap av) noexcept {
    auto it = std::ranges::find_if(items_, [&](const auto& item) {
        return item.id == chat_id;
    });

    if (it == items_.end()) {
        return;
    }

    it->avatar = av;

    const auto row = std::distance(items_.begin(), it);
    auto idx = index(row);

    emit dataChanged(idx, idx, {Avatar});
}

void ChatListModel::setUnreadMessagesCount(const QString &chat_id, int unread) {
    for (ChatItem& c : items_) {
        if (c.id == chat_id) {
            c.unread_count = unread;
            break;
        }
    }
}
