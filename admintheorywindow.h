#ifndef ADMINTHEORYWINDOW_H
#define ADMINTHEORYWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AdminTheoryWindow;
}

class AdminTheoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminTheoryWindow(QWidget *parent = 0);
    ~AdminTheoryWindow();

    void set_window_options();

    void set_options_for_file(int id_page);
    QString get_path_file(int id_page);
    int get_num_page();

    void set_id_page(int id) { id_page = id; }
    int get_id_page() { return id_page; }

    void set_name_theme(QString name) { name_theme = name; }
    QString get_name_theme() { return name_theme; }

    void set_name_file(QString name) { name_file = name; }
    QString get_name_fiile() { return name_file; }

    void open_and_output_file(QString path);
    void add_file_in_database();

private slots:
    void on_action_create_triggered();

    void on_action_save_triggered();

    void on_text_theory_textChanged();

    void on_button_generation_clicked();

    void on_button_add_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_action_open_resource_triggered();

    void on_action_open_directory_triggered();

    void on_button_options_clicked();

private:
    Ui::AdminTheoryWindow *ui;
    QSqlDatabase db;
    int id_page;
    QString name_file, name_theme;
};

#endif // ADMINTHEORYWINDOW_H
