#pragma once

#include <QStyledItemDelegate>

class QModelIndex;
class QPainter;

class ParticipantDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ParticipantDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};

