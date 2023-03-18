#include "optiontestwindow.h"
#include "ui_optiontestwindow.h"
#include "testwindow.h"
#include "ui_testwindow.h"
#include "userteststatswindow.h"
#include "ui_userteststatswindow.h"

OptionTestWindow::OptionTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionTestWindow)
{
    ui->setupUi(this);
    ui->datetime_test->setDateTime(QDateTime::currentDateTime());

    set_window_options();
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
    QPixmap stats(":/icons/images/stats-users-button.png");

    QIcon ButtonInformation(help);
    QIcon ButtonStart(start);
    QIcon ButtonCancel(cancel);
    QIcon ButtonStats(stats);

    ui->button_help->setIcon(ButtonInformation);
    ui->button_start->setIcon(ButtonStart);
    ui->button_cancel->setIcon(ButtonCancel);
    ui->button_stats->setIcon(ButtonStats);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.3
void OptionTestWindow::set_visible_name_user()
{
    ui->label_user->setText(get_fullname_user());
}

// 1.2 + 1.3
void OptionTestWindow::on_button_start_clicked()
{
    TestWindow *tw = new TestWindow;
    tw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    tw->set_id_user(get_id_user());
    tw->set_date_test(ui->datetime_test->dateTime());
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

// 1.3
void OptionTestWindow::on_button_stats_clicked()
{
    UserTestStatsWindow *utsw = new UserTestStatsWindow;
    utsw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    utsw->set_user_id(get_id_user());
    utsw->set_user_name(get_fullname_user());
    utsw->set_title_information();
    utsw->output_table_information();
    utsw->exec();
}
