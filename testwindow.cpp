#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    QPixmap complete (":/icons/images/complete-button.png");
    QPixmap prevQuestion (":/icons/images/prev-page.png");
    QPixmap nextQuestion (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonComplete(complete);
    QIcon ButtonNextQues(nextQuestion);
    QIcon ButtonPrevQues(prevQuestion);
    QIcon ButtonInformation(help);

    ui->button_complete_test->setIcon(ButtonComplete);
    ui->button_next_question->setIcon(ButtonNextQues);
    ui->button_prev_question->setIcon(ButtonPrevQues);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

TestWindow::~TestWindow()
{
    delete ui;
}
