#ifndef ADMINPANELWINDOW_H
#define ADMINPANELWINDOW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class AdminPanelWindow;
}

class AdminPanelWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPanelWindow(QWidget *parent = 0);
    ~AdminPanelWindow();

    void set_window_options();
    void output_list_users(int id_role);
    QString get_group(int id_group);

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &);

    void on_comboBox_users_currentIndexChanged(int index);

    void on_button_add_clicked();

    void on_button_edit_clicked();

    void on_button_delete_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::AdminPanelWindow *ui;
    QSqlDatabase db;
};

#endif // ADMINPANELWINDOW_H
