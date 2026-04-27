#ifndef CHATHISTORYMODEL_H
#define CHATHISTORYMODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "message.h"

class ChatHistoryModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        ContentRole = Qt::UserRole + 1,
        TimestampRole,
        IsOutgoingRole,
    };

    explicit ChatHistoryModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addMessage(const Message& msg) noexcept;
    bool setData(const QModelIndex& idx, const QVariant& value, int role) override;
    bool removeRows(int role, int count, const QModelIndex& parent = QModelIndex()) override;

protected:
    QHash<int, QByteArray> roleNames() const override;
private:
    QVector<Message> messages_;
};

#endif // CHATHISTORYMODEL_H
