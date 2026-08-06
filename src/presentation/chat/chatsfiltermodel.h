#pragma once

#include <QSortFilterProxyModel>
#include <QString>

class ChatsFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ChatsFilterModel(QObject *parent = nullptr);

    void setFilterText(const QString& text);

protected:
    bool filterAcceptsRow(
        int sourceRow,
        const QModelIndex& sourceParent
    ) const override;

private:
    QString text_;
};

