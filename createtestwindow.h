#ifndef CREATETESTWINDOW_H
#define CREATETESTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class CreateTestWindow;
}

class CreateTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTestWindow(QWidget *parent = 0);
    ~CreateTestWindow();

    void set_window_options();
    void set_default_options();
    void set_enabled_add_question();

    void set_id_theme(int id) { id_theme = id; }
    int get_id_theme() { return id_theme; }

    int get_num_test();
    int get_selected_answer();

    void set_flag_correct_answer(int id_right_answer);
    void get_select_question(int id_theme, int id_question);
    void set_list_question_numbers();

    void check_availability_question();
    bool check_availability(int id_theme, int id_question);

    void add_test_in_database();
    void add_question_from_test();
    void edit_question_from_test();

private slots:
    void on_comboBox_types_currentIndexChanged(int index);

    void on_button_generation_clicked();

    void on_button_add_test_clicked();

    void on_button_add_question_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_comboBox_numbers_currentIndexChanged(int index);

private:
    Ui::CreateTestWindow *ui;
    int id_theme;
};

#endif // CREATETESTWINDOW_H
