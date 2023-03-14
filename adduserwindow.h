#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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
    void list_available_groups(int id_role);
    bool code_is_number(const std::string& s);
    bool input_validation();
    void add_new_user();
    //void add_new_admin();
    void clear_input_fields();

private slots:
    void on_comboBox_roles_currentIndexChanged(int index);

    void on_buttod_add_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

private:
    Ui::AddUserWindow *ui;
    QSqlDatabase db;
};

#endif // ADDUSERWINDOW_H
