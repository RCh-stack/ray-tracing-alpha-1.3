#ifndef PRACTICWINDOW_H
#define PRACTICWINDOW_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
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
    void set_list_works();
    void set_enabled_button(int id_status);
    void update_status_work();

    void output_table_of_contents(int row_index);
    void open_file(QString path);

    QString get_lab_work(int id_work);

    int get_id_status(QString id_user, int id_work);
    QString get_status_work(QString id_user, int id_work);

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

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
    QSqlDatabase db;
    QString id_user;
    QString fullname_user;
};

#endif // PRACTICWINDOW_H
