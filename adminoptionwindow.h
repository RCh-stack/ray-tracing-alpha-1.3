#ifndef ADMINOPTIONWINDOW_H
#define ADMINOPTIONWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AdminOptionWindow;
}

class AdminOptionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOptionWindow(QWidget *parent = 0);
    ~AdminOptionWindow();

    void set_window_options();
    void set_default_options();
    void set_combobox_values();
    void set_enabled_elements_in_form();
    void save_system_options();

    QString get_format_files();

private slots:
    void on_button_save_clicked();

    void on_button_help_clicked();

    void on_button_cancel_clicked();

    void on_button_all_format_clicked();

    void on_use_some_format_clicked();

    void on_use_select_in_list_clicked();

    void on_use_hints_clicked();

    void on_use_time_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::AdminOptionWindow *ui;
};

#endif // ADMINOPTIONWINDOW_H
