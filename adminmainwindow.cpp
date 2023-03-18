#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "aboutwindowinformation.h"
#include "userprofilewindow.h"
#include "useroptionwindow.h"
#include "adminpanelwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

// 1.3
void AdminMainWindow::set_window_options()
{
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

void AdminMainWindow::on_action_user_profile_triggered()
{
    UserProfileWindow *upw = new UserProfileWindow;
    upw->set_fullname("Администратор");
    upw->set_group("АСОИУ");
    upw->set_role("Преподаватель");
    upw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    upw->exec();
}

void AdminMainWindow::on_action_about_information_triggered()
{
    AboutWindowInformation *awi = new AboutWindowInformation;
    awi->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    awi->exec();
}

void AdminMainWindow::on_action_user_option_triggered()
{
    UserOptionWindow *uow = new UserOptionWindow;
    uow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uow->exec();
}

void AdminMainWindow::on_button_admin_panel_clicked()
{
    AdminPanelWindow *apw = new AdminPanelWindow;
    apw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    apw->exec();
}
