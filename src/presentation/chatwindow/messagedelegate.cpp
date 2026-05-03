#include "messagedelegate.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDateTime>

#include <QDebug>

MessageDelegate::MessageDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{

}


void MessageDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
//    painter->save();

//    QString content = index.data(Qt::DisplayRole).toString();
//    QDateTime timestamp = index.data(Qt::UserRole + 2).toDateTime();
//    bool is_outgoing = index.data(Qt::UserRole + 3).toBool();

//    QRect rect = option.rect;

//    int maxWidth = static_cast<int>(rect.width() * 0.6);

//    QFontMetrics fm(option.font);
//    QRect textRect = fm.boundingRect(0, 0, maxWidth, 0,
//                     Qt::TextWordWrap, content);

//    QRect bubbleRect;

//    if (is_outgoing) {
//        bubbleRect = QRect(rect.right() - textRect.width() - 60,
//               rect.top() + 5,
//               textRect.width() + 50,
//               textRect.height() + 20);
//    } else {
//        bubbleRect = QRect(rect.left() + 10,
//               rect.top() + 5,
//               textRect.width() + 50,
//               textRect.height() + 20);
//    }

//    QColor bubbleColor = is_outgoing ? QColor("#4287f5") : QColor("#c1e3cc");

//    painter->setRenderHint(QPainter::Antialiasing);
//    painter->setBrush(bubbleColor);
//    painter->setPen(Qt::NoPen);
//    painter->drawRoundedRect(bubbleRect, 10, 10);

//        int contentTop = bubbleRect.top() + 10;

//    // Text
//    painter->setPen(Qt::black);
//    painter->drawText(bubbleRect.adjusted(10, 10, -10, -10),
//              Qt::TextWordWrap,
//              content);

//    // Timestamp
//    painter->setPen(Qt::gray);
//    QString timeStr = timestamp.toString("hh:mm");

////    painter->drawText(bubbleRect.adjusted(10, 10, -10, -10),
////              Qt::AlignBottom | Qt::AlignRight,
////              timeStr);
//    contentTop += textRect.height() + 5;
//    painter->drawText(bubbleRect.left() + 10,
//                          contentTop + fm.ascent(),
//                          timeStr);

//    painter->restore();


    painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        QString text = index.data(Qt::DisplayRole).toString();
        QDateTime time = index.data(Qt::UserRole + 2).toDateTime();
        bool outgoing = index.data(Qt::UserRole + 3).toBool();

        // Optional (for group chats)
        QString sender = index.data(Qt::UserRole + 4).toString();
        bool isGroup = !sender.isEmpty() && !outgoing;

        QRect rect = option.rect;
        int maxWidth = static_cast<int>(rect.width() * 0.6);

        QFontMetrics fm(option.font);

        // 🔹 Text rect
        QRect textRect = fm.boundingRect(0, 0, maxWidth, 0,
                                         Qt::TextWordWrap, text);

        int bubbleWidth = textRect.width() + 20;
        int bubbleHeight = textRect.height() + 10;

        int yOffset = rect.top() + 5;

        // 🔹 Add space for sender (group chat)
        if (isGroup) {
            bubbleHeight += fm.height() + 5;
        }

        // 🔹 Add space for timestamp BELOW text
        bubbleHeight += fm.height();

        QRect bubbleRect;

        if (outgoing) {
            bubbleRect = QRect(rect.right() - bubbleWidth - 10,
                               yOffset,
                               bubbleWidth,
                               bubbleHeight);
        } else {
            bubbleRect = QRect(rect.left() + 10,
                               yOffset,
                               bubbleWidth,
                               bubbleHeight);
        }

        QColor bubbleColor = outgoing ? QColor("#4287f5") : QColor("#c1e3cc");

        // 🔹 Draw bubble
        painter->setBrush(bubbleColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(bubbleRect, 10, 10);

        int contentTop = bubbleRect.top() + 5;

        // 🔹 Sender name (group chat)
        if (isGroup) {
            painter->setPen(Qt::blue);
            painter->drawText(bubbleRect.left() + 10,
                              contentTop + fm.ascent(),
                              sender);

            contentTop += fm.height() + 5;
        }

        // 🔹 Message text
        painter->setPen(Qt::black);
        QRect messageRect(bubbleRect.left() + 10,
                          contentTop,
                          bubbleRect.width() - 20,
                          textRect.height());

        painter->drawText(messageRect, Qt::TextWordWrap, text);

        contentTop += textRect.height() + 1;

        // 🔹 Timestamp (NOW BELOW TEXT)
        painter->setPen(Qt::gray);
        QString timeStr = time.toString("hh:mm");

        painter->drawText(bubbleRect.left() + 10,
                          contentTop + fm.ascent(),
                          timeStr);

        painter->restore();
}

QSize MessageDelegate::sizeHint(const QStyleOptionViewItem& option,
                             const QModelIndex& index) const
{
//    QString content = index.data(Qt::DisplayRole).toString();

//    QFontMetrics fm(option.font);
//    int maxWidth = static_cast<int>(option.rect.width() * 0.6);

//    QRect rect = fm.boundingRect(0, 0, maxWidth, 0,
//                 Qt::TextWordWrap, content);

//    int height = rect.height() + 30; // padding + timestamp
//    return QSize(option.rect.width(), height);

    QString text = index.data(Qt::DisplayRole).toString();
        bool outgoing = index.data(Qt::UserRole + 3).toBool();
        QString sender = index.data(Qt::UserRole + 4).toString();

        bool isGroup = !sender.isEmpty() && !outgoing;

        int maxWidth = option.rect.width() > 0
            ? static_cast<int>(option.rect.width() * 0.6)
            : 300; // fallback (important!)

        QFont font = option.font;
        QFontMetrics fm(font);

        // 🔹 Text height
        QRect textRect = fm.boundingRect(0, 0, maxWidth, 0,
                                         Qt::TextWordWrap, text);

        int height = 10; // top padding

        // 🔹 Sender (group chat)
        if (isGroup) {
            height += fm.height() + 5;
        }

        // 🔹 Message text
        height += textRect.height();

        // 🔹 Space between text and timestamp
        height += 5;

        // 🔹 Timestamp
        height += fm.height();

        // 🔹 Bottom padding
        height += 10;

        return QSize(option.rect.width(), height);
}
