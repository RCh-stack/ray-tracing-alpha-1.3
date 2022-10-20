#include "mainwindow.h"
#include "theorywindow.h"
#include "demonstrationwindow.h"
#include "testwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    DemonstrationWindow *dw = new DemonstrationWindow;
    dw->exec();
}

void MainWindow::on_button_test_clicked()
{
    TestWindow *tw = new TestWindow;
    tw->exec();
}
