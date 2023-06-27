#ifndef CHANGETESTWINDOW_H
#define CHANGETESTWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class ChangeTestWindow;
}

class ChangeTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeTestWindow(QWidget *parent = 0);
    ~ChangeTestWindow();

    void set_window_options();
    void set_default_options();

    void set_id_theme(int id) { id_theme = id; }
    int get_id_theme() { return id_theme; }

    void get_data_from_db();
    int get_selected_answer();

    void set_flag_correct_answer(int id_right_answer);
    void get_select_question(int id_theme, int id_question);
    void set_list_question_numbers();

    void edit_test_in_database();
    void edit_question_from_test();

private slots:
    void on_button_generation_clicked();

    void on_button_edit_test_clicked();

    void on_comboBox_types_currentIndexChanged(int index);

    void on_comboBox_numbers_currentIndexChanged(int index);

    void on_button_edit_question_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::ChangeTestWindow *ui;
    int id_theme;
};

#endif // CHANGETESTWINDOW_H
