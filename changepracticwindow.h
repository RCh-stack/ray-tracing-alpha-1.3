#ifndef CHANGEPRACTICWINDOW_H
#define CHANGEPRACTICWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
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
    void set_system_options();
    void set_font_options();

    void get_data_from_db();
    void output_data();
    void open_and_output_file(QString path);
    void split_string_with_path(QString path);

    QString generate_path_file(QString filename);
    void save_text_in_file();
    void edit_file_in_database();

    void set_id_work(int id) { id_work = id; }
    void set_name_file(QString name) { name_file = name; }
    void set_name_theme(QString name) { name_theme = name; }
    void set_path_file(QString path) { path_to_file = path; }

    int get_id_work() { return id_work; }
    QString get_name_file() { return name_file; }
    QString get_name_theme() { return name_theme; }
    QString get_path_file() { return path_to_file; }

    void set_name_font(QString name) { name_font = name; }
    QString get_name_font() { return name_font; }

    void set_size_font(int size) { size_font = size; }
    int get_size_font() { return size_font; }

    void set_id_font_color(int id) { id_font_color = id; }
    int get_id_font_color() { return id_font_color; }

    void set_use_deadline(bool use) { use_deadline = use; }
    bool get_use_deadline() { return use_deadline; }

private slots:
    void on_text_work_textChanged();

    void on_button_generation_clicked();

    void on_button_edit_clicked();

    void on_button_options_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::ChangePracticWindow *ui;
    int id_work, id_font_color, size_font;
    QString name_file, name_theme, path_to_file, name_font;
    bool use_deadline;
};

#endif // CHANGEPRACTICWINDOW_H
