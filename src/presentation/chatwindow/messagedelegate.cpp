#include "messagedelegate.h"

#include "core/domain/messagestatus.h"
#include "infrastructure/utils/avatarprovider.h"

#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QDateTime>

#include <QDebug>


MessageDelegate::MessageDelegate(AvatarProvider* provider, QObject* parent)
    : QStyledItemDelegate(parent)
    , av_provider_(provider)
{

}


void MessageDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QString text = index.data(Qt::DisplayRole).toString();
    QDateTime time = index.data(Qt::UserRole + 2).toDateTime();
    bool outgoing = index.data(Qt::UserRole + 3).toBool();

    // Optional (for group chats)
    QString sender = index.data(Qt::UserRole + 4).toString();
    bool isGroup = !sender.isEmpty() && !outgoing;

    const auto status = static_cast<MessageStatus>(index.data(Qt::UserRole + 5).toInt());

    const auto sender_id = index.data(Qt::UserRole + 6).toString();

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

    ////////////////////////////////
    QRect avatarRect(
        rect.left() + 5,
        bubbleRect.bottom() - avatar_size_,
        avatar_size_,
        avatar_size_);

    QPixmap pix;
    if (const auto avatar_opt = av_provider_->getImage(sender_id);
        avatar_opt.has_value()) {
        pix = avatar_opt.value();
    } else {
        pix.load(":/avatars/icons/empty_av.png");
    }

    painter->drawPixmap(
        avatarRect,
        pix.scaled(
            avatar_size_,
            avatar_size_,
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation));
///////////////////////////////////////////////
///
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

    if (status != MessageStatus::Sent) {
        // Message status
        QColor statusColor;

        switch (status)
        {
        case MessageStatus::Pending:
            statusColor = QColor(255, 220, 0); // yellow
            break;

        case MessageStatus::Failed:
            statusColor = QColor(220, 0, 0);   // red
            break;
        default: break;
        }

        painter->setBrush(statusColor);
        painter->setPen(Qt::NoPen);

        painter->drawEllipse(bubbleRect.right() - 14, bubbleRect.bottom() - 14, 8, 8);
    }

    painter->restore();
}

// QSize MessageDelegate::sizeHint(const QStyleOptionViewItem& option,
//                              const QModelIndex& index) const
// {
//     QString text = index.data(Qt::DisplayRole).toString();
//     bool outgoing = index.data(Qt::UserRole + 3).toBool();
//     QString sender = index.data(Qt::UserRole + 4).toString();

//     bool isGroup = !sender.isEmpty() && !outgoing;

//     int maxWidth = option.rect.width() > 0
//         ? static_cast<int>(option.rect.width() * 0.6)
//         : 300; // fallback (important!)

//     QFont font = option.font;
//     QFontMetrics fm(font);

//     // 🔹 Text height
//     QRect textRect = fm.boundingRect(0, 0, maxWidth, 0,
//                      Qt::TextWordWrap, text);

//     int height = 10; // top padding

//     // 🔹 Sender (group chat)
//     if (isGroup) {
//         height += fm.height() + 5;
//     }

//     // 🔹 Message text
//     height += textRect.height();

//     // 🔹 Space between text and timestamp
//     height += 5;

//     // 🔹 Timestamp
//     height += fm.height();

//     // 🔹 Bottom padding
//     height += 10;

//     return QSize(option.rect.width(), height);
// }


QSize MessageDelegate::sizeHint(const QStyleOptionViewItem& option,
                                const QModelIndex& index) const
{
    QString text = index.data(Qt::DisplayRole).toString();
    bool outgoing = index.data(Qt::UserRole + 3).toBool();
    QString sender = index.data(Qt::UserRole + 4).toString();

    bool isGroup = !sender.isEmpty() && !outgoing;

    int maxWidth = option.rect.width() > 0
                       ? static_cast<int>(option.rect.width() * 0.6)
                       : 300;

    constexpr int TopPadding = 10;
    constexpr int BottomPadding = 10;
    constexpr int Spacing = 5;
    constexpr int AvatarSize = 40;

    QFontMetrics fm(option.font);

    QRect textRect = fm.boundingRect(
        0, 0,
        maxWidth, 0,
        Qt::TextWordWrap,
        text);

    // Bubble height
    int bubbleHeight = TopPadding;

    if (isGroup)
        bubbleHeight += fm.height() + Spacing;      // sender name

    bubbleHeight += textRect.height();              // message text
    bubbleHeight += Spacing;
    bubbleHeight += fm.height();                    // timestamp
    bubbleHeight += BottomPadding;

    // Row height
    int height = bubbleHeight;

    // Incoming messages in group chat show avatar.
    // Ensure the row is at least as high as the avatar.
    if (isGroup)
        height = std::max(height, AvatarSize + TopPadding + BottomPadding);

    return QSize(option.rect.width(), height);
}
