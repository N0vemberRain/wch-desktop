#include "chatinfodialog.h"
#include "ui_chatinfodialog.h"

#include "core/usecases/updatechatusecase.h"
#include "utils.h"

#include <QPushButton>
#include <QMovie>
#include <QFileDialog>
#include <QBuffer>

ChatInfoDialog::ChatInfoDialog(UpdateChatUseCase& uc, const Chat& chat, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatInfoDialog)
    , uc_{uc}
    , chat_tmp_{chat}
{
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &ChatInfoDialog::onAvatarClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &ChatInfoDialog::onSaveClicked);

    connect(&uc_, &UpdateChatUseCase::requestFinished,
            this, &ChatInfoDialog::onChatInfoChanged);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadLabel->setFixedSize(40, 40);
    ui->loadLabel->setMovie(gif);
    ui->loadLabel->setScaledContents(true);
    ui->loadLabel->hide();
    ui->verticalLayout->setAlignment(ui->loadLabel, Qt::AlignCenter);

    ui->displayNameEdit->setText(QString::fromStdString(chat.name));
}

ChatInfoDialog::~ChatInfoDialog()
{
    delete ui;
}

void ChatInfoDialog::setAvatar(QPixmap img) noexcept {
    ui->avatarWgt->setImage(img);
}

void ChatInfoDialog::onAvatarClicked() {
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
    // emit avatarChanged(filename);
}

void ChatInfoDialog::onSaveClicked() {
    Chat chat;
    chat.name = ui->displayNameEdit->text().toStdString();
    chat.avatar = new_avatar_path_.toStdString();
    chat.id = chat_tmp_.id;
    chat.type = chat_tmp_.type;

    const auto img = ui->avatarWgt->image();

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");

    uc_.execute(chat, toBytes(buffer.data()));

    startLoadAnim();
}

void ChatInfoDialog::startLoadAnim() {
    ui->loadLabel->show();
    ui->loadLabel->movie()->start();
}

void ChatInfoDialog::stopLoadAnim() {
    ui->loadLabel->movie()->stop();
    ui->loadLabel->hide();
}

void ChatInfoDialog::onChatInfoChanged(std::expected<Chat, Error> res) {
    stopLoadAnim();
    if (res.has_value()) {
        ui->displayNameEdit->setText(QString::fromStdString(res.value().name));
    } else {
        ui->errLabel->setText(QString::fromStdString(res.error().msg));
    }
}