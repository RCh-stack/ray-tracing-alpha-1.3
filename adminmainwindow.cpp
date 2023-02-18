#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);

    QPixmap panel (":/icons/images/admin-panel-button.png");
    QPixmap theory (":/icons/images/admin-theory-button.png");
    QPixmap lab (":/icons/images/admin-lab-button.png");
    QPixmap test (":/icons/images/admin-test-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonPanel(panel);
    QIcon ButtonTheory(theory);
    QIcon ButtonLab(lab);
    QIcon ButtonTest(test);
    QIcon ButtonInformation(help);

    ui->button_admin_panel->setIcon(ButtonPanel);
    ui->button_admin_theory->setIcon(ButtonTheory);
    ui->button_admin_lab->setIcon(ButtonLab);
    ui->button_admin_test->setIcon(ButtonTest);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}
