#include "chatslistwgt.h"
#include "ui_chatslistwgt.h"

ChatsListWgt::ChatsListWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatsListWgt)
{
    ui->setupUi(this);
}

ChatsListWgt::~ChatsListWgt()
{
    delete ui;
}
