#include "mainwindow.h"
#include "theorywindow.h"
#include "optiondemowindow.h"
#include "optiontestwindow.h"
#include "practicwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindowinformation.h"
#include "userprofilewindow.h"
#include "useroptionwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set_window_options();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_window_options()
{
    QPixmap theory (":/icons/images/admin-theory-button.png");
    QPixmap demo(":/icons/images/admin-demo-button.png");
    QPixmap lab (":/icons/images/admin-lab-button.png");
    QPixmap test (":/icons/images/admin-test-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonTheory(theory);
    QIcon ButtonDemo(demo);
    QIcon ButtonLab(lab);
    QIcon ButtonTest(test);
    QIcon ButtonInformation(help);

    ui->button_theory->setIcon(ButtonTheory);
    ui->button_demo->setIcon(ButtonDemo);
    ui->button_practic->setIcon(ButtonLab);
    ui->button_test->setIcon(ButtonTest);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void MainWindow::on_button_theory_clicked()
{
    TheoryWindow *tw = new TheoryWindow;
    tw->exec();
}

void MainWindow::on_button_demo_clicked()
{
    OptionDemoWindow *dw = new OptionDemoWindow;
    dw->exec();
}

void MainWindow::on_button_test_clicked()
{
    OptionTestWindow *tw = new OptionTestWindow;
    tw->set_id_user(get_id_user());
    tw->set_fullname_user(get_fullname_user());
    tw->set_visible_name_user();
    tw->exec();
}

void MainWindow::on_button_practic_clicked()
{
    PracticWindow *pw = new PracticWindow;
    pw->exec();
}

void MainWindow::on_action_about_information_triggered()
{
    AboutWindowInformation *awi = new AboutWindowInformation;
    awi->exec();
}

void MainWindow::on_action_user_profile_triggered()
{
    UserProfileWindow *upw = new UserProfileWindow;
    upw->set_fullname(get_fullname_user());
    upw->set_group("ДИПРБ-21/1");
    upw->set_role("Студент");
    upw->exec();
}

void MainWindow::on_action_user_option_triggered()
{
    UserOptionWindow *uow = new UserOptionWindow;
    uow->exec();
}
