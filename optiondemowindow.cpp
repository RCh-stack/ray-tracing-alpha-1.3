#include "optiondemowindow.h"
#include "ui_optiondemowindow.h"
#include "demonstrationwindow.h"
#include "ui_demonstrationwindow.h"

OptionDemoWindow::OptionDemoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionDemoWindow)
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

OptionDemoWindow::~OptionDemoWindow()
{
    delete ui;
}

void OptionDemoWindow::on_pushButton_clicked()
{
    DemonstrationWindow *dw = new DemonstrationWindow;
    dw->exec();
}
