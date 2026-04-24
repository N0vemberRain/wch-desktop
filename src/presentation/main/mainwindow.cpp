#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chats_dock_wgt_ = new QDockWidget("chats", this);

    list_view_ = new QListView(chats_dock_wgt_);
    chats_model_ = new ChatListModel(list_view_);
    list_view_->setModel(chats_model_);

    chats_dock_wgt_->setWidget(list_view_);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, chats_dock_wgt_);

    chats_model_->addChat({"Igor", "Hello!", 1});
    chats_model_->addChat({"Lisa", "Hi!", 1});
}

MainWindow::~MainWindow()
{
    delete ui;
}

