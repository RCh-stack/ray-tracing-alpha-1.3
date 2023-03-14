#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class TestWindow;
}

// 1.2
class TestWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

    // 1.2
    // Rus:
    //      ...
    void set_theme_test(int id_theme) { theme_test = id_theme; }
    int get_theme_test() { return theme_test; }

    void set_mode_test(int id_mode) { mode_test = id_mode; }
    int get_mode_test() { return mode_test; }

    void add_correct_answer(int index, int number) { correct_answers[index] = number; }
    int get_correct_answer(int index) { return correct_answers[index]; }

    void add_saved_answer(int index, int answer) { current_answers[index] = answer; }
    int get_saved_answer(int index) { return current_answers[index]; }
    //      ...

    // Rus:
    //      ...
    void set_window_options();
    void set_enabled_button(int id_question);
    void start_test();
    void get_question(int id_question);
    void output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4, int correct_answer);
    void reset_answers();
    void save_marked_answer(int id_question);
    void get_marked_answer(int id_question, bool next_question);
    void determine_test_result();
    int get_rating();
    //      ....

private slots:
    void on_button_prev_question_clicked();

    void on_button_next_question_clicked();

    void on_button_complete_test_clicked();

    void on_button_help_clicked();

private:
    Ui::TestWindow *ui;
    QSqlDatabase db;
    QString code_user; // идентификатор пользователя
    int theme_test;  // тема тестирования
    int mode_test; // режим тестирования
    QDateTime datetime_test; // дата/время прохождения тестирования
    int num_question; // номер вопроса
    int current_answers[10]; // текущие ответы на вопросы
    int correct_answers[10]; // корректные ответы на выданные вопросы
    int num_correct_answers, num_wrong_answers;
};

#endif // TESTWINDOW_H
