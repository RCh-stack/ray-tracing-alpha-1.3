#ifndef CHANGEPRACTICWINDOW_H
#define CHANGEPRACTICWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class ChangePracticWindow;
}

class ChangePracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePracticWindow(QWidget *parent = 0);
    ~ChangePracticWindow();

    void set_window_options();
    void set_default_options();

    void get_data_from_db();
    void output_data();

    QString generate_path_file(QString filename);
    void edit_file_in_database();

    void set_id_work(int id) { id_work = id; }
    void set_name_theme(QString name) { name_theme = name; }
    void set_path_file(QString path) { path_to_file = path; }

    int get_id_work() { return id_work; }
    QString get_name_theme() { return name_theme; }
    QString get_path_file() { return path_to_file; }

private slots:
    void on_text_work_textChanged();

    void on_button_generation_clicked();

    void on_button_edit_clicked();

    void on_button_options_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::ChangePracticWindow *ui;
    QSqlDatabase db;
    int id_work;
    QString name_theme, path_to_file;
};

#endif // CHANGEPRACTICWINDOW_H
