#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = 0);
    ~AdminMainWindow();

    void set_window_options();

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

private slots:
    void on_action_user_profile_triggered();

    void on_action_about_information_triggered();

    void on_action_user_option_triggered();

    void on_button_admin_panel_clicked();

    void on_action_exit_triggered();

    void on_action_help_triggered();

    void on_action_manual_triggered();

    void on_button_help_clicked();

    void on_button_admin_theory_clicked();

    void on_button_admin_lab_clicked();

    void on_button_admin_test_clicked();

private:
    Ui::AdminMainWindow *ui;
    QString id_user;
    QString fullname_user;
};

#endif // ADMINMAINWINDOW_H
