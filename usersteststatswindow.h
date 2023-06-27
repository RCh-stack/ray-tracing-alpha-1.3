#ifndef USERSTESTSTATSWINDOW_H
#define USERSTESTSTATSWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include <regex>
#include "sql_requests.h"

namespace Ui {
class UsersTestStatsWindow;
}

class UsersTestStatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UsersTestStatsWindow(QWidget *parent = 0);
    ~UsersTestStatsWindow();

    void set_window_options();
    void output_data_in_lists_to_form();
    void set_enabled_combobox(bool status);

    void set_list_of_groups();
    void set_list_of_tests();

    int get_grade(QString grade);

    void clear_table();
    void output_list_tests();
    void output_list_tests_with_selection(int id_group, int id_test, int grade);

private slots:
    void on_use_selection_clicked();

    void on_comboBox_groups_currentIndexChanged(int index);

    void on_comboBox_tests_currentIndexChanged(int index);

    void on_comboBox_grades_currentIndexChanged(const QString &arg1);

    void on_button_update_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

    void on_table_list_cellDoubleClicked(int row, int column);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::UsersTestStatsWindow *ui;
};

#endif // USERSTESTSTATSWINDOW_H
