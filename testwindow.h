#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>
#include "sql_requests.h"

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
    int get_number_of_questions(int id_theme);

    void set_theme_test(int id_theme) { theme_test = id_theme; }
    int get_theme_test() { return theme_test; }

    void set_mode_test(int id_mode) { mode_test = id_mode; }
    int get_mode_test() { return mode_test; }

    void set_id_user(QString id) { id_user = id; }
    QString get_id_user() { return id_user; }

    void set_date_test(QDateTime dt) { datetime_test = dt; }
    QDateTime get_date_test() { return datetime_test; }

    void set_max_num_hints(int num) { max_num_hints = num; }
    int get_max_num_hints() { return max_num_hints; }

    void set_use_timer(bool use) { use_timer = use; }
    bool get_use_timer() { return use_timer; }

    void run_timer();

    // Rus:
    //      ...
    void set_window_options();
    void set_system_options();
    void set_enabled_button(int id_question);

    void start_test();
    void get_question(int id_question);
    void output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4);
    void reset_answers();

    void save_answer_of_question();
    int get_saved_answer(int id_question);
    int get_correct_answer(int id_question);

    void add_marked_answer(int id_question, int id_answer);
    void edit_saved_answer(int id_question, int id_answer);
    int get_marked_answer();
    void set_marked_answer(int answer);

    bool check_result_test();
    void end_of_test();
    int determine_test_result();
    int get_rating(int num_correct_answers);
    void save_test_result(int rating_test);
    //      ....

private slots:
    void on_button_prev_question_clicked();

    void on_button_next_question_clicked();

    void on_button_complete_test_clicked();

    void on_button_help_clicked();

    void on_button_clue_clicked();

private:
    Ui::TestWindow *ui;
    QString id_user; // идентификатор пользователя
    int theme_test;  // тема тестирования
    int mode_test; // режим тестирования
    QDateTime datetime_test; // дата/время прохождения тестирования
    int number_of_questions; // кол-во вопросов в тесте
    int num_question; // номер вопроса
    int num_hints; // кол-во подсказок
    int max_num_hints;
    bool use_timer;
    QTime time;

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event);
};

#endif // TESTWINDOW_H
