#include "admintestwindow.h"
#include "ui_admintestwindow.h"
#include "usersteststatswindow.h"

AdminTestWindow::AdminTestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminTestWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminTestWindow::~AdminTestWindow()
{
    delete ui;
}

// 1.6
void AdminTestWindow::set_window_options()
{
    QPixmap add(":/icons/images/add-test-button.png");
    QPixmap edit(":/icons/images/edit-test-button.png");
    QPixmap stats(":/icons/images/stats-users-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonStats(stats);
    QIcon ButtonInformation(help);

    ui->button_create->setIcon(ButtonAdd);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_stats->setIcon(ButtonStats);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AdminTestWindow::on_action_help_triggered()
{

}

void AdminTestWindow::on_action_manual_triggered()
{

}

// 1.6
void AdminTestWindow::on_button_stats_clicked()
{
    UsersTestStatsWindow *utsw = new UsersTestStatsWindow;
    utsw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    utsw->output_data_in_lists_to_form();
    utsw->output_list_tests();

    utsw->exec();
    utsw->deleteLater();
}

void AdminTestWindow::on_button_create_clicked()
{

}

void AdminTestWindow::on_button_edit_clicked()
{

}

void AdminTestWindow::on_button_help_clicked()
{

}
