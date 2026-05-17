#pragma once

#include <QString>
#include <QDateTime>

struct MessageItem {
    QString sender;
    QString content;
    QDateTime timestamp;
    bool is_outgoing;
};

