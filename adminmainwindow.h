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

private slots:
    void on_action_user_profile_triggered();

    void on_action_about_information_triggered();

    void on_action_user_option_triggered();

    void on_button_admin_panel_clicked();

private:
    Ui::AdminMainWindow *ui;
};

#endif // ADMINMAINWINDOW_H
