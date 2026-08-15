#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "presentation/profile/profiledialog.h"
#include "presentation/chatinfo/chatinfodialog.h"
#include "presentation/chatinfo/createchatdialog.h"
#include "presentation/createchat/chattypedialog.h"
#include "presentation/createchat/searchuserdialog.h"

#include <QPixmap>
#include <QImageReader>
#include <QDebug>
#include <QDateTime>
#include <QShortcut>
#include <QSplitter>
#include <QAbstractAnimation>
#include <QPropertyAnimation>
#include <QMessageBox>

MainWindow::MainWindow(/*SendMessageUseCase* send_msgs_uc*/std::shared_ptr<AppContext> ctx, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ctx_(std::move(ctx))
{
    ui->setupUi(this);


    auto central = new QWidget{this};
    setCentralWidget(central);

    auto splitter = new QSplitter{Qt::Horizontal, central};

    chats_wgt_ = new ChatsListWgt{this};

    connect(chats_wgt_, &ChatsListWgt::showChatInfo, this, &MainWindow::onShowChatInfo);

    sidebar_ = new SidebarWidget(this);
    if (ctx_->isLoading()) {
        sidebar_->startLoadingIcon();
    }

    chat_wgt_ = new ChatWgt{ctx_->getAvatarProvider(), ctx_->getSendMessageUC(), this};
    connect(ctx_.get(), &AppContext::currentUserChanged,
            this, &MainWindow::onCurrentUserChanged);


    splitter->addWidget(sidebar_);
//    splitter->addWidget(list_view_);
    splitter->addWidget(chats_wgt_);

    qDebug() << QImageReader::supportedImageFormats();

    QPixmap p1(":/avatars/1763883703395.jpg");
    qDebug() << "p1: " << (p1.isNull() ? "null" : "not null");
    QPixmap p2(":/avatars/b9cb7bcf741565f868e468fcfcfcf3dd.jpg");
    qDebug() << "p2: " << (p2.isNull() ? "null" : "not null");

    splitter->addWidget(chat_wgt_);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 4);

    auto *layout = new QHBoxLayout(central);
    layout->setContentsMargins(3,3,3,3);
    layout->addWidget(splitter);


    connect(chats_wgt_, &ChatsListWgt::showChat, this, &MainWindow::showChat);
    connect(chats_wgt_, &ChatsListWgt::chatSelected, this, &MainWindow::onChatSelected);
    connect(chat_wgt_, &ChatWgt::updateUnreadMessagesCount,
            chats_wgt_, &ChatsListWgt::updateUnreadMessagesCount);

    nav_wgt_ = new NavigationWgt{this};
    // nav_wgt_->setUser(ctx_.session_manager.getSession().getCurrentUser());
    nav_wgt_->setGeometry(-280, 0, 280, height());
    nav_wgt_->move(sidebar_->width(), 0);
    nav_wgt_->hide();
    connect(nav_wgt_, &NavigationWgt::profileClicked, this, &MainWindow::currentUserProfileClicked);

    sidebar_width = sidebar_->width();
    navigation_width = nav_wgt_->width();
    connect(sidebar_, &SidebarWidget::settingsOpen, this, &MainWindow::settingsCalled);
    connect(sidebar_, &SidebarWidget::logoutClicked, this, &MainWindow::onLogoutClicked);

    connect(ctx_.get(), &AppContext::loadingProfileFinished, this, [this](){
        // sidebar_->stopLoadingIcon();
        nav_wgt_->setUser(ctx_->getCurrentUser());
        is_profile_loaded_ = true;
        if (is_chats_loaded_) {
            sidebar_->stopLoadingIcon();
        }
    });
    connect(ctx_.get(), &AppContext::loadingAvatarFinished, nav_wgt_, &NavigationWgt::setAvatar);
    connect(ctx_.get(), &AppContext::loadingChatsFinished, this,
            &MainWindow::onLoadingChatsFinished);
    connect(ctx_.get(), &AppContext::loadingAvatarsForChatsFinished, this,
            &MainWindow::onLoadingAvatarsForChatsFinished);
    connect(ctx_.get(), &AppContext::updateChatFinished, this, &MainWindow::onUpdateChatFinished);
    connect(sidebar_, &SidebarWidget::createNewChat, this,
            &MainWindow::onCreateNewChat);
    connect(ctx_.get(), &AppContext::createChatFinished, this,
            &MainWindow::onCreateNewChatFinished);

    connect(ctx_.get(), &AppContext::addParticipantFinished, this,
            &MainWindow::onAddParticipantFinished);
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

void MainWindow::currentUserProfileClicked() {
    ProfileDialog dialog{ctx_->getUpdateUserUC()};
    dialog.setUser(ctx_->getCurrentUser());
    auto img = nav_wgt_->getUserAvatar();
    if (!img.isNull()) {
        dialog.setAvatar(img);
    }

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "ProfileDialog accepted";
    }
}

void MainWindow::onShowUserProfile(const User& u, QPixmap av) {
    ProfileDialog dialog{ctx_->getUpdateUserUC(), ProfileDialog::Type::Show};
    dialog.setUser(u);
    if (!av.isNull()) {
        dialog.setAvatar(av);
    }

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "ProfileDialog accepted";
    }

}

void MainWindow::onShowChatInfo(const Chat& c, QPixmap chat_av) {
    ChatInfoDialog dialog{
        ctx_->getAvatarProvider(),
        ctx_->getUpdateChatUC(),
        ctx_->getLoadParticipantsUC(),
        c
    };
    if (!chat_av.isNull()) {
        dialog.setAvatar(chat_av);
    }

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "ProfileDialog accepted";
    }
}

void MainWindow::onCurrentUserChanged(const User& u) {
    chat_wgt_->onCurrentUserChanged(u);
    nav_wgt_->setUser(u);
}

void MainWindow::onLoadingChatsFinished(std::expected<std::list<Chat>, Error> res) {
    if (!res.has_value()) {
        QMessageBox::critical(nullptr, "Load chats",
            QString::fromStdString(res.error().msg));

        return;
    }

    chats_wgt_->addChats(res.value());
    is_chats_loaded_ = true;
    if (is_profile_loaded_) {
        sidebar_->stopLoadingIcon();
    }
}

void MainWindow::onUpdateChatFinished(Chat chat, QPixmap new_av) {
    chats_wgt_->updateChat(std::move(chat), new_av);
}

void MainWindow::onLoadingAvatarsForChatsFinished(const QHash<QString, QPixmap>& avs) {
    foreach(const auto& key, avs.keys()) {
        chats_wgt_->updateAvatarForChat(key, avs[key]);
    }
}

void MainWindow::onCreateNewChat() {
    ChatTypeDialog dialog{};
    if (dialog.exec() == QDialog::Accepted) {
        switch (dialog.getChosenType()) {
        case Chat::Type::Direct: {
            SearchUserDialog search_user{
                ctx_->getSearchUsersUC(),
                ctx_->getCreateChatUC(),
                ctx_->getAvatarProvider()
            };

            connect(&search_user, &SearchUserDialog::showUserProfile, this,
                    &MainWindow::onShowUserProfile);
            connect(&search_user, &SearchUserDialog::addUserToChat, this,
                    &MainWindow::onAddUserToChat);
            search_user.exec();
            return;
        }
        case Chat::Type::Group: {
            CreateChatDialog create_dialog{ctx_->getCreateChatUC()};
            create_dialog.exec();
            return;
        }
        case Chat::Type::Unknown: {
            QMessageBox::warning(nullptr, "Choose chat's type", "Choose one type from available");
        }
        }
    }
}

void MainWindow::onCreateNewChatFinished(const Chat& chat, std::optional<QPixmap> av_opt) {
    chats_wgt_->addChat(chat, av_opt.has_value() ? av_opt.value() : QPixmap{});
}

void MainWindow::onAddUserToChat(const QString& user_id) {
    selected_user_id_ = user_id;

    chats_wgt_->startChatSelection(ChatsListWgt::SelectionMode::SelectGroupChat);
    chats_wgt_->setFocus();
}

void MainWindow::onChatSelected(const QString& chat_id) {
    qDebug() << "Add user " << selected_user_id_ << " to chat " << chat_id << "\n";

    ctx_->getAddParticipantUC().execute(
        chat_id.toStdString(),
        selected_user_id_.toStdString(),
        ChatParticipant::Role::Admin
    );
}

void MainWindow::onAddParticipantFinished(std::optional<Error> res) {
    if (res.has_value()) {
        ui->statusbar->showMessage(QString::fromStdString(res.value().msg), 10000);
    } else {
        ui->statusbar->showMessage(QString{"User has been added to chat"}, 10000);
    }
}

void MainWindow::onLogoutClicked() {
    emit logoutRequested();
}