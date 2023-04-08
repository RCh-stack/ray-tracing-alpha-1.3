#ifndef ADMINTESTWINDOW_H
#define ADMINTESTWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminTestWindow;
}

class AdminTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminTestWindow(QWidget *parent = 0);
    ~AdminTestWindow();

    void set_window_options();

private slots:
    void on_action_help_triggered();

    void on_action_manual_triggered();

    void on_button_stats_clicked();

    void on_button_create_clicked();

    void on_button_edit_clicked();

    void on_button_help_clicked();

private:
    Ui::AdminTestWindow *ui;
};

#endif // ADMINTESTWINDOW_H
