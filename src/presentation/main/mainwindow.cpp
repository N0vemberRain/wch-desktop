#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPixmap>
#include <QImageReader>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chats_dock_wgt_ = new QDockWidget("chats", this);

    list_view_ = new QListView(chats_dock_wgt_);
    chats_model_ = new ChatListModel(list_view_);
    chat_delegate_ = new ChatDelegate(list_view_);
    list_view_->setModel(chats_model_);
    list_view_->setItemDelegate(chat_delegate_);

    chats_dock_wgt_->setWidget(list_view_);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, chats_dock_wgt_);

    qDebug() << QImageReader::supportedImageFormats();

    QPixmap p1(":/avatars/1763883703395.jpg");
    qDebug() << "p1: " << (p1.isNull() ? "null" : "not null");
    QPixmap p2(":/avatars/b9cb7bcf741565f868e468fcfcfcf3dd.jpg");
    qDebug() << "p2: " << (p2.isNull() ? "null" : "not null");
    chats_model_->addChat({"Igor", "Hello!", 1, p1});
    chats_model_->addChat({"Lisa", "Hi!", 3, p2});
}

MainWindow::~MainWindow()
{
    delete ui;
}

