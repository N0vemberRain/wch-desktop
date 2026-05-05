#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>
#include <QImageReader>
#include <QDebug>
#include <QDateTime>
#include <QShortcut>
#include <QSplitter>

#include "presentation/chatwindow/chatswitcherdialog.h"

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

    list_view_->setModel(chats_model_);
    list_view_->setItemDelegate(chat_delegate_);

    splitter->addWidget(sidebar_);
    splitter->addWidget(list_view_);

//    ui->leftSideLayout->addWidget(sidebar_);
//    ui->leftSideLayout->addWidget(list_view_);

    qDebug() << QImageReader::supportedImageFormats();

    QPixmap p1(":/avatars/1763883703395.jpg");
    qDebug() << "p1: " << (p1.isNull() ? "null" : "not null");
    QPixmap p2(":/avatars/b9cb7bcf741565f868e468fcfcfcf3dd.jpg");
    qDebug() << "p2: " << (p2.isNull() ? "null" : "not null");
    chats_model_->addChat({"Igor", "Hello!", 1, p1});
    chats_model_->addChat({"Lisa", "Hi!", 3, p2});

    auto lv = new QListView(this);
//    ui->leftSideLayout->addWidget(lv);
    chat_history_model_ = new ChatHistoryModel{lv};
    message_delegate_ = new MessageDelegate{lv};

    lv->setModel(chat_history_model_);
//    ui->chatHistoryListView->setModel(chat_history_model_);
    lv->setItemDelegate(message_delegate_);

    lv->setSelectionMode(QAbstractItemView::NoSelection);
    lv->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    splitter->addWidget(lv);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 4);

    auto *layout = new QHBoxLayout(central);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(splitter);

    auto timestamp = QDateTime::currentDateTime();
    chat_history_model_->addMessage({"Igor", "Hello, World!", timestamp, true});
    chat_history_model_->addMessage({"Maria", "Hello, World!slslslsslslslsllsslawnfwnwjanlfnwalnwfalnwfalnfwalnwfalnfwalnwfalnwafllnawflnawflnawflnafwlnwf", timestamp, false});
    chat_history_model_->addMessage({"Igor", "Hi! Who are you?knsdjnsjnsgns", timestamp, true});
    chat_history_model_->addMessage({"Igor", "Hi! Who are you?", timestamp, false});
    chat_history_model_->addMessage({"Lexa", "Hi! elfmwlmfw", timestamp, true});
    chat_history_model_->addMessage({"Igor", "Hi! ,aldwdl,l,wdlwd?", timestamp, false});
    chat_history_model_->addMessage({"Diana", "Hi! Wh    jnsjnsgns", timestamp, false});
    chat_history_model_->addMessage({"Igor", "Hi! Who are you?", timestamp, false});

    qDebug() << "row count: " << chat_history_model_->rowCount();

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
}
