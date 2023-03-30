#ifndef ADMINPRACTICWINDOW_H
#define ADMINPRACTICWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminPracticWindow;
}

class AdminPracticWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPracticWindow(QWidget *parent = 0);
    ~AdminPracticWindow();

    void set_window_options();

private slots:
    void on_button_add_work_clicked();

    void on_button_edit_work_clicked();

    void on_button_check_work_clicked();

    void on_button_statistics_clicked();

    void on_button_help_clicked();

    void on_action_current_statuses_triggered();

    void on_action_help_triggered();

    void on_action_manual_triggered();

    void on_action_list_works_triggered();

private:
    Ui::AdminPracticWindow *ui;
};

#endif // ADMINPRACTICWINDOW_H
