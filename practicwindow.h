#ifndef PRACTICWINDOW_H
#define PRACTICWINDOW_H

#include <QDialog>
#include <QFile>
#include <QDate>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class PracticWindow;
}

class PracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PracticWindow(QWidget *parent = 0);
    ~PracticWindow();

    void set_window_options();
    void set_system_options();
    void set_date_options();
    void set_list_works();
    void set_enabled_button(int id_status);
    void update_status_work();

    void output_table_of_contents(int row_index);
    void open_file(QString path);
    bool check_delivery_date(QDate date_due, QDate date_deadline) { return date_due < date_deadline; }
    void add_new_work();

    QString get_lab_work(int id_work);
    QString get_note(QString id_user, int id_work);

    int get_id_status(QString id_user, int id_work);
    QString get_status_work(QString id_user, int id_work);

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

    void set_allow_pass(bool flag) { allow_pass = flag; }
    bool get_allow_pass() { return allow_pass; }

    void set_check_date(bool flag) { check_date = flag; }
    bool get_check_date() { return check_date; }

private slots:
    void on_comboBox_works_currentIndexChanged(int index);

    void on_button_send_work_clicked();

    void on_button_edit_work_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

    void on_button_update_clicked();

public slots:
    void close_add_edit_window(int result);

private:
    Ui::PracticWindow *ui;
    QString id_user, fullname_user, note;
    bool allow_pass, check_date;
};

#endif // PRACTICWINDOW_H
