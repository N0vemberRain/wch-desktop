#pragma once

#include <QWidget>

#include <list>

#include "core/domain/chat.h"

class QString;
class QModelIndex;
class ChatListModel;

namespace Ui {
class ChatsListWgt;
}

class ChatsListWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatsListWgt(QWidget *parent = nullptr);
    ~ChatsListWgt();

    void addChats(std::list<Chat> chats);
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
