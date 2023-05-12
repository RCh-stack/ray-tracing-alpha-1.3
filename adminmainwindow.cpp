#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include "aboutwindowinformation.h"
#include "userprofilewindow.h"
#include "adminoptionwindow.h"
#include "adminpanelwindow.h"
#include "admintheorywindow.h"
#include "adminpracticwindow.h"
#include "admintestwindow.h"
#include "adminhelpwindow.h"

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

    upw->set_fullname(get_fullname_user());
    upw->set_group("АСОИУ");
    upw->set_role("Преподаватель");

    upw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    upw->exec();
    upw->deleteLater();
}

void AdminMainWindow::on_action_about_information_triggered()
{
    AboutWindowInformation *awi = new AboutWindowInformation;
    awi->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    awi->exec();
    awi->deleteLater();
}

void AdminMainWindow::on_action_admin_option_triggered()
{
    AdminOptionWindow *aow = new AdminOptionWindow;
    aow->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    aow->set_default_options();

    aow->exec();
    aow->deleteLater();
}

void AdminMainWindow::on_button_admin_panel_clicked()
{
    AdminPanelWindow *apw = new AdminPanelWindow;
    apw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    apw->exec();
    apw->deleteLater();
}

// 1.5
void AdminMainWindow::on_button_admin_theory_clicked()
{
    AdminTheoryWindow *atw = new AdminTheoryWindow;
    atw->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    atw->setMinimumHeight(747);
    atw->setMaximumHeight(747);
    atw->setMinimumWidth(1286);
    atw->setMaximumWidth(1286);

    atw->show();
}

// 1.6
void AdminMainWindow::on_button_admin_lab_clicked()
{
    AdminPracticWindow *apw = new AdminPracticWindow;
    apw->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    apw->setMinimumHeight(221);
    apw->setMaximumHeight(221);
    apw->setMinimumWidth(556);
    apw->setMaximumWidth(556);

    apw->show();
}

// 1.6
void AdminMainWindow::on_button_admin_test_clicked()
{
    AdminTestWindow *atw = new AdminTestWindow;
    atw->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    atw->setMinimumHeight(165);
    atw->setMaximumHeight(165);
    atw->setMinimumWidth(410);
    atw->setMaximumWidth(410);

    atw->show();
}

// 1.4
void AdminMainWindow::on_action_exit_triggered()
{
    this->close();
}

void AdminMainWindow::on_action_help_triggered()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void AdminMainWindow::on_action_manual_triggered()
{

}

void AdminMainWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}
