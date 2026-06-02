#ifndef CHATWGT_H
#define CHATWGT_H

#include <QWidget>
#include <QVector>
#include <QListView>
#include <QModelIndex>

#include "presentation/chatwindow/chathistorymodel.h"

namespace Ui {
class ChatWgt;
}

class ChatWgt : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWgt(QWidget *parent = nullptr);
    ~ChatWgt();

public slots:
    void switchChat(const QString& id, const QString& name);

signals:
    void updateUnreadMessagesCount(const QString& chat_id, int unread);

private slots:
    void isScrollBarInEnd(int value);
private:
    ChatHistoryModel* loadChatData(const QString& id, const QString& name);

    Ui::ChatWgt *ui;

    QHash<QString, ChatHistoryModel*> chat_models_;
    QListView view_;
};

#endif // CHATWGT_H
