#ifndef EDITUSERWINDOW_H
#define EDITUSERWINDOW_H

#include <QDialog>

namespace Ui {
class EditUserWindow;
}

class EditUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserWindow(QWidget *parent = 0);
    ~EditUserWindow();

    void set_window_options();

private slots:
    void on_comboBox_roles_currentIndexChanged(int index);

    void on_button_edit_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

private:
    Ui::EditUserWindow *ui;
};

#endif // EDITUSERWINDOW_H
