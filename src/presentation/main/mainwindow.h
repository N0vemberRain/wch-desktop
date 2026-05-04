#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QListView>
#include <QString>

#include "presentation/chat/chatlistmodel.h"
#include "presentation/chat/chatdelegate.h"
#include "presentation/sidebar/sidebarwidget.h"
#include "presentation/chatwindow/chathistorymodel.h"
#include "presentation/chatwindow/messagedelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToChat(const QModelIndex& index);
private:
    Ui::MainWindow *ui;

    ChatListModel *chats_model_;
    QListView *list_view_;
    ChatDelegate *chat_delegate_;

    SidebarWidget *sidebar_;

    ChatHistoryModel* chat_history_model_;
    MessageDelegate* message_delegate_;
};
#endif // MAINWINDOW_H
