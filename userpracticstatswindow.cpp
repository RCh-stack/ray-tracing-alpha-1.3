#include "userpracticstatswindow.h"
#include "ui_userpracticstatswindow.h"
#include "adminhelpwindow.h"

UserPracticStatsWindow::UserPracticStatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPracticStatsWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_enabled_combobox(false);
}

UserPracticStatsWindow::~UserPracticStatsWindow()
{
    delete ui;
}

// 1.6
void UserPracticStatsWindow::set_window_options()
{
    QPixmap exit(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap update(":/icons/images/update-button.png");

    QIcon ButtonExit(exit);
    QIcon ButtonHelp(help);
    QIcon ButtonUpdate(update);

    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonHelp);
    ui->button_update->setIcon(ButtonUpdate);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->table_list->setColumnWidth(0, 100);
    ui->table_list->setColumnWidth(1, 220);
    ui->table_list->setColumnWidth(2, 340);
    ui->table_list->setColumnWidth(3, 180);
}

// 1.6
void UserPracticStatsWindow::set_enabled_combobox(bool status)
{
    ui->comboBox_groups->setEnabled(status);
    ui->comboBox_statuses->setEnabled(status);
    ui->comboBox_works->setEnabled(status);
}

// 1.6
void UserPracticStatsWindow::clear_table()
{
    ui->table_list->clearContents();
    ui->table_list->setRowCount(0);
}

// 1.6
void UserPracticStatsWindow::output_data_in_lists_to_form()
{
    set_list_of_groups();
    set_list_of_statuses();
    set_list_of_works();
}

// 1.6
void UserPracticStatsWindow::set_list_of_groups()
{
    ui->comboBox_groups->clear();

    QSqlQuery query;
    query.prepare(select_all_groups());
    query.exec();

    while(query.next())
        ui->comboBox_groups->addItem(query.value("Name_Group").toString());

    ui->comboBox_groups->removeItem(ui->comboBox_groups->count() - 1);
}

// 1.6
void UserPracticStatsWindow::set_list_of_works()
{
    ui->comboBox_works->clear();

    QSqlQuery query;
    query.prepare(select_all_themes_lab_works());
    query.exec();

    while(query.next())
        ui->comboBox_works->addItem(query.value("ID_Theme").toString() + ". " + query.value("Name").toString().simplified());
}

// 1.6
void UserPracticStatsWindow::set_list_of_statuses()
{
    ui->comboBox_statuses->clear();

    QSqlQuery query;
    query.prepare(select_all_statuses_works());
    query.exec();

    while(query.next())
        ui->comboBox_statuses->addItem(query.value("Name").toString().simplified());
}

// 1.6
void UserPracticStatsWindow::on_use_selection_clicked()
{
    clear_table();
    if(ui->use_selection->isChecked())
    {
        set_enabled_combobox(true);
        output_list_works_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_works->currentIndex() + 1, ui->comboBox_statuses->currentIndex() + 1);
    }
    else
    {
        set_enabled_combobox(false);
        output_list_works();
    }
}

// 1.6
void UserPracticStatsWindow::output_list_works()
{
    QSqlQuery query;
    query.prepare(select_all_lab_works());

    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_list->insertRow(i);
        ui->table_list->setItem(i, 0, new QTableWidgetItem(query.value("GroupName").toString()));
        ui->table_list->setItem(i, 1, new QTableWidgetItem(query.value("ID_User").toString() + " - " + query.value("Fullname").toString()));
        ui->table_list->setItem(i, 2, new QTableWidgetItem(query.value("NameWork").toString()));
        ui->table_list->setItem(i, 3, new QTableWidgetItem(query.value("StatusWork").toString()));
    }
}

// 1.6
void UserPracticStatsWindow::output_list_works_with_selection(int id_group, int id_work, int id_status)
{
    QSqlQuery query;
    query.prepare(select_all_lab_works_with_selections());
    query.bindValue(":id_group",    id_group);
    query.bindValue(":id_work",     id_work);
    query.bindValue(":id_status",   id_status);

    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_list->insertRow(i);
        ui->table_list->setItem(i, 0, new QTableWidgetItem(query.value("GroupName").toString()));
        ui->table_list->setItem(i, 1, new QTableWidgetItem(query.value("ID_User").toString() + " - " + query.value("Fullname").toString()));
        ui->table_list->setItem(i, 2, new QTableWidgetItem(query.value("NameWork").toString()));
        ui->table_list->setItem(i, 3, new QTableWidgetItem(query.value("StatusWork").toString()));
    }
}

// 1.6
void UserPracticStatsWindow::on_button_update_clicked()
{
    clear_table();
    if(ui->use_selection->isChecked())
        output_list_works_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_works->currentIndex() + 1, ui->comboBox_statuses->currentIndex() + 1);
    else
        output_list_works();
}

// 1.6
void UserPracticStatsWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    clear_table();
    output_list_works_with_selection(index + 1, ui->comboBox_works->currentIndex() + 1, ui->comboBox_works->currentIndex() + 1);
}

// 1.6
void UserPracticStatsWindow::on_comboBox_works_currentIndexChanged(int index)
{
    clear_table();
    output_list_works_with_selection(ui->comboBox_groups->currentIndex() + 1, index + 1, ui->comboBox_statuses->currentIndex() + 1);
}

// 1.6
void UserPracticStatsWindow::on_comboBox_statuses_currentIndexChanged(int index)
{
    clear_table();
    output_list_works_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_works->currentIndex() + 1, index + 1);
}

// 1.6
void UserPracticStatsWindow::on_button_exit_clicked()
{
    this->close();
}

void UserPracticStatsWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}
