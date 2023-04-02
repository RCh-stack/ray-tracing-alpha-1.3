#ifndef CHECKPRACTICWORKWINDOW_H
#define CHECKPRACTICWORKWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <regex>
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
    void set_font_default();
    void output_data_to_form();
    void enabled_elements_in_form(bool enable);

    void set_list_groups();
    void set_list_users(int id_group);
    void set_list_statuses();
    void set_list_works();
    void output_text_work(QString id_user, int id_work);

    void set_id_user(QString id) { id_user = id; }
    void set_id_work(int id) { id_work = id; }
    void set_id_status(int id) { id_status = id; }
    void set_note(QString text) { note = text; }

    QString get_id_user() { return id_user; }
    int get_id_work() { return id_work; }
    int get_id_status() { return id_status; }
    QString get_note() { return note; }

private slots:
    void on_comboBox_groups_currentIndexChanged(int index);

    void on_comboBox_users_currentIndexChanged(const QString &arg1);

    void on_comboBox_statuses_currentIndexChanged(int index);

    void on_comboBox_works_currentIndexChanged(int index);

    void on_button_save_clicked();

    void on_button_edit_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

    void on_button_note_clicked();

    void on_button_enter_note_clicked();

    void on_button_clear_clicked();

private:
    Ui::CheckPracticWorkWindow *ui;
    QSqlDatabase db;
    QString id_user;
    int id_work, id_status;
    QString note;
};

#endif // CHECKPRACTICWORKWINDOW_H
