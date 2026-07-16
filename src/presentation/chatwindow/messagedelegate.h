#pragma once

#include <QStyledItemDelegate>

class AvatarProvider;

class MessageDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MessageDelegate(AvatarProvider* avatar_provider,
                             QObject* parent = nullptr);

    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

private:
    AvatarProvider* av_provider_;

    const int avatar_size_ = 40;
    const int bubble_spacing_ = 8;
};
