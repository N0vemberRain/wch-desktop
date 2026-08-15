#pragma once

#include <QWidget>
#include <QTimer>

#include <list>

#include "core/domain/chat.h"

class ChatsFilterModel;

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
    enum class SelectionMode {
        Normal,
        SelectGroupChat,
    };


    explicit ChatsListWgt(QWidget *parent = nullptr);
    ~ChatsListWgt();

    void addChat(const Chat& chat, QPixmap av = {});
    void addChats(std::list<Chat> chats);
    void updateChat(Chat&& chat, QPixmap new_av);
    void updateChat(Chat&& chat);
    void updateAvatarForChat(const QString& chat_id, QPixmap av) noexcept;

    void startChatSelection(SelectionMode mode);
    void stopChatSelection();
public slots:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);
private slots:
    void onItemClicked(const QModelIndex& index);
    void onContextMenuRequested(const QPoint& pos);
    void onOpenChatInfo(const QModelIndex& idx);

    void performSearch();

    void openChat(const QModelIndex& idx);
    void selectGroupChat(const QModelIndex& idx);
signals:
    void showChat(const QString& chat_id, const QString& chat_name);
    void showChatInfo(const Chat& c, QPixmap chat_av);
    void chatSelected(const QString& chat_id);
private:
    Ui::ChatsListWgt *ui;

    ChatListModel* model_;
    QTimer search_timer_;

    ChatsFilterModel* proxy_;

    SelectionMode selection_mode_ {SelectionMode::Normal};

    int n {10};
};
