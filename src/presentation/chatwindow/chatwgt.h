#pragma once

#include <QWidget>
#include <QString>
#include <QHash>

struct Message;
struct SendMessageResult;
class User;
class SendMessageUseCase;
class ChatHistoryModel;
class AvatarProvider;

class QEvent;

namespace Ui {
class ChatWgt;
}

class ChatWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWgt(AvatarProvider* av_provider,
                    SendMessageUseCase* send_msgs_uc,
                    QWidget *parent = nullptr);
    ~ChatWgt();

    QString getCurrentChatID() const noexcept;
public slots:
    void switchChat(const QString& id, const QString& name);
    void onCurrentUserChanged(const User& u);
signals:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);

private slots:
    void isScrollBarInEnd(int value);
    void sendButtonClicked();
    void requestFinished(SendMessageResult res);
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
private:
    void addMessage(const Message& msg);

    ChatHistoryModel* loadChatData(const QString& id, const QString& name);

    Ui::ChatWgt *ui;

    QHash<QString, ChatHistoryModel*> chat_models_;
    SendMessageUseCase* send_msgs_uc_;
};
