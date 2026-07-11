#include "avatarwgt.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

AvatarWgt::AvatarWgt(QWidget* parent)
    : QWidget{parent}
{
    setFixedSize(96, 96);
}

void AvatarWgt::setImage(const QPixmap& img) noexcept {
    img_ = img;
    update();
}

void AvatarWgt::paintEvent(QPaintEvent* e) {
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QRect r = rect();

    QPainterPath path;
    path.addEllipse(r);

    painter.setClipPath(path);

    if (!img_.isNull()) {
        painter.drawPixmap(
            r,
            img_.scaled(
                r.size(),
                Qt::AspectRatioMode::KeepAspectRatioByExpanding,
                Qt::TransformationMode::SmoothTransformation));
    } else {
        painter.fillPath(path, QColor{180, 180, 180});
    }
}

void AvatarWgt::mousePressEvent(QMouseEvent* e) {
    emit clicked();
}
