#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>
#include <QImageReader>
#include <QDebug>
#include <QDateTime>
#include <QShortcut>
#include <QSplitter>
#include <QAbstractAnimation>
#include <QPropertyAnimation>

MainWindow::MainWindow(/*SendMessageUseCase* send_msgs_uc*/std::unique_ptr<AppContext> ctx, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ctx_(std::move(ctx))
{
    ui->setupUi(this);


    auto central = new QWidget{this};
    setCentralWidget(central);

    auto splitter = new QSplitter{Qt::Horizontal, central};

    chats_wgt_ = new ChatsListWgt{this};

//    list_view_ = new QListView(this);
//    chats_model_ = new ChatListModel(list_view_);
//    chat_delegate_ = new ChatDelegate(list_view_);
    sidebar_ = new SidebarWidget(this);
    if (ctx_->isLoading()) {
        sidebar_->startLoadingIcon();
    }

    chat_wgt_ = new ChatWgt{&ctx_->send_msgs_use_case, this};

//    list_view_->setModel(chats_model_);
//    list_view_->setItemDelegate(chat_delegate_);

    splitter->addWidget(sidebar_);
//    splitter->addWidget(list_view_);
    splitter->addWidget(chats_wgt_);

    qDebug() << QImageReader::supportedImageFormats();

    QPixmap p1(":/avatars/1763883703395.jpg");
    qDebug() << "p1: " << (p1.isNull() ? "null" : "not null");
    QPixmap p2(":/avatars/b9cb7bcf741565f868e468fcfcfcf3dd.jpg");
    qDebug() << "p2: " << (p2.isNull() ? "null" : "not null");

//    const auto chats = MockChatFactory::getChatList(":/mock_data/src/mock/data/chats_list.json");
//    chats_model_->addChat({"Igor", "Hello!", 1, p1});
//    chats_model_->addChat({"Lisa", "Hi!", 3, p2});
//    for (const auto& chat : chats) {
//        chats_model_->addChat({QString::fromStdString(chat.name),
//                               QString::fromStdString(chat.last_message),
//                               chat.unread_count,
//                               QString::fromStdString(chat.avatar),
//                               QString::fromStdString(chat.id)});
//    }

    splitter->addWidget(chat_wgt_);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 4);

    auto *layout = new QHBoxLayout(central);
    layout->setContentsMargins(3,3,3,3);
    layout->addWidget(splitter);


//    auto chat_switcher_shortcut = new QShortcut{QKeySequence{"Ctrl+K"}, this};
//    connect(chat_switcher_shortcut, &QShortcut::activated, this, [this]() {
//        ChatSwitcherDialog dialog{chats_model_, this};

//        connect(&dialog, &ChatSwitcherDialog::chatSelected, this, &MainWindow::switchToChat);

//        dialog.exec();
//    });

    connect(chats_wgt_, &ChatsListWgt::showChat, this, &MainWindow::showChat);
    connect(chat_wgt_, &ChatWgt::updateUnreadMessagesCount,
            chats_wgt_, &ChatsListWgt::updateUnreadMessagesCount);

    nav_wgt_ = new NavigationWgt{this};
    // nav_wgt_->setUser(ctx_.session_manager.getSession().getCurrentUser());
    nav_wgt_->setGeometry(-280, 0, 280, height());
    nav_wgt_->move(sidebar_->width(), 0);
    nav_wgt_->hide();

    sidebar_width = sidebar_->width();
    navigation_width = nav_wgt_->width();
    connect(sidebar_, &SidebarWidget::settingsOpen, this, &MainWindow::settingsCalled);

    connect(ctx_.get(), &AppContext::loadingFinished, this, [this](){
        sidebar_->stopLoadingIcon();
        nav_wgt_->setUser(ctx_->session_manager.getSession().getCurrentUser());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchToChat(const QModelIndex& index) {
    qDebug() << "switching to the chat " << index.data(Qt::UserRole + 1);
//    chat_wgt_->switchChat(index.data(Qt::UserRole + 5).toString());
}

void MainWindow::showChat(const QString& id, const QString& name) {
    chat_wgt_->switchChat(id, name);
}

void MainWindow::showNavigation() {
    // auto *animation = new QPropertyAnimation(nav_wgt_, "pos", this);

    // animation->setDuration(200);
    // nav_wgt_->move(sidebar_->width(), 0);
    // animation->setStartValue(QPoint(-nav_wgt_->width(), 0));
    // animation->setEndValue(QPoint(0, 0));

    // nav_wgt_->show();
    // animation->start(QAbstractAnimation::DeleteWhenStopped);

    auto *animation = new QPropertyAnimation(nav_wgt_, "pos", this);

    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    // Hidden position: only the sidebar is visible
    animation->setStartValue(QPoint(sidebar_width - navigation_width, 0));

    // Visible position: drawer starts immediately after sidebar
    animation->setEndValue(QPoint(sidebar_width, 0));

    nav_wgt_->show();

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::hideNavigation() {
    // auto *animation = new QPropertyAnimation(nav_wgt_, "pos", this);

    // animation->setDuration(200);
    // nav_wgt_->move(sidebar_->width() - nav_wgt_->width(), 0);
    // animation->setStartValue(nav_wgt_->pos());
    // animation->setEndValue(QPoint(-nav_wgt_->width(), 0));

    // connect(animation, &QPropertyAnimation::finished,
    //         nav_wgt_, &QWidget::hide);

    // animation->start(QAbstractAnimation::DeleteWhenStopped);

    auto *animation = new QPropertyAnimation(nav_wgt_, "pos", this);

    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::InCubic);

    animation->setStartValue(nav_wgt_->pos());
    animation->setEndValue(QPoint(sidebar_width - navigation_width, 0));

    connect(animation, &QPropertyAnimation::finished,
            nav_wgt_, &QWidget::hide);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::settingsCalled() {
    if (nav_wgt_->isHidden()) {
        showNavigation();
    } else {
        hideNavigation();
    }
}

void MainWindow::resizeEvent(QResizeEvent* e) {
    QMainWindow::resizeEvent(e);

    nav_wgt_->setFixedHeight(height());
}