#include "admintestwindow.h"
#include "ui_admintestwindow.h"

AdminTestWindow::AdminTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminTestWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminTestWindow::~AdminTestWindow()
{
    delete ui;
}

// 1.6
void AdminTestWindow::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}
