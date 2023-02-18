#include "mainwindow.h"
#include "theorywindow.h"
#include "optiondemowindow.h"
#include "demonstrationwindow.h"
#include "optiontestwindow.h"
#include "testwindow.h"
#include "practicwindow.h"
#include "ui_mainwindow.h"
#include "aboutwindowinformation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_theory_clicked()
{
    TheoryWindow *tw = new TheoryWindow;
    tw->exec();
}

void MainWindow::on_button_demo_clicked()
{
    //DemonstrationWindow *dw = new DemonstrationWindow;
    OptionDemoWindow *dw = new OptionDemoWindow;
    dw->exec();
}

void MainWindow::on_button_test_clicked()
{
    OptionTestWindow *tw = new OptionTestWindow;
    //TestWindow *tw = new TestWindow;
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
