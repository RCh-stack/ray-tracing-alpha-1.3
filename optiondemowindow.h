#ifndef OPTIONDEMOWINDOW_H
#define OPTIONDEMOWINDOW_H

#include <QDialog>
#include <QKeyEvent>
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
    void set_list_of_background_colors();
    void set_list_of_sphere_colors();
    void set_sphere_colors_to_lists(QIcon olive, QIcon dark_red, QIcon grey,
                                    QIcon light_grey, QIcon pink, QIcon orange, QIcon yellow);

    void set_default_settings_mode();
    void set_users_settings_mode();

    void set_default_value();
    void set_default_color();
    void set_default_light();

private slots:
    void on_button_start_clicked();

    void on_button_cancel_clicked();

    void on_button_help_clicked();

    void on_check_option_clicked();

    void on_button_path_clicked();

    void on_comboBox_types_currentIndexChanged(int index);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::OptionDemoWindow *ui;
};

#endif // OPTIONDEMOWINDOW_H
