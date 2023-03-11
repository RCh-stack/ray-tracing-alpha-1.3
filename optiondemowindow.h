#ifndef OPTIONDEMOWINDOW_H
#define OPTIONDEMOWINDOW_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class OptionDemoWindow;
}

class OptionDemoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDemoWindow(QWidget *parent = 0);
    ~OptionDemoWindow();

    void set_window_options();
    void set_default_settings_mode();
    void set_users_settings_mode();

    // 1.1 release
    void set_default_value();
    void set_default_color();
    void set_default_light();

private slots:
    void on_button_start_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

    void on_check_option_clicked();

    void on_button_path_clicked();

private:
    Ui::OptionDemoWindow *ui;
};

#endif // OPTIONDEMOWINDOW_H
