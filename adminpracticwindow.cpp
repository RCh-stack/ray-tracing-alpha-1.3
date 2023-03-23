#include "adminpracticwindow.h"
#include "ui_adminpracticwindow.h"

AdminPracticWindow::AdminPracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPracticWindow)
{
    ui->setupUi(this);
}

AdminPracticWindow::~AdminPracticWindow()
{
    delete ui;
}


// 1.n
void AdminPracticWindow::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}
