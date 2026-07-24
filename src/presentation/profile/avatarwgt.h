#pragma once

#include <QWidget>
#include <QPixmap>

class AvatarWgt : public QWidget
{
    Q_OBJECT
public:
    explicit AvatarWgt(QWidget *parent = nullptr);

    void setImage(const QPixmap& img) noexcept;
    QPixmap image() const noexcept {
        return img_;
    }

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;

private:
    QPixmap img_;
};

