#ifndef CHATWGT_H
#define CHATWGT_H

#include <QWidget>
#include <QVector>
#include <QListView>
#include <QModelIndex>

#include "core/usecases/sendmessageusecase.h"
#include "presentation/chatwindow/chathistorymodel.h"

namespace Ui {
class ChatWgt;
}

class ChatWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWgt(SendMessageUseCase* send_msgs_uc, QWidget *parent = nullptr);
    ~ChatWgt();

    QString getCurrentChatID() const noexcept;
public slots:
    void switchChat(const QString& id, const QString& name);

signals:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);

private slots:
    void isScrollBarInEnd(int value);
    void sendButtonClicked();
    void requestFinished(SendMessageResult res);
private:
    void addMessage(const Message& msg);

    ChatHistoryModel* loadChatData(const QString& id, const QString& name);

    Ui::ChatWgt *ui;

    QHash<QString, ChatHistoryModel*> chat_models_;
    QListView view_;

    SendMessageUseCase* send_msgs_uc_;
};

#endif // CHATWGT_H
