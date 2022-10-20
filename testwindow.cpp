#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    QPixmap help(":/icons/images/help-button.png");
    QIcon ButtonInformation(help);
    ui->button_help->setIcon(ButtonInformation);
}

TestWindow::~TestWindow()
{
    delete ui;
}
