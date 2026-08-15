#include "chatinfodialog.h"
#include "ui_chatinfodialog.h"

#include "presentation/chatinfo/chatparticipantsmodel.h"
#include "presentation/chatinfo/participantdelegate.h"
#include "core/usecases/updatechatusecase.h"
#include "core/usecases/loadparticipantsusecase.h"
#include "utils.h"

#include <QPushButton>
#include <QMovie>
#include <QFileDialog>
#include <QBuffer>

ChatInfoDialog::ChatInfoDialog(
    AvatarProvider* av_provider,
    UpdateChatUseCase& uuc, LoadParticipantsUseCase& luc,
    const Chat& chat, QWidget *parent
)
    : QDialog(parent)
    , ui(new Ui::ChatInfoDialog)
    , av_provider_{av_provider}
    , uuc_{uuc}
    , luc_{luc}
    , chat_tmp_{chat}
{
    setup();
    ui->displayNameEdit->setText(QString::fromStdString(chat_tmp_.name));

    model_ = new ChatParticipantsModel{ui->participantsListView};
    ui->participantsListView->setModel(model_);

    auto participants_delegate = new ParticipantDelegate{ui->participantsListView};
    ui->participantsListView->setItemDelegate(participants_delegate);
    connect(&luc_, &LoadParticipantsUseCase::requestFinished, this,
            &ChatInfoDialog::onLoadParticipantsFinished);

    luc_.execute(chat_tmp_.id);
}

ChatInfoDialog::ChatInfoDialog(
    AvatarProvider* av_provider,
    UpdateChatUseCase& uuc, LoadParticipantsUseCase& luc,
    QWidget *parent
)
    : QDialog(parent)
    , ui(new Ui::ChatInfoDialog)
    , av_provider_{av_provider}
    , uuc_{uuc}
    , luc_{luc}
{
    setup();
}

ChatInfoDialog::~ChatInfoDialog()
{
    delete ui;
}

void ChatInfoDialog::setup() {
    ui->setupUi(this);

    connect(ui->avatarWgt, &AvatarWgt::clicked, this, &ChatInfoDialog::onAvatarClicked);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &ChatInfoDialog::onSaveClicked);

    connect(&uuc_, &UpdateChatUseCase::requestFinished,
            this, &ChatInfoDialog::onChatInfoChanged);

    auto gif = new QMovie{":/icons/icons/load_spin.gif", QByteArray{}, this};
    ui->loadLabel->setFixedSize(40, 40);
    ui->loadLabel->setMovie(gif);
    ui->loadLabel->setScaledContents(true);
    ui->loadLabel->hide();
    ui->verticalLayout->setAlignment(ui->loadLabel, Qt::AlignCenter);

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

    uuc_.execute(chat, toBytes(buffer.data()));

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

void ChatInfoDialog::onLoadParticipantsFinished(
        std::expected<std::list<ChatParticipant>, Error> res
) {
    if (!res.has_value()) {
        ui->errLabel->setText(QString::fromStdString(res.error().msg));
    }

    for (const auto& p : res.value()) {
        if (p.avatar.img_data.empty()) {
            model_->addUser({p.user_id, p.name, QPixmap{}});
        } else {
            try {
                auto pix = av_provider_->addImage(p.avatar);
                model_->addUser({p.user_id, p.name, pix});
            } catch (const std::exception& e) {
                ui->errLabel->setText(QString::fromStdString(e.what()));
            }
        }
    }

    stopLoadAnim();
}