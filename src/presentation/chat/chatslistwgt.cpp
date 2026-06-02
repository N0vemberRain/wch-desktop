#include "chatslistwgt.h"
#include "ui_chatslistwgt.h"

#include "presentation/chat/chatdelegate.h"
#include "mock/mockchatfactory.h"

ChatsListWgt::ChatsListWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatsListWgt)
{
    ui->setupUi(this);

    model_ = new ChatListModel{ui->listView};
    auto delegate = new ChatDelegate{ui->listView};


    const auto chats = MockChatFactory::getChatList(":/mock_data/src/mock/data/chats_list.json");
    for (const auto& chat : chats) {
        model_->addChat({QString::fromStdString(chat.name),
                               QString::fromStdString(chat.last_message),
                               chat.unread_count,
                               QString::fromStdString(chat.avatar),
                               QString::fromStdString(chat.id)});
    }

    ui->listView->setModel(model_);
    ui->listView->setItemDelegate(delegate);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->listView, &QListView::clicked, this, &ChatsListWgt::onItemClicked);
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
