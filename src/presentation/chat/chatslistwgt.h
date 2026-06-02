#ifndef CHATSLISTWGT_H
#define CHATSLISTWGT_H

#include <QWidget>

#include "presentation/chat/chatlistmodel.h"
#include "core/domain/chat.h"

namespace Ui {
class ChatsListWgt;
}

class ChatsListWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatsListWgt(QWidget *parent = nullptr);
    ~ChatsListWgt();

public slots:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);
private slots:
    void onItemClicked(const QModelIndex& index);

signals:
    void showChat(const QString& chat_id, const QString& chat_name);
private:
    Ui::ChatsListWgt *ui;

    ChatListModel* model_;
};

#endif // CHATSLISTWGT_H
