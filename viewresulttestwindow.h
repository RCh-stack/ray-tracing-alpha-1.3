#ifndef VIEWRESULTTESTWINDOW_H
#define VIEWRESULTTESTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class ViewResultTestWindow;
}

class ViewResultTestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ViewResultTestWindow(QWidget *parent = 0);
    ~ViewResultTestWindow();

    // -------------------------------------------
    void set_window_options();
    void set_enabled_elements_in_form();
    void output_data_in_form();
    void set_enabled_button(int id_question);

    // --------------------------------------
    int get_number_of_questions(int id_test);

    void set_theme_test(int id_test) { id_theme = id_test; }
    int get_theme_test() { return id_theme; }

    void set_name_test(QString name) { name_theme = name; }
    QString get_name_test() { return name_theme; }

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_date_test(QDateTime dt) { datetime_test = dt; }
    QDateTime get_date_test() { return datetime_test; }

    // --------------------------------
    void get_question(int id_question);
    void output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4);
    void reset_answers();

    int get_saved_answer(int id_question);
    int get_correct_answer(int id_question);

    void set_color_marks(int answer, bool correct);
    QIcon get_icon_checkbox(bool correct);
    void set_marked_answer(int answer, int correct_answer);

private slots:
    void on_button_prev_question_clicked();

    void on_button_next_question_clicked();

    void on_button_help_clicked();

    void on_button_exit_clicked();

private:
    Ui::ViewResultTestWindow *ui;
    QString id_user, name_theme;
    int id_theme;
    QDateTime datetime_test;
    int number_of_questions;
    int num_question;
};

#endif // VIEWRESULTTESTWINDOW_H
