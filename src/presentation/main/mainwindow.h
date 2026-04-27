#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QListView>
#include <QString>

#include "presentation/chat/chatlistmodel.h"
#include "presentation/chat/chatdelegate.h"
#include "presentation/sidebar/sidebarwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ChatListModel *chats_model_;
    QListView *list_view_;
    ChatDelegate *chat_delegate_;

    SidebarWidget *sidebar_;
};
#endif // MAINWINDOW_H
