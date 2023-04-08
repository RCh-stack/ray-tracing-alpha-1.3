#ifndef CREATEPRACTICWINDOW_H
#define CREATEPRACTICWINDOW_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class CreatePracticWindow;
}

class CreatePracticWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePracticWindow(QWidget *parent = 0);
    ~CreatePracticWindow();

    void set_window_options();
    void set_default_options();
    void set_font_options();

    void set_name_font(QString name) { name_font = name; }
    QString get_name_font() { return name_font; }

    void set_size_font(int size) { size_font = size; }
    int get_size_font() { return size_font; }

    void set_id_font_color(int id) { id_font_color = id; }
    int get_id_font_color() { return id_font_color; }

    int get_num_work();
    QString generate_path_file(QString filename);
    void save_text_in_file();
    void add_file_in_database();

private slots:
    void on_button_generation_clicked();

    void on_button_add_clicked();

    void on_button_options_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

    void on_text_work_textChanged();

private:
    Ui::CreatePracticWindow *ui;
    QSqlDatabase db;
    QString name_font;
    int id_font_color, size_font;
};

#endif // CREATEPRACTICWINDOW_H
