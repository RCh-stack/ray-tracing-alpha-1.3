#include "theorywindow.h"
#include "ui_theorywindow.h"

TheoryWindow::TheoryWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TheoryWindow)
{
    ui->setupUi(this);

    QPixmap leftArrow (":/icons/images/left-arrow.png");
    QPixmap rightArrow (":/icons/images/right-arrow.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonNextPage(rightArrow);
    QIcon ButtonPrevPage(leftArrow);
    QIcon ButtonInformation(help);

    ui->button_next_page->setIcon(ButtonNextPage);
    ui->button_prev_page->setIcon(ButtonPrevPage);
    ui->button_help->setIcon(ButtonInformation);
}

TheoryWindow::~TheoryWindow()
{
    delete ui;
}
