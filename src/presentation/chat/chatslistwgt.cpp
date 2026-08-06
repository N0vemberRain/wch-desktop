#include "chatslistwgt.h"
#include "ui_chatslistwgt.h"

#include "presentation/chat/chatdelegate.h"
// #include "mock/mockchatfactory.h"

#include "chatlistmodel.h"

#include <QString>
#include <QModelIndex>
#include <QMenu>
#include <QAction>

ChatsListWgt::ChatsListWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatsListWgt)
{
    ui->setupUi(this);

    model_ = new ChatListModel{ui->listView};
    auto delegate = new ChatDelegate{ui->listView};


    // const auto chats = MockChatFactory::getChatList(":/mock_data/src/mock/data/chats_list.json");
    // for (const auto& chat : chats) {
    //     model_->addChat({QString::fromStdString(chat.name),
    //                            QString::fromStdString(chat.last_message),
    //                            chat.unread_count,
    //                            QString::fromStdString(chat.avatar),
    //                            QString::fromStdString(chat.id)});
    // }

    ui->listView->setModel(model_);
    ui->listView->setItemDelegate(delegate);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->listView, &QListView::clicked, this, &ChatsListWgt::onItemClicked);

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, &QListView::customContextMenuRequested,
            this, &ChatsListWgt::onContextMenuRequested);
}

ChatsListWgt::~ChatsListWgt()
{
    delete ui;
}

void ChatsListWgt::onItemClicked(const QModelIndex& index) {
    const auto chat_name = index.data(Qt::UserRole + 1).toString();
    const auto chat_id = index.data(Qt::UserRole + 5).toString();

    emit showChat(chat_id, chat_name);
}

void ChatsListWgt::updateUnreadMessagesCount(const QString& chat_id, int unread) {
    model_->setUnreadMessagesCount(chat_id, unread);
}

void ChatsListWgt::addChat(const Chat& c, QPixmap av) {
    model_->addChat({
        QString::fromStdString(c.name),
        QString::fromStdString(c.last_message),
        c.unread_count,
        !av.isNull() ? av : QPixmap{},
        QString::fromStdString(c.id),
        c.type
    });
}

void ChatsListWgt::addChats(std::list<Chat> chats) {
    for (auto&& c : chats) {
        model_->addChat({
            QString::fromStdString(c.name),
            QString::fromStdString(c.last_message),
            c.unread_count,
            QString::fromStdString(c.avatar),
            QString::fromStdString(c.id),
            c.type
        });
    }
}

void ChatsListWgt::updateChat(Chat&& c, QPixmap new_av) {
    model_->updateChat({
            QString::fromStdString(c.name),
            QString::fromStdString(c.last_message),
            c.unread_count,
            new_av,
            QString::fromStdString(c.id),
            c.type
    });
}

void ChatsListWgt::updateChat(Chat&& chat) {

}

void ChatsListWgt::updateAvatarForChat(const QString& chat_id, QPixmap av) noexcept {
    model_->updateAvatarForChat(chat_id, av);
}

void ChatsListWgt::onContextMenuRequested(const QPoint& pos) {
    auto idx = ui->listView->indexAt(pos);
    if (!idx.isValid()) {
        return;
    }

    QMenu menu{this};
    auto chat_info = menu.addAction("Chat Info");

    auto selected = menu.exec(ui->listView->viewport()->mapToGlobal(pos));
    if (selected == chat_info) {
        onOpenChatInfo(idx);
    }
}

void ChatsListWgt::onOpenChatInfo(const QModelIndex& index) {
    const auto chat_name = index.data(Qt::UserRole + 1).toString();
    const auto chat_id = index.data(Qt::UserRole + 5).toString();
    const auto type = Chat::typeFromInt(index.data(Qt::UserRole + 6).toInt());

    Chat chat;
    chat.name = chat_name.toStdString();
    chat.id = chat_id.toStdString();
    chat.type = type;

    emit showChatInfo(chat);
}