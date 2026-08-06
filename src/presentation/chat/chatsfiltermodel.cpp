#include "chatsfiltermodel.h"

#include "presentation/chat/chatlistmodel.h"

ChatsFilterModel::ChatsFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{}


void ChatsFilterModel::setFilterText(const QString& text) {
    text_ = text;
    invalidateFilter();
}

bool ChatsFilterModel::filterAcceptsRow(
    int source_row,
    const QModelIndex& source_parent
) const {
    auto idx = sourceModel()->index(source_row, 0, source_parent);

    QString name =
        sourceModel()->data(idx, ChatListModel::Roles::Name).toString();

    return name.contains(text_, Qt::CaseInsensitive);
}
