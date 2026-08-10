#include "searchusersmodel.h"

SearchUsersModel::SearchUsersModel(QObject *parent)
    : QAbstractListModel{parent}
{}


int SearchUsersModel::rowCount(const QModelIndex &parent) const {
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return users_.size();
}

QVariant SearchUsersModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= users_.size()) {
        return {};
    }

    const auto usr = users_[index.row()];

    switch (role) {
    case Qt::DisplayRole:
    case Roles::ID: return usr.id;
    case Roles::NameRole: return usr.name;
    case Roles::EmailRole: return usr.email;
    case Roles::AvatarRole: return usr.avatar;
    }

    return {};
}

QHash<int, QByteArray> SearchUsersModel::roleNames() const {
    return {
        {Roles::ID, "ID"},
        {Roles::NameRole, "name"},
        {Roles::EmailRole, "email"},
        {Roles::AvatarRole, "avatar"},
    };
}

void SearchUsersModel::addUser(const UserItem& u) noexcept {
    beginInsertRows(QModelIndex(), users_.size(), users_.size());
    users_.append(u);
    endInsertRows();
}

void SearchUsersModel::clear() noexcept {
    if (users_.isEmpty())
        return;

    beginRemoveRows(QModelIndex(), 0, users_.size() - 1);
    users_.clear();
    endRemoveRows();
}