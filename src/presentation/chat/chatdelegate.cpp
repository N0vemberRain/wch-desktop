#include "chatdelegate.h"
#include <QPainter>
#include <QApplication>

ChatDelegate::ChatDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void ChatDelegate::paint(QPainter *painter,
                         const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    QRect rect = option.rect;

    // --- Selection background ---
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, option.palette.highlight());
    }

    // --- Fetch data ---
    QString name = index.data(Qt::UserRole + 1).toString();
    QString message = index.data(Qt::UserRole + 2).toString();
    int unread = index.data(Qt::UserRole + 3).toInt();

    QPixmap avatar = index.data(Qt::UserRole + 4).value<QPixmap>();

    // --- Layout constants ---
    int margin = 10;
    int avatarSize = 40;


    QRect avatarRect(rect.left() + margin,
                     rect.top() + (rect.height() - avatarSize) / 2,
                     avatarSize,
                     avatarSize);

    int textLeft = avatarRect.right() + margin;
    int textWidth = rect.width() - textLeft - 50;

    QRect nameRect(textLeft, rect.top() + 8, textWidth, 20);
    QRect msgRect(textLeft, rect.top() + 28, textWidth, 18);

    // --- Avatar (circle) ---
    if (!avatar.isNull()) {
        QPainterPath path;
        path.addEllipse(avatarRect);

        painter->setClipPath(path);
        painter->drawPixmap(avatarRect,
                avatar.scaled(avatarRect.size(),
                          Qt::KeepAspectRatioByExpanding,
                          Qt::SmoothTransformation));
        painter->setClipping(false);
    } else {
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setBrush(QColor("#cccccc"));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(avatarRect);
    }
    // Optional: first letter
    painter->setPen(Qt::black);
    QFont avatarFont = option.font;
    avatarFont.setBold(true);
    painter->setFont(avatarFont);
    painter->drawText(avatarRect, Qt::AlignCenter, name.left(1).toUpper());

    // --- Name (bold if unread) ---
    QFont nameFont = option.font;
    nameFont.setBold(unread > 0);
    painter->setFont(nameFont);
    painter->setPen(Qt::black);
    painter->drawText(nameRect, Qt::AlignLeft | Qt::AlignVCenter, name);

    // --- Message ---
    painter->setFont(option.font);
    painter->setPen(Qt::gray);
    painter->drawText(msgRect, Qt::AlignLeft | Qt::AlignVCenter, message);

    // --- Unread badge ---
    if (unread > 0) {
        int badgeSize = 20;

        QRect badgeRect(rect.right() - badgeSize - margin,
                        rect.top() + (rect.height() - badgeSize) / 2,
                        badgeSize,
                        badgeSize);

        painter->setBrush(QColor("#2AABEE")); // Telegram-like blue
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(badgeRect);

        painter->setPen(Qt::white);
        QFont badgeFont = option.font;
        badgeFont.setBold(true);
        painter->setFont(badgeFont);
        painter->drawText(badgeRect, Qt::AlignCenter, QString::number(unread));
    }

    painter->restore();
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &,
                             const QModelIndex &) const
{
    return QSize(0, 60); // fixed row height
}
