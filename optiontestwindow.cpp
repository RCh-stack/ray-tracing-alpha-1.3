#include "optiontestwindow.h"
#include "ui_optiontestwindow.h"
#include "testwindow.h"
#include "ui_testwindow.h"

OptionTestWindow::OptionTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionTestWindow)
{
    ui->setupUi(this);
    ui->datetime_test->setDateTime(QDateTime::currentDateTime());

    set_window_options();
    ui->label_user->setText("Тест_Студент");
}

OptionTestWindow::~OptionTestWindow()
{
    delete ui;
}

void OptionTestWindow::set_window_options()
{
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

void OptionTestWindow::set_user(QString user)
{
    ui->label_user->setText(user);
}

// 1.2
void OptionTestWindow::on_button_start_clicked()
{
    TestWindow *tw = new TestWindow;

    tw->set_mode_test(ui->comboBox_modes->currentIndex());
    tw->set_theme_test(ui->comboBox_topics->currentIndex() + 1);

    tw->start_test();
    tw->exec();
}

void OptionTestWindow::on_button_cancel_clicked()
{
    this->close();
}

void OptionTestWindow::on_button_help_clicked()
{

}
