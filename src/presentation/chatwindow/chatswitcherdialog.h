#pragma once

#include <QDialog>

class QAbstractItemModel;
class QModelIndex;
class QLineEdit;
class QListView;
class QSortFilterProxyModel;
class QEvent;

class ChatSwitcherDialog : public QDialog
{
    Q_OBJECT
public:
    ChatSwitcherDialog(QAbstractItemModel* source_model, QWidget* parent = nullptr);

signals:
    void chatSelected(const QModelIndex& source_index);

protected:
    bool eventFilter(QObject *, QEvent *) override;

private slots:
    void onSearchChanged(const QString& text);
    void onActivated(const QModelIndex& index);
private:
    QLineEdit* search_edit_;
    QListView* list_view_;
    QSortFilterProxyModel* proxy_;
};

