#include "useroptionwindow.h"
#include "ui_useroptionwindow.h"

UserOptionWindow::UserOptionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserOptionWindow)
{
    ui->setupUi(this);

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

UserOptionWindow::~UserOptionWindow()
{
    delete ui;
}
