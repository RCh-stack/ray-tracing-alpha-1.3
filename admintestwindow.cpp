#include "admintestwindow.h"
#include "ui_admintestwindow.h"

AdminTestWindow::AdminTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminTestWindow)
{
    ui->setupUi(this);
}

AdminTestWindow::~AdminTestWindow()
{
    delete ui;
}

// 1.n
void AdminTestWindow::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}
