#ifndef ADMINPANELWINDOW_H
#define ADMINPANELWINDOW_H

#include <QDialog>

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

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_comboBox_users_currentIndexChanged(int index);

    void on_button_add_clicked();

    void on_button_edit_clicked();

    void on_button_delete_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::AdminPanelWindow *ui;
};

#endif // ADMINPANELWINDOW_H
