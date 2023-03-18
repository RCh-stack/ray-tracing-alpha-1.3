#include "useroptionwindow.h"
#include "ui_useroptionwindow.h"

UserOptionWindow::UserOptionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserOptionWindow)
{
    ui->setupUi(this);

    set_window_options();
}

UserOptionWindow::~UserOptionWindow()
{
    delete ui;
}

// 1.3
void UserOptionWindow::set_window_options()
{
    QPixmap save(":/icons/images/option-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");

    QIcon ButtonSave(save);
    QIcon ButtonCancel(cancel);

    ui->button_save->setIcon(ButtonSave);
    ui->button_cancel->setIcon(ButtonCancel);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}
