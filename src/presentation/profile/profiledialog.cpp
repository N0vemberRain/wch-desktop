#include "profiledialog.h"
#include "ui_profiledialog.h"

#include "core/domain/user.h"
#include "core/usecases/updateprofileusecase.h"
#include "presentation/profile/avatarwgt.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMovie>

ProfileDialog::ProfileDialog(UpdateProfileUseCase& uc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProfileDialog)
    , uc_(uc)
{
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &ProfileDialog::onAvatarClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &ProfileDialog::onSaveClicked);

    connect(&uc_, &UpdateProfileUseCase::requestFinished,
            this, &ProfileDialog::onProfileChanged);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadLabel->setFixedSize(40, 40);
    ui->loadLabel->setMovie(gif);
    ui->loadLabel->setScaledContents(true);
    ui->loadLabel->hide();
    ui->verticalLayout->setAlignment(ui->loadLabel, Qt::AlignCenter);
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

void ProfileDialog::setUser(const User& u) noexcept {
    ui->displayNameEdit->setText(QString::fromStdString(u.name));
    ui->emailEdit->setText(QString::fromStdString(u.email));
    ui->userNameEdit->setText(QString::fromStdString(u.name));

    QPixmap avatar{QString::fromStdString(u.avatar_url)};
    ui->avatarWgt->setImage(avatar);
}

void ProfileDialog::onAvatarClicked() {
    const auto filename =
        QFileDialog::getOpenFileName(
                            this,
                            tr("Choose avatar"),
                            QString(),
                            tr("Images (*.png *.jpg *.jpeg *.bmp *.webp)"));

    if (filename.isEmpty()) {
        return;
    }

    QPixmap avatar{filename};
    if (avatar.isNull()) {
        return;
    }

    ui->avatarWgt->setImage(avatar);
    new_avatar_path_ = filename;
    emit avatarChanged(filename);
}

void ProfileDialog::onSaveClicked() {
    User u;
    u.name = ui->userNameEdit->text().toStdString();
    u.email = ui->emailEdit->text().toStdString();
    u.avatar_url = new_avatar_path_.toStdString();

    uc_.execute(u);

    startLoadAnim();
}

void ProfileDialog::onProfileChanged(std::expected<User, Error> res) {
    stopLoadAnim();
    if (res.has_value()) {
        setUser(*res);
    } else {
        // User u;
        // u.name = "Igor";
        // u.avatar_url = new_avatar_path_.toStdString();
        // setUser(u);
        ui->errLabel->setText(QString::fromStdString(res.error().msg));
    }
}

void ProfileDialog::startLoadAnim() {
    ui->loadLabel->show();
    ui->loadLabel->movie()->start();
}

void ProfileDialog::stopLoadAnim() {
    ui->loadLabel->movie()->stop();
    ui->loadLabel->hide();
}