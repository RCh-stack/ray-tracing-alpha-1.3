#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserWindow(QWidget *parent = 0);
    ~EditUserWindow();

    void set_window_options();
    void list_available_groups(int id_role);
    bool code_is_number(const std::string& s);
    bool input_validation();
    int get_id_group();
    void edit_current_user();
    void clear_input_fields();

    void set_user_data_by_id();
    void set_current_id(QString id_user) { current_id_user = id_user; }
    QString get_current_id() { return current_id_user; }

private slots:
    void on_comboBox_roles_currentIndexChanged(int index);

    void on_button_edit_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_EditUserWindow_finished(int result);

private:
    Ui::EditUserWindow *ui;
    QSqlDatabase db;
    QString current_id_user;
};

#endif // EDITUSERWINDOW_H
