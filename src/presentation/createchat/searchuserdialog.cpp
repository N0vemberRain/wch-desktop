#include "searchuserdialog.h"
#include "ui_searchuserdialog.h"

#include "core/usecases/searchusersusecase.h"
#include "core/domain/users_search_filter.h"
#include "presentation/createchat/searchusersmodel.h"
#include "presentation/createchat/usersummarydelegate.h"

#include <QKeyEvent>
#include <QMovie>

SearchUserDialog::SearchUserDialog(SearchUsersUseCase& uc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchUserDialog)
    , uc_(uc)
{
    ui->setupUi(this);

    connect(ui->findButton, &QPushButton::clicked, this,
            &SearchUserDialog::onFindClicked);
    connect(&uc_, &SearchUsersUseCase::requestFinished, this,
            &SearchUserDialog::onSearchFinished);

    ui->searchLineEdit->installEventFilter(this);
    ui->searchLineEdit->setFocus();

    model_ = new SearchUsersModel(ui->usersListView);
    ui->usersListView->setModel(model_);

    auto user_summary_delegate = new UserSummaryDelegate(ui->usersListView);
    ui->usersListView->setItemDelegate(user_summary_delegate);

    setupLoadLabel();
}

SearchUserDialog::~SearchUserDialog()
{
    delete ui;
}

void SearchUserDialog::setupLoadLabel() {
    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadLabel->setFixedSize(40, 40);
    ui->loadLabel->setMovie(gif);
    ui->loadLabel->setScaledContents(true);
    ui->loadLabel->hide();
    ui->verticalLayout->setAlignment(ui->loadLabel, Qt::AlignCenter);
}

bool SearchUserDialog::eventFilter(QObject* obj, QEvent* e) {
    if (obj == ui->searchLineEdit && e->type() == QEvent::KeyPress) {
        const auto key_event = static_cast<QKeyEvent*>(e);
        if (key_event->key() == Qt::Key_Enter) {
            if (!(key_event->modifiers() & Qt::ShiftModifier)) {
                onFindClicked();
                return true;
            }
        }
    }

    return QWidget::eventFilter(obj, e);
}

void SearchUserDialog::onFindClicked() {
    const auto text = ui->searchLineEdit->text();
    if (text.isEmpty())
        return;

    UsersSearchFilter filter;
    filter.name = text.toStdString();
    filter.email = filter.name;

    uc_.execute(filter);
    startLoadAnim();
}

void SearchUserDialog::onSearchFinished(std::expected<std::list<UserSummary>, Error> res) {
    if (!res.has_value()) {
        return;
    }

    model_->clear();

    for (const auto& u : res.value()) {
        model_->addUser({
            QString::fromStdString(u.id),
            QString::fromStdString(u.name),
            QString::fromStdString(u.email),
        });
    }

    stopLoadAnim();
}

void SearchUserDialog::startLoadAnim() {
    ui->loadLabel->show();
    ui->loadLabel->movie()->start();
}

void SearchUserDialog::stopLoadAnim() {
    ui->loadLabel->movie()->stop();
    ui->loadLabel->hide();
}