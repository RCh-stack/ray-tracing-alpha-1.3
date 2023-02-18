#include "practicwindow.h"
#include "ui_practicwindow.h"

PracticWindow::PracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PracticWindow)
{
    ui->setupUi(this);

    QPixmap attach (":/icons/images/attach-button.png");
    QPixmap save (":/icons/images/save-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAttach(attach);
    QIcon ButtonSave(save);
    QIcon ButtonInformation(help);

    ui->button_attach->setIcon(ButtonAttach);
    ui->button_save->setIcon(ButtonSave);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

PracticWindow::~PracticWindow()
{
    delete ui;
}
