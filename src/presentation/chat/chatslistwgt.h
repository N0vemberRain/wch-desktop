#ifndef CHATSLISTWGT_H
#define CHATSLISTWGT_H

#include <QWidget>

#include "presentation/chat/chatlistmodel.h"

namespace Ui {
class ChatsListWgt;
}

class ChatsListWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatsListWgt(QWidget *parent = nullptr);
    ~ChatsListWgt();

private:
    Ui::ChatsListWgt *ui;

    ChatListModel* model_;
};

#endif // CHATSLISTWGT_H
