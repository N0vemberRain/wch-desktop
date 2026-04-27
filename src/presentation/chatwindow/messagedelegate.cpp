#include "messagedelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDateTime>

MessageDelegate::MessageDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}


void MessageDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    QString content = index.data(Qt::DisplayRole).toString();
    bool is_outgoing = index.data(Qt::UserRole + 2).toBool();
    QDateTime timestamp = index.data(Qt::UserRole + 3).toDateTime();

    QRect rect = option.rect;

    int maxWidth = static_cast<int>(rect.width() * 0.6);

    QFontMetrics fm(option.font);
    QRect textRect = fm.boundingRect(0, 0, maxWidth, 0,
                     Qt::TextWordWrap, content);

    QRect bubbleRect;

    if (is_outgoing) {
    bubbleRect = QRect(rect.right() - textRect.width() - 30,
               rect.top() + 5,
               textRect.width() + 20,
               textRect.height() + 20);
    } else {
    bubbleRect = QRect(rect.left() + 10,
               rect.top() + 5,
               textRect.width() + 20,
               textRect.height() + 20);
    }

    QColor bubbleColor = is_outgoing ? QColor("#DCF8C6") : QColor("#FFFFFF");

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(bubbleColor);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(bubbleRect, 10, 10);

    // Text
    painter->setPen(Qt::black);
    painter->drawText(bubbleRect.adjusted(10, 10, -10, -10),
              Qt::TextWordWrap,
              content);

    // Timestamp
    painter->setPen(Qt::gray);
    QString timeStr = timestamp.toString("hh:mm");

    painter->drawText(bubbleRect.adjusted(10, 10, -10, -10),
              Qt::AlignBottom | Qt::AlignRight,
              timeStr);

    painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem& option,
                             const QModelIndex& index) const
{
    QString content = index.data(Qt::DisplayRole).toString();

    QFontMetrics fm(option.font);
    int maxWidth = static_cast<int>(option.rect.width() * 0.6);

    QRect rect = fm.boundingRect(0, 0, maxWidth, 0,
                 Qt::TextWordWrap, content);

    int height = rect.height() + 30; // padding + timestamp
    return QSize(option.rect.width(), height);
}
