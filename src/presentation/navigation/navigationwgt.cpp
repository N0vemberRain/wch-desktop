#include "navigationwgt.h"

#include "core/domain/user.h"
#include "presentation/navigation/userheaderwgt.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

NavigationWgt::NavigationWgt(QWidget *parent)
    : QFrame(parent)
    , user_wgt_(new UserHeaderWgt(this))
{
    setFixedWidth(280);

    // Telegram-like white panel
    setStyleSheet(R"(
        NavigationWgt {
            background: white;
            border-right: 1px solid #d0d0d0;
        }
        QPushButton {
            text-align: left;
            padding: 12px;
            border: none;
            font-size: 14px;
        }
        QPushButton:hover {
            background: #eeeeee;
        }
    )");

    auto *layout = new QVBoxLayout(this);

    // Header
    // auto *header = new QLabel("👤 Igor");
    // header->setMinimumHeight(80);
    // header->setAlignment(Qt::AlignCenter);

    layout->addWidget(user_wgt_);

    profile_button_ = new QPushButton("Profile");
    settings_button_ = new QPushButton("Settings");
    logout_button_ = new QPushButton("Log out");

    layout->addWidget(profile_button_);
    layout->addWidget(settings_button_);

    layout->addStretch();

    layout->addWidget(logout_button_);

    connect(profile_button_, &QPushButton::clicked,
            this, &NavigationWgt::profileClicked);

    connect(settings_button_, &QPushButton::clicked,
            this, &NavigationWgt::settingsClicked);

    connect(logout_button_, &QPushButton::clicked,
            this, &NavigationWgt::logoutClicked);
}

void NavigationWgt::setUser(const User& u) noexcept {
    user_wgt_->setUser(u);
}