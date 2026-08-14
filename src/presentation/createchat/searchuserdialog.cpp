#include "searchuserdialog.h"
#include "ui_searchuserdialog.h"

#include "core/domain/user.h"
#include "core/usecases/searchusersusecase.h"
#include "core/usecases/createchatusecase.h"
#include "core/domain/users_search_filter.h"
#include "presentation/createchat/searchusersmodel.h"
#include "presentation/createchat/usersummarydelegate.h"
#include "infrastructure/utils/avatarprovider.h"

#include <QKeyEvent>
#include <QMovie>
#include <QMenu>

SearchUserDialog::SearchUserDialog(
    SearchUsersUseCase& suc,
    CreateChatUseCase& cuc,
    AvatarProvider* av_provider,
    QWidget *parent
)
    : QDialog(parent)
    , ui(new Ui::SearchUserDialog)
    , suc_(suc)
    , cuc_(cuc)
    , av_provider_(av_provider)
{
    assert(av_provider_);
    ui->setupUi(this);

    connect(ui->findButton, &QPushButton::clicked, this,
            &SearchUserDialog::onFindClicked);
    connect(&suc_, &SearchUsersUseCase::requestFinished, this,
            &SearchUserDialog::onSearchFinished);

    ui->searchLineEdit->installEventFilter(this);
    ui->searchLineEdit->setFocus();

    model_ = new SearchUsersModel(ui->usersListView);
    ui->usersListView->setModel(model_);

    auto user_summary_delegate = new UserSummaryDelegate(ui->usersListView);
    ui->usersListView->setItemDelegate(user_summary_delegate);

    setupLoadLabel();
    setupContextMenu();

    connect(av_provider_, &AvatarProvider::getAvatarsFinished, this,
        &SearchUserDialog::onGetAvatarsFinished);
}

SearchUserDialog::~SearchUserDialog()
{
    delete ui;
}

void SearchUserDialog::setupContextMenu() {
    ui->usersListView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
    ui->usersListView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->usersListView, &QListView::customContextMenuRequested,
            this, &SearchUserDialog::onContextMenuRequested);
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

    suc_.execute(filter);
    startLoadAnim();
}

void SearchUserDialog::onSearchFinished(std::expected<std::list<UserSummary>, Error> res) {
    if (!res.has_value()) {
        return;
    }

    model_->clear();

    QStringList ids;
    for (const auto& u : res.value()) {
        model_->addUser({
            QString::fromStdString(u.id),
            QString::fromStdString(u.name),
            QString::fromStdString(u.email),
        });

        ids.append(QString::fromStdString(u.id));
    }

    stopLoadAnim();

    auto avs = av_provider_->getImages(ids);
    if (avs.isEmpty()) {
        return;
    }

    foreach (const auto& pair, avs) {
        model_->addAvatarForUser(pair.first, pair.second);
    }
}

void SearchUserDialog::onGetAvatarsFinished(const QVector<QPair<QString, QPixmap>>& res) {
    foreach (const auto& pair, res) {
        model_->addAvatarForUser(pair.first, pair.second);
    }
}

void SearchUserDialog::startLoadAnim() {
    ui->loadLabel->show();
    ui->loadLabel->movie()->start();
}

void SearchUserDialog::stopLoadAnim() {
    ui->loadLabel->movie()->stop();
    ui->loadLabel->hide();
}

void SearchUserDialog::onContextMenuRequested(const QPoint& pos) {
    const auto idx = ui->usersListView->indexAt(pos);
    if (!idx.isValid())
        return;

    QMenu menu{this};
    auto user_info = menu.addAction("Show User Profile");
    auto create_chat = menu.addAction("Create New Chat");

    auto selected = menu.exec(ui->usersListView->viewport()->mapToGlobal(pos));
    if (selected == user_info) {
        onShowProfile(idx);
        return;
    }
    if (selected == create_chat) {
        onCreateChat(idx);
        return;
    }
}

void SearchUserDialog::onShowProfile(const QModelIndex& idx) {
    const auto id = idx.data(Qt::UserRole + 1).toString();
    const auto name = idx.data(Qt::UserRole + 2).toString();
    const auto email = idx.data(Qt::UserRole + 3).toString();

    QPixmap av = idx.data(Qt::UserRole + 4).value<QPixmap>();

    User u;
    u.id = id.toStdString();
    u.name = name.toStdString();
    u.email = email.toStdString();

    emit showUserProfile(u, av);
}

void SearchUserDialog::onCreateChat(const QModelIndex& idx) {
    const auto id = idx.data(Qt::UserRole + 1).toString().toStdString();
    if (id.empty()) {
        throw std::runtime_error{"SearchUserDialog:onCreateChat: id.empty == true"};
    }

    cuc_.execute(id);
}