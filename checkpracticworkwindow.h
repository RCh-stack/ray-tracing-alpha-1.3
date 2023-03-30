#ifndef CHECKPRACTICWORKWINDOW_H
#define CHECKPRACTICWORKWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class CheckPracticWorkWindow;
}

class CheckPracticWorkWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CheckPracticWorkWindow(QWidget *parent = 0);
    ~CheckPracticWorkWindow();

    void set_window_options();
    void output_data_to_form();

    void set_list_groups();
    void set_list_users(int id_group);
    void set_list_statuses();
    void set_list_works();

private slots:
    void on_comboBox_groups_currentIndexChanged(int index);

    void on_comboBox_users_currentIndexChanged(int index);

    void on_comboBox_works_currentIndexChanged(int index);

    void on_button_save_clicked();

    void on_button_edit_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::CheckPracticWorkWindow *ui;
    QSqlDatabase db;
};

#endif // CHECKPRACTICWORKWINDOW_H
