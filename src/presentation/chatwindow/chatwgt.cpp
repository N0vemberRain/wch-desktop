#include "chatwgt.h"
#include "ui_chatwgt.h"

#include "core/domain/message.h"
#include "core/usecases/sendmessageusecase.h"
#include "presentation/chatwindow/chathistorymodel.h"
#include "presentation/chatwindow/messagedelegate.h"
#include "mock/mockchatfactory.h"
#include "utils.h"

#include <QMessageBox>
#include <QScrollBar>
#include <QDebug>
#include <QUuid>
#include <QKeyEvent>

ChatWgt::ChatWgt(AvatarProvider* av_provider, SendMessageUseCase* send_msgs_uc, QWidget *parent) :
    QWidget(parent),
    send_msgs_uc_(send_msgs_uc),
    ui(new Ui::ChatWgt)
{
    ui->setupUi(this);
    auto timestamp = QDateTime::currentDateTime();

    auto message_delegate = new MessageDelegate{av_provider, ui->view};

    ui->view->setItemDelegate(message_delegate);
    ui->view->setSelectionMode(QAbstractItemView::NoSelection);
    ui->view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    setContentsMargins(0,0,0,0);

    connect(ui->view->verticalScrollBar(), &QScrollBar::valueChanged, this, &ChatWgt::isScrollBarInEnd);
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWgt::sendButtonClicked);
    connect(send_msgs_uc_, &SendMessageUseCase::requestFinished, this, &ChatWgt::requestFinished);

    ui->msgEdit->installEventFilter(this);
    ui->msgEdit->setFocus();
}

ChatWgt::~ChatWgt()
{
    qDeleteAll(chat_models_);
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

    ui->msgEdit->clear();
    ui->msgEdit->setFocus();

    emit updateUnreadMessagesCount(model->getID(), 0);
}

void ChatWgt::isScrollBarInEnd(int value) {
    qDebug() << "void ChatWgt::isScrollBarInEnd(int value)";
    const auto bar = ui->view->verticalScrollBar();
    if (value == bar->maximum()) {
        qDebug() << "void ChatWgt::isScrollBarInEnd: value == max";
    }
}

void ChatWgt::sendButtonClicked() {
    Message msg;
    msg.content = ui->msgEdit->toPlainText().trimmed().toStdString();
    if (msg.content.empty()) {
        return;
    }
    msg.id = QUuid::createUuid().toString().toStdString();
    msg.chat_id = getCurrentChatID().toStdString();
    msg.is_outgoing = true;
    msg.status = MessageStatus::Pending;
    msg.created_at = fromQDateTime(QDateTime::currentDateTime());

    send_msgs_uc_->execute(msg);

    addMessage(msg);

    ui->msgEdit->clear();
    ui->msgEdit->setFocus();
}

void ChatWgt::requestFinished(SendMessageResult res) {
    if (res.ok) {
        auto msg = res.message.value();
        auto chat = chat_models_.find(QString::fromStdString(res.message.value().chat_id));
        // chat.value()->addMessage({"aaaaa", QString::fromStdString(msg.content), toQDateTime(msg.created_at), false});
    } else {
        QMessageBox::critical(this, "requestedFinished", QString::fromStdString(res.error));
    }
}

void ChatWgt::addMessage(const Message& msg) {
    chat_models_.value(QString::fromStdString(msg.chat_id))->addMessage({
        QString::fromStdString(msg.sender_id),
        QString::fromStdString(msg.sender_name),
        QString::fromStdString(msg.content),
        toQDateTime(msg.created_at),
        true,
        msg.status
    });
}

QString ChatWgt::getCurrentChatID() const noexcept {
    auto model = ui->view->model();
    if (!model) {
        return {};
    }

    auto chat_model = qobject_cast<ChatHistoryModel*>(model);
    if (!chat_model) {
        return {};
    }

    return chat_model->getID();
}

bool ChatWgt::eventFilter(QObject* obj, QEvent* e) {
    if (obj == ui->msgEdit && e->type() == QEvent::KeyPress) {
        const auto key_event = static_cast<QKeyEvent*>(e);
        if (key_event->key() == Qt::Key_Return || key_event->key() == Qt::Key_Enter) {
            if (!(key_event->modifiers() & Qt::ShiftModifier)) {
                sendButtonClicked();
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, e);
}

void ChatWgt::onCurrentUserChanged(const User& u) {

}
