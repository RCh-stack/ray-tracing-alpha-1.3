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

private slots:
    void on_button_theory_clicked();

    void on_button_demo_clicked();

    void on_button_test_clicked();

    void on_button_practic_clicked();

    void on_action_about_information_triggered();

    void on_action_user_profile_triggered();

    void on_action_user_option_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
