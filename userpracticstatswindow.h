#ifndef USERPRACTICSTATSWINDOW_H
#define USERPRACTICSTATSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class UserPracticStatsWindow;
}

class UserPracticStatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserPracticStatsWindow(QWidget *parent = 0);
    ~UserPracticStatsWindow();

    void set_window_options();
    void output_data_in_lists_to_form();
    void set_enabled_combobox(bool status);

    void set_list_of_groups();
    void set_list_of_statuses();
    void set_list_of_works();

    void clear_table();
    void output_list_works();
    void output_list_works_with_selection(int id_group, int id_work, int id_status);

private slots:
    void on_comboBox_groups_currentIndexChanged(int index);

    void on_comboBox_works_currentIndexChanged(int index);

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_use_selection_clicked();

    void on_comboBox_statuses_currentIndexChanged(int index);

    void on_button_update_clicked();

private:
    Ui::UserPracticStatsWindow *ui;
    QSqlDatabase db;
};

#endif // USERPRACTICSTATSWINDOW_H
