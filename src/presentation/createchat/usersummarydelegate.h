#pragma once

#include <QStyledItemDelegate>

class QModelIndex;
class QPainter;

class UserSummaryDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit UserSummaryDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

