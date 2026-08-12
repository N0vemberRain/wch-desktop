#include "profiledialog.h"
#include "ui_profiledialog.h"

#include "core/domain/user.h"
#include "core/usecases/updateprofileusecase.h"
#include "presentation/profile/avatarwgt.h"
#include "utils.h"

#include <QPixmap>
#include <QFileDialog>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QMovie>
#include <QBuffer>

ProfileDialog::ProfileDialog(UpdateProfileUseCase& uc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProfileDialog)
    , uc_(uc)
{
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &ProfileDialog::onAvatarClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &ProfileDialog::onSaveClicked);

    // connect(&uc_, &UpdateProfileUseCase::requestFinished,
    //         this, &ProfileDialog::onProfileChanged);

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

    user_tmp_ = u;
}

void ProfileDialog::setAvatar(QPixmap img) noexcept {
    ui->avatarWgt->setImage(img);
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

    const auto img = ui->avatarWgt->image();

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");

    AvatarData av_data{user_tmp_.id, toBytes(buffer.data()), "PNG"};

    uc_.execute(u, av_data);

    startLoadAnim();
}

void ProfileDialog::onProfileChanged(std::expected<User, Error> res) {
    stopLoadAnim();
    if (res.has_value()) {
        setUser(*res);
        ui->errLabel->setText("Changes have been saved");
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