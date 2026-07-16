#pragma once

#include "core/domain/messagestatus.h"

#include <QString>
#include <QDateTime>

struct MessageItem {
    QString sender_id;
    QString sender;
    QString content;
    QDateTime timestamp;
    bool is_outgoing;

    MessageStatus status = MessageStatus::Sent;
};

