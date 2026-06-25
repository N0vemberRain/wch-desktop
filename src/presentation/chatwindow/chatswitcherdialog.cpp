#include "chatswitcherdialog.h"

#include <QLineEdit>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QModelIndex>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QCoreApplication>

ChatSwitcherDialog::ChatSwitcherDialog(QAbstractItemModel* source_model, QWidget* parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setModal(true);
    resize(400, 500);

    auto layout = new QVBoxLayout(this);

    search_edit_ = new QLineEdit(this);
    search_edit_->setPlaceholderText("search chats...");
    search_edit_->installEventFilter(this);

    list_view_ = new QListView(this);

    proxy_ = new QSortFilterProxyModel(this);
    proxy_->setSourceModel(source_model);
    proxy_->setFilterCaseSensitivity(Qt::CaseSensitivity::CaseInsensitive);
    proxy_->setFilterRole(Qt::DisplayRole);

    list_view_->setModel(proxy_);

    layout->addWidget(search_edit_);
    layout->addWidget(list_view_);

    list_view_->setSelectionMode(QAbstractItemView::SingleSelection);
    list_view_->setCurrentIndex(proxy_->index(0, 0));
    list_view_->setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    connect(search_edit_, &QLineEdit::textChanged, this, &ChatSwitcherDialog::onSearchChanged);
    connect(list_view_, &QListView::doubleClicked, this, &ChatSwitcherDialog::onActivated);

    connect(search_edit_, &QLineEdit::returnPressed, this, [this]() {
        const auto index = list_view_->currentIndex();
        if (index.isValid()) {
            onActivated(index);
        }
    });
}


void ChatSwitcherDialog::onSearchChanged(const QString& text) {
    proxy_->setFilterFixedString(text);
}

void ChatSwitcherDialog::onActivated(const QModelIndex& index) {
    auto source_index = proxy_->mapToSource(index);
    emit chatSelected(source_index);
    accept();
}

bool ChatSwitcherDialog::eventFilter(QObject *obj, QEvent *e) {
    if (obj == search_edit_ && e->type() == QEvent::KeyPress) {
        const auto key_event = static_cast<QKeyEvent*>(e);
        if (key_event->key() == Qt::Key_Up || key_event->key() == Qt::Key_Down) {
            QCoreApplication::sendEvent(list_view_, key_event);
            return true;
        }
    }

    return QDialog::eventFilter(obj, e);
}
