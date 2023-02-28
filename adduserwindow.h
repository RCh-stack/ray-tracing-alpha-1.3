#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QDialog>

namespace Ui {
class AddUserWindow;
}

class AddUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserWindow(QWidget *parent = 0);
    ~AddUserWindow();

    void set_window_options();

private slots:
    void on_comboBox_roles_currentIndexChanged(int index);

    void on_buttod_add_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

private:
    Ui::AddUserWindow *ui;
};

#endif // ADDUSERWINDOW_H
