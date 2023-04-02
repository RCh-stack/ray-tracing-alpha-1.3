#ifndef CREATEPRACTICWINDOW_H
#define CREATEPRACTICWINDOW_H

#include <QDialog>
#include <QMessageBox>
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

    int get_num_work();
    QString generate_path_file(QString filename);
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
};

#endif // CREATEPRACTICWINDOW_H
