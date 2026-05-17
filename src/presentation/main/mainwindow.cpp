#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>
#include <QImageReader>
#include <QDebug>
#include <QDateTime>
#include <QShortcut>
#include <QSplitter>

#include "presentation/chatwindow/chatswitcherdialog.h"
#include "mock/mockchatfactory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto central = new QWidget{this};
    setCentralWidget(central);

    auto splitter = new QSplitter{Qt::Horizontal, central};

    list_view_ = new QListView(this);
    chats_model_ = new ChatListModel(list_view_);
    chat_delegate_ = new ChatDelegate(list_view_);
    sidebar_ = new SidebarWidget(this);

    chat_wgt_ = new ChatWgt{this};

    list_view_->setModel(chats_model_);
    list_view_->setItemDelegate(chat_delegate_);

    splitter->addWidget(sidebar_);
    splitter->addWidget(list_view_);

    qDebug() << QImageReader::supportedImageFormats();

    QPixmap p1(":/avatars/1763883703395.jpg");
    qDebug() << "p1: " << (p1.isNull() ? "null" : "not null");
    QPixmap p2(":/avatars/b9cb7bcf741565f868e468fcfcfcf3dd.jpg");
    qDebug() << "p2: " << (p2.isNull() ? "null" : "not null");

    const auto chats = MockChatFactory::getChatList(":/mock_data/src/mock/data/chats_list.json");
//    chats_model_->addChat({"Igor", "Hello!", 1, p1});
//    chats_model_->addChat({"Lisa", "Hi!", 3, p2});
    for (const auto& chat : chats) {
        chats_model_->addChat({QString::fromStdString(chat.name),
                               QString::fromStdString(chat.last_message),
                               chat.unread_count,
                               QString::fromStdString(chat.avatar),
                               QString::fromStdString(chat.id)});
    }

    splitter->addWidget(chat_wgt_);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 4);

    auto *layout = new QHBoxLayout(central);
    layout->setContentsMargins(3,3,3,3);
    layout->addWidget(splitter);


    auto chat_switcher_shortcut = new QShortcut{QKeySequence{"Ctrl+K"}, this};
    connect(chat_switcher_shortcut, &QShortcut::activated, this, [this]() {
        ChatSwitcherDialog dialog{chats_model_, this};

        connect(&dialog, &ChatSwitcherDialog::chatSelected, this, &MainWindow::switchToChat);

        dialog.exec();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToChat(const QModelIndex& index) {
    qDebug() << "switching to the chat " << index.data(Qt::UserRole + 1);
    chat_wgt_->switchChat(index.data(Qt::UserRole + 5).toString());
}
