#include "userheaderwgt.h"
#include "ui_userheaderwgt.h"

#include "core/domain/user.h"

#include <QPixmap>

UserHeaderWgt::UserHeaderWgt(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserHeaderWgt)
{
    ui->setupUi(this);
}

UserHeaderWgt::~UserHeaderWgt()
{
    delete ui;
}

void UserHeaderWgt::setUser(const User& u) noexcept {
    ui->nameLabel->setText(QString::fromStdString(u.name));
    ui->nameLabel->setFixedHeight(50);

    if (u.avatar_url.empty()) {
        ui->avatarLable->setText("👤");
    } else {
        auto av = QPixmap{QString::fromStdString(u.avatar_url)};
        setAvatar(av);
    }


    auto status_pix = QPixmap{":/icons/icons/green_c.png"};
    status_pix = status_pix.scaled(16, 16,
                      Qt::AspectRatioMode::KeepAspectRatio,
                      Qt::TransformationMode::SmoothTransformation);
    ui->statusLabel->setPixmap(status_pix);
    // ui->statusLabel->setSizePolicy(
    //     QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed
    // );
    ui->statusLabel->setFixedWidth(30);
    ui->statusLabel->setAlignment(Qt::AlignCenter | Qt::AlignRight);
}

void UserHeaderWgt::setAvatar(QPixmap img) {
    ui->avatarLable->setPixmap(img.scaled(
        100, 100,
        Qt::AspectRatioMode::KeepAspectRatio,
        Qt::TransformationMode::SmoothTransformation));
    ui->avatarLable->setFixedSize(100, 100);
    ui->avatarLable->setAlignment(Qt::AlignCenter | Qt::AlignRight);
}

QPixmap UserHeaderWgt::getAvatar() const noexcept {
    return ui->avatarLable->pixmap();
}