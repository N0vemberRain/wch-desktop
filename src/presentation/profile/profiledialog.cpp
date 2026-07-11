#include "profiledialog.h"
#include "ui_profiledialog.h"

#include "core/domain/user.h"
#include "presentation/profile/avatarwgt.h"

#include <QPixmap>
#include <QFileDialog>

ProfileDialog::ProfileDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProfileDialog)
{
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &ProfileDialog::onAvatarClicked);
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
    emit avatarChanged(filename);
}