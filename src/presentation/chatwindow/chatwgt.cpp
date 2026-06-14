#include "chatwgt.h"
#include "ui_chatwgt.h"

#include "core/domain/message.h"
#include "presentation/chatwindow/messagedelegate.h"
#include "mock/mockchatfactory.h"

#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>

ChatWgt::ChatWgt(SendMessageUseCase* send_msgs_uc, QWidget *parent) :
    QWidget(parent),
    send_msgs_uc_(send_msgs_uc),
    ui(new Ui::ChatWgt)
{
    ui->setupUi(this);
    auto timestamp = QDateTime::currentDateTime();

//    auto chat_data = MockChatFactory::create(":/mock_data/src/mock/data/chat_history1.json");

//    auto chat_1 = new ChatHistoryModel{ui->view};
//    chat_1->setChatData(std::move(chat_data));
//    chat_1->addMessage({"Igor", "Hello, World!", timestamp, true});
//    chat_1->addMessage({"Maria", "Hello, World!slslslsslslslsllsslawnfwnwjanlfnwalnwfalnwfalnfwalnwfalnfwalnwfalnwafllnawflnawflnawflnafwlnwf", timestamp, false});
//    chat_1->addMessage({"Igor", "Hi! Who are you?knsdjnsjnsgns", timestamp, true});
//    chat_1->addMessage({"Igor", "Hi! Who are you?", timestamp, false});
//    chat_1->addMessage({"Lexa", "Hi! elfmwlmfw", timestamp, true});
//    chat_1->addMessage({"Igor", "Hi! ,aldwdl,l,wdlwd?", timestamp, false});
//    chat_1->addMessage({"Diana", "Hi! Wh    jnsjnsgns", timestamp, false});
//    chat_1->addMessage({"Igor", "Hi! Who are you?", timestamp, false});

//    auto chat_2 = new ChatHistoryModel{ui->view};
//    auto chat_data2 = MockChatFactory::create(":/mock_data/src/mock/data/chat_history2.json");
//    chat_2->setChatData(std::move(chat_data2));
//    chat_2->addMessage({"Igor", "Hello, World!", timestamp, true});
//    chat_2->addMessage({"Maria", "Hello, World!slslslsslslslsllsslawnfwnwjanlfnwalnwfalnwfalnfwalnwfalnfwalnwfalnwafllnawflnawflnawflnafwlnwf", timestamp, false});
//    chat_2->addMessage({"Igor", "Hi! Who are you?knsdjnsjnsgns", timestamp, true});
//    chat_2->addMessage({"Igor", "Hi! Who are you?", timestamp, false});
//    chat_2->addMessage({"Lexa", "Hi! elfmwlmfw", timestamp, true});
//    chat_2->addMessage({"Igor", "Hi! ,aldwdl,l,wdlwd?", timestamp, false});
//    chat_2->addMessage({"Diana", "Hi! Wh    jnsjnsgns", timestamp, false});
//    chat_2->addMessage({"Igor", "Hi! Who are you?", timestamp, false});

//    chat_models_.append(chat_1);
//    chat_models_.insert(chat_1->getID(), chat_1);
////    chat_models_.append(chat_2);
//    chat_models_.insert(chat_2->getID(), chat_2);

    auto message_delegate = new MessageDelegate{ui->view};

//    ui->view->setModel(chat_1);
    ui->view->setItemDelegate(message_delegate);
    ui->view->setSelectionMode(QAbstractItemView::NoSelection);
    ui->view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setContentsMargins(0,0,0,0);

    connect(ui->view->verticalScrollBar(), &QScrollBar::valueChanged, this, &ChatWgt::isScrollBarInEnd);
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWgt::sendButtonClicked);
}

ChatWgt::~ChatWgt()
{
    delete ui;
}

ChatHistoryModel* ChatWgt::loadChatData(const QString &id, const QString& name) {
    QString path;
    if (id == "30d638ef-9daa-451c-903e-d4cc605aec58") {
        path = ":/mock_data/src/mock/data/chat_history1.json";
    } else if (id == "30d638ef-9daa-451c-903e-d4cc605aec59") {
        path = ":/mock_data/src/mock/data/chat_history2.json";
    }

    auto chat_data = MockChatFactory::create(id, name, path);
    auto model = new ChatHistoryModel{ui->view};
    model->setChatData(std::move(chat_data));

    return model;
}

void ChatWgt::switchChat(const QString& id, const QString& name) {
    auto model = chat_models_.value(id, nullptr);
    if (!model) {
        model = loadChatData(id, name);
        if (!model) {
            QMessageBox::critical(this, "switch chat", "chat does not exist");
            return;
        }
        chat_models_.insert(model->getID(), model);
        ui->view->setModel(model);
    } else {
        ui->view->setModel(model);
    }
    auto message_delegate = new MessageDelegate{ui->view};
    ui->view->setItemDelegate(message_delegate);

    emit updateUnreadMessagesCount(model->getID(), 0);
//    if (model->getUnreadCount() != 0) {
//        model->setUnreadCount(0);
//        emit updateUnreadMessagesCount(model->getID(), 0);
//    }
}

void ChatWgt::isScrollBarInEnd(int value) {
    qDebug() << "void ChatWgt::isScrollBarInEnd(int value)";
    const auto bar = ui->view->verticalScrollBar();
    if (value == bar->maximum()) {
        qDebug() << "void ChatWgt::isScrollBarInEnd: value == max";
//        emit updateUnreadMessagesCount(0);
    }
}

void ChatWgt::sendButtonClicked() {
    Message msg;
    msg.content = ui->msgEdit->toPlainText().toStdString();

    send_msgs_uc_->execute(msg);
}