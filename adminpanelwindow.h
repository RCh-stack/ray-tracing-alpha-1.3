#ifndef ADMINPANELWINDOW_H
#define ADMINPANELWINDOW_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AdminPanelWindow;
}

class AdminPanelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanelWindow(QWidget *parent = 0);
    ~AdminPanelWindow();

    void set_window_options();
    void set_enabled_combobox(bool status);

    void output_list_users_with_selection(int id_role, int id_group, int id_status);
    void output_list_users();
    void clear_table();

    QString get_group(int id_group);
    QString get_status(int id_status);
    QString get_selected_id_user();
    int get_status_by_id_user(QString id_user);

    void mark_unmark_user_for_deletion(int id_status, QString id_user);

private slots:

    void on_comboBox_roles_currentIndexChanged(int index);

    void on_button_add_clicked();

    void on_button_edit_clicked();

    void on_button_delete_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

    void on_comboBox_groups_currentIndexChanged(int index);

    void on_button_update_clicked();

    void on_table_users_cellDoubleClicked(int row, int column);

    void on_comboBox_status_currentIndexChanged(int index);

    void on_use_selection_clicked();

public slots:
    void close_add_edit_window(int result);

private:
    Ui::AdminPanelWindow *ui;
    QSqlDatabase db;
};

#endif // ADMINPANELWINDOW_H
