#include "userteststatswindow.h"
#include "ui_userteststatswindow.h"
#include "userhelpwindow.h"
#include "viewresulttestwindow.h"

UserTestStatsWindow::UserTestStatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserTestStatsWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_system_options();
}

UserTestStatsWindow::~UserTestStatsWindow()
{
    delete ui;
}

// 1.3
void UserTestStatsWindow::set_window_options()
{
    QPixmap exit(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonExit(exit);
    QIcon ButtonHelp(help);

    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonHelp);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->text_id_user->setEnabled(0);
    ui->text_user_name->setEnabled(0);
}

void UserTestStatsWindow::set_system_options()
{
    QSqlQuery query;
    query.prepare(select_system_options());
    query.exec();

    if(query.next())
    {
        if(query.value("UseViewResult").toBool())
            set_allow_view(true);
        else
            set_allow_view(false);
    }
}

// 1.3
void UserTestStatsWindow::set_title_information()
{
    ui->text_id_user->setText(get_user_id());
    ui->text_user_name->setText(get_user_name());
}

// 1.3
void UserTestStatsWindow::output_table_information()
{
    QSqlQuery query;
    query.prepare(select_test_results_for_user());
    query.bindValue(":id_user",     get_user_id());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_stats->insertRow(i);
        ui->table_stats->setItem(i, 0, new QTableWidgetItem(query.value("ID_Theme").toString()));
        ui->table_stats->setItem(i, 1, new QTableWidgetItem(query.value("Name").toString()));
        ui->table_stats->setItem(i, 2, new QTableWidgetItem(query.value("Grade").toString()));
        ui->table_stats->setItem(i, 3, new QTableWidgetItem(query.value("Date").toString()));
    }
}

// 1.3
void UserTestStatsWindow::on_button_exit_clicked()
{
    this->close();
}

// 1.3
void UserTestStatsWindow::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    uhw->exec();
    uhw->deleteLater();
}

void UserTestStatsWindow::on_table_stats_cellDoubleClicked(int row, int column)
{
    if(get_allow_view())
    {
        column = 1;

        ViewResultTestWindow *vrtw = new ViewResultTestWindow;
        vrtw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

        vrtw->set_id_user(get_user_id());
        vrtw->set_theme_test(ui->table_stats->item(row, 0)->text().toInt());
        vrtw->set_name_test(ui->table_stats->item(row, column)->text());
        vrtw->output_data_in_form();

        vrtw->exec();
        vrtw->deleteLater();
    }
}
