#include "createchatdialog.h"
#include "ui_createchatdialog.h"

#include "core/usecases/createchatusecase.h"
#include "utils.h"

#include <QPushButton>
#include <QMovie>
#include <QFileDialog>
#include <QBuffer>


CreateChatDialog::CreateChatDialog(CreateChatUseCase& uc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateChatDialog)
    , uc_(uc)
{
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &CreateChatDialog::onAvatarClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked,
            this, &CreateChatDialog::onSaveClicked);

    // connect(&uc_, &CreateChatUseCase::requestFinished,
    //         this, &CreateChatDialog::onChatInfoChanged);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadLabel->setFixedSize(40, 40);
    ui->loadLabel->setMovie(gif);
    ui->loadLabel->setScaledContents(true);
    ui->loadLabel->hide();
    ui->verticalLayout->setAlignment(ui->loadLabel, Qt::AlignCenter);
}

CreateChatDialog::~CreateChatDialog()
{
    delete ui;
}

void CreateChatDialog::onAvatarClicked() {
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
    avatar_path_ = filename;
    // emit avatarChanged(filename);
}

void CreateChatDialog::onSaveClicked() {
    Chat chat;
    chat.name = ui->displayNameEdit->text().toStdString();
    chat.avatar = avatar_path_.toStdString();

    const auto img = ui->avatarWgt->image();

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    img.save(&buffer, "PNG");

    uc_.execute(chat, toBytes(buffer.data()));

    startLoadAnim();
}

void CreateChatDialog::startLoadAnim() {
    ui->loadLabel->show();
    ui->loadLabel->movie()->start();
}

void CreateChatDialog::stopLoadAnim() {
    ui->loadLabel->movie()->stop();
    ui->loadLabel->hide();
}