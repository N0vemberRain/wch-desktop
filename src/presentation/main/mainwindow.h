#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QListView>
#include <QString>

#include "presentation/sidebar/sidebarwidget.h"
#include "presentation/chatwindow/chathistorymodel.h"
#include "presentation/chatwindow/messagedelegate.h"
#include "presentation/chatwindow/chatwgt.h"
#include "presentation/chat/chatslistwgt.h"

#include "core/usecases/sendmessageusecase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SendMessageUseCase* send_msgs_uc, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToChat(const QModelIndex& index);
    void showChat(const QString& id, const QString& name);
private:
    Ui::MainWindow *ui;

    ChatsListWgt *chats_wgt_;

//    ChatListModel *chats_model_;
//    QListView *list_view_;
//    ChatDelegate *chat_delegate_;

    SidebarWidget *sidebar_;

    ChatHistoryModel* chat_history_model_;
    MessageDelegate* message_delegate_;

    ChatWgt* chat_wgt_;
};
#endif // MAINWINDOW_H
