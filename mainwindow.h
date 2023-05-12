#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_window_options();

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_fullname_user(QString fullname) { fullname_user = fullname; }
    QString get_fullname_user() { return fullname_user; }

    void set_id_group(int id) { id_group = id; }
    int get_id_group() { return id_group; }
    QString get_name_group(int id);

private slots:
    void on_button_theory_clicked();

    void on_button_demo_clicked();

    void on_button_test_clicked();

    void on_button_practic_clicked();

    void on_action_about_information_triggered();

    void on_action_user_profile_triggered();

    void on_action_exit_triggered();

    void on_action_help_triggered();

    void on_action_manual_triggered();

    void on_button_help_clicked();

private:
    Ui::MainWindow *ui;
    QString id_user;
    QString fullname_user;
    int id_group;
};

#endif // MAINWINDOW_H
