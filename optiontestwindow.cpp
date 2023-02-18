#include "optiontestwindow.h"
#include "ui_optiontestwindow.h"
#include "testwindow.h"
#include "ui_testwindow.h"

OptionTestWindow::OptionTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionTestWindow)
{
    ui->setupUi(this);

    QPixmap help(":/icons/images/help-button.png");
    QPixmap start(":/icons/images/start-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");

    QIcon ButtonInformation(help);
    QIcon ButtonStart(start);
    QIcon ButtonCancel(cancel);

    ui->button_help->setIcon(ButtonInformation);
    ui->button_start->setIcon(ButtonStart);
    ui->button_cancel->setIcon(ButtonCancel);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

OptionTestWindow::~OptionTestWindow()
{
    delete ui;
}

void OptionTestWindow::on_button_start_clicked()
{
    TestWindow *tw = new TestWindow;
    tw->exec();
}

void OptionTestWindow::on_button_cancel_clicked()
{

}

void OptionTestWindow::on_button_help_clicked()
{

}
