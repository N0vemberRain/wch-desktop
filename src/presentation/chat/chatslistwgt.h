#pragma once

#include <QWidget>

#include <list>

#include "core/domain/chat.h"

class QString;
class QModelIndex;
class ChatListModel;
class QPoint;

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
    void updateChat(Chat&& chat, QPixmap new_av);
    void updateChat(Chat&& chat);
public slots:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);
private slots:
    void onItemClicked(const QModelIndex& index);
    void onContextMenuRequested(const QPoint& pos);
    void onOpenChatInfo(const QModelIndex& idx);
signals:
    void showChat(const QString& chat_id, const QString& chat_name);
    void showChatInfo(const Chat& c);
private:
    Ui::ChatsListWgt *ui;

    ChatListModel* model_;
};
