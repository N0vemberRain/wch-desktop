#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

struct Message {
    QString sender;
    QString content;
    QDateTime timestamp;
    bool is_outgoing;
};

#endif // MESSAGE_H
