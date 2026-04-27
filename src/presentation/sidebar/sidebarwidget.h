#ifndef SIDEBARWIDGET_H
#define SIDEBARWIDGET_H

#include <QWidget>

namespace Ui {
class SidebarWidget;
}

class SidebarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SidebarWidget(QWidget *parent = nullptr);
    ~SidebarWidget();

private slots:
    void onAddGroupAction();
    void onSettingsAction();

private:
    Ui::SidebarWidget *ui;
};

#endif // SIDEBARWIDGET_H
