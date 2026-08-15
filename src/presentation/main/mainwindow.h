#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QListView>
#include <QString>
#include <QResizeEvent>

#include <memory>

#include "presentation/sidebar/sidebarwidget.h"
#include "presentation/chatwindow/chathistorymodel.h"
#include "presentation/chatwindow/messagedelegate.h"
#include "presentation/chatwindow/chatwgt.h"
#include "presentation/chat/chatslistwgt.h"
#include "presentation/navigation/navigationwgt.h"

#include "core/usecases/sendmessageusecase.h"

#include "app/appcontext.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SendMessageUseCase* send_msgs_uc, QWidget *parent = nullptr);
    explicit MainWindow(std::shared_ptr<AppContext> ctx, QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent* e) override;

signals:
    void logoutRequested();
private slots:
    void switchToChat(const QModelIndex& index);
    void showChat(const QString& id, const QString& name);

    void showNavigation();
    void hideNavigation();

    void settingsCalled();
    void currentUserProfileClicked();
    void onShowChatInfo(const Chat& c, QPixmap chat_av);

    void onCurrentUserChanged(const User& u);
    void onUpdateChatFinished(Chat chat, QPixmap new_av);

    void onLoadingChatsFinished(std::expected<std::list<Chat>, Error> res);
    void onLoadingAvatarsForChatsFinished(const QHash<QString, QPixmap>& avs);

    void onShowUserProfile(const User& u, QPixmap av);

    void onCreateNewChat();
    void onCreateNewChatFinished(const Chat& chat, std::optional<QPixmap> av_opt);
    // Store selected user id to tmp variable in order to add the user later
    void onAddUserToChat(const QString& user_id);
    // Send a request to the chats service in order to add the user to the chat
    void onChatSelected(const QString& chat_id);
    void onAddParticipantFinished(std::optional<Error> res);

    void onLogoutClicked();
private:
    Ui::MainWindow *ui;
    std::shared_ptr<AppContext> ctx_;

    ChatsListWgt *chats_wgt_;

//    ChatListModel *chats_model_;
//    QListView *list_view_;
//    ChatDelegate *chat_delegate_;

    SidebarWidget *sidebar_;

    ChatHistoryModel* chat_history_model_;
    MessageDelegate* message_delegate_;

    ChatWgt* chat_wgt_;


    NavigationWgt* nav_wgt_;

    int sidebar_width;
    int navigation_width;

    bool is_profile_loaded_ {false};
    bool is_chats_loaded_ {false};

    QString selected_user_id_;
};
#endif // MAINWINDOW_H
