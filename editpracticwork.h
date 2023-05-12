#ifndef EDITPRACTICWORK_H
#define EDITPRACTICWORK_H

#include <QDialog>
#include <QDate>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class EditPracticWork;
}

class EditPracticWork : public QDialog
{
    Q_OBJECT

public:
    explicit EditPracticWork(QWidget *parent = 0);
    ~EditPracticWork();

    void set_window_options();
    void set_system_options();
    void set_visible_information();

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_name_work(QString name) { name_work = name; }
    QString get_name_work() { return name_work; }

    void set_id_work(int id) { id_work = id; }
    int get_id_work() { return id_work; }

    void set_path_to_file(QString path) { path_to_file = path; }
    QString get_path_to_file() { return path_to_file; }

    void set_default_format_file(int id_format);
    void set_formats_files(QString formats) {  format_file = formats; }
    QString get_format_file() { return format_file; }

    void update_select_work();
    QString read_text_work_from_file(QString path);

private slots:
    void on_button_path_clicked();

    void on_button_help_clicked();

    void on_button_edit_clicked();

    void on_button_exit_clicked();

    void on_EditPracticWork_finished(int result);

private:
    Ui::EditPracticWork *ui;
    QString id_user, name_work, path_to_file, format_file;
    int id_work;
};

#endif // EDITPRACTICWORK_H
