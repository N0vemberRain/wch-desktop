#pragma once

#include <QStyledItemDelegate>

class QModelIndex;
class QPainter;

class ChatDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ChatDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    void setSelectedColor(QColor color) {
        selected_color_ = color;
    }
    void unsetSelectedColor() {
        selected_color_ = "red";
    }
private:
    QColor selected_color_ {"red"};
};