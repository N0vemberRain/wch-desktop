#include "chatparticipantsmodel.h"

ChatParticipantsModel::ChatParticipantsModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int ChatParticipantsModel::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return users_.size();
}

QVariant ChatParticipantsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= users_.size()) {
        return {};
    }

    const auto usr = users_[index.row()];

    switch (role) {
    case Qt::DisplayRole:
    case Roles::UserID: return usr.user_id;
    case Roles::Name: return usr.name;
    case Roles::Avatar: return usr.avatar;
    }

    return {};
}

QHash<int, QByteArray> ChatParticipantsModel::roleNames() const {
    return {
        {Roles::UserID, "user_id"},
        {Roles::Name, "name"},
        {Roles::Avatar, "avatar"},
    };
}

void ChatParticipantsModel::addUser(const ParticipantItem& u) noexcept {
    beginInsertRows(QModelIndex(), users_.size(), users_.size());
    users_.append(u);
    endInsertRows();
}

void ChatParticipantsModel::addAvatarForUser(const QString& user_id, QPixmap img) noexcept {
    auto it = std::ranges::find_if(users_, [&](const auto& item) {
        return item.user_id == user_id;
    });

    if (it == users_.end()) {
        return;
    }

    it->avatar = img;

    const auto row = std::distance(users_.begin(), it);
    auto idx = index(row);

    emit dataChanged(idx, idx, {Avatar});
}