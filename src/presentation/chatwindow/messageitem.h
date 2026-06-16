#pragma once

#include <QString>
#include <QDateTime>

#include "core/domain/messagestatus.h"

struct MessageItem {
    QString sender;
    QString content;
    QDateTime timestamp;
    bool is_outgoing;

    MessageStatus status = MessageStatus::Sent;
};

