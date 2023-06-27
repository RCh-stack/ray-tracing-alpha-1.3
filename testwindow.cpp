#include "testwindow.h"
#include "ui_testwindow.h"
#include "userhelpwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_system_options();
}

TestWindow::~TestWindow()
{
    delete ui;
}

// 1.3
void TestWindow::set_window_options()
{
    QPixmap complete (":/icons/images/complete-button.png");
    QPixmap prevQuestion (":/icons/images/prev-page.png");
    QPixmap nextQuestion (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap clue(":/icons/images/clue-button.png");

    QIcon ButtonComplete(complete);
    QIcon ButtonNextQues(nextQuestion);
    QIcon ButtonPrevQues(prevQuestion);
    QIcon ButtonInformation(help);
    QIcon ButtonClue(clue);

    ui->button_complete_test->setIcon(ButtonComplete);
    ui->button_next_question->setIcon(ButtonNextQues);
    ui->button_prev_question->setIcon(ButtonPrevQues);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_clue->setIcon(ButtonClue);

    ui->radiobutton_null->setVisible(0);
    ui->button_clue->setVisible(0);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    QFont font("Century Gothic", 14);
    ui->text_question->setFont(font);
}

void TestWindow::set_system_options()
{
    QSqlQuery query;
    query.prepare(select_system_options());
    query.exec();

    if(query.next())
    {
        if(query.value("UseHintsInTest").toBool())
        {
            ui->button_clue->setEnabled(true);
            set_max_num_hints(query.value("NumberHints").toInt());
        }
        else
            ui->button_clue->setEnabled(false);

        if(query.value("UseTimer").toBool())
        {
            set_use_timer(true);
            ui->label_timer->setVisible(true);
            ui->timer_test->setVisible(true);
            ui->timer_test->setEnabled(false);
            time = query.value("TimerValue").toTime();
            ui->timer_test->setTime(time);
        }
        else
        {
            set_use_timer(false);
            ui->label_timer->setVisible(false);
            ui->timer_test->setVisible(false);
        }
    }
}

// 1.3
int TestWindow::get_number_of_questions(int id_theme)
{
    QSqlQuery query;
    query.prepare(select_number_of_questions());
    query.bindValue(":id_theme",  id_theme);
    query.exec();

    if(query.next())
        return query.value("NumberOfQuestions").toInt();

    return 10;
}

// 1.3
void TestWindow::start_test()
{
    number_of_questions = get_number_of_questions(get_theme_test());
    num_question = 1;

    if(get_mode_test() == 0)
    {
        num_hints = 0;
        ui->button_clue->setVisible(1);
    }

    if(get_use_timer())
        run_timer();

    get_question(num_question);
}

void TestWindow::run_timer()
{
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000);

    connect(timer, &QTimer::timeout, this, [=]() {
        time = time.addMSecs(-1000);

        if (time == QTime(0, 0, 0))
        {
            timer->stop();
            end_of_test();
        }

        ui->timer_test->setTime(time);
    });

    timer->start();
}

// 1.2
void TestWindow::set_enabled_button(int id_question)
{
    if(id_question == 1)
        ui->button_prev_question->setEnabled(0);
    else
        ui->button_prev_question->setEnabled(1);

    if(id_question == number_of_questions)
        ui->button_next_question->setEnabled(0);
    else
        ui->button_next_question->setEnabled(1);
}

void TestWindow::reset_answers()
{
    ui->radiobutton_null->setChecked(1);
}

// 1.2
void TestWindow::get_question(int id_question)
{
    QSqlQuery query;
    query.prepare(select_question());
    query.bindValue(":id_question",  id_question);
    query.bindValue(":id_theme",     get_theme_test());

    query.exec();

    if(!query.next())
        QMessageBox::warning(this, "Теcтирование", "Вопрос не найден!");
    else
        output_question(id_question, query.value("Text_Question").toString(), query.value("Answer_1").toString(), query.value("Answer_2").toString(),
                        query.value("Answer_3").toString(), query.value("Answer_4").toString());
}

// 1.2
void TestWindow::output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4)
{
    ui->text_question->setText(QString::number(id_question) + ". " + question);
    ui->first_answer->setText(answer1);
    ui->second_answer->setText(answer2);
    ui->third_answer->setText(answer3);
    ui->fourth_answer->setText(answer4);

    set_enabled_button(id_question);
}

void TestWindow::add_marked_answer(int id_question, int id_answer)
{
    QSqlQuery query;
    query.prepare(insert_answer_of_question());
    query.bindValue(":id_user",       get_id_user());
    query.bindValue(":id_theme",    get_theme_test());
    query.bindValue(":id_question", id_question);
    query.bindValue(":id_answer",   id_answer);

    query.exec();
}

void TestWindow::edit_saved_answer(int id_question, int id_answer)
{
    QSqlQuery query;
    query.prepare(update_answer_of_question());
    query.bindValue(":id_user",       get_id_user());
    query.bindValue(":id_theme",    get_theme_test());
    query.bindValue(":id_question", id_question);
    query.bindValue(":id_answer",   id_answer);

    query.exec();
}

int TestWindow::get_saved_answer(int id_question)
{
    QSqlQuery query;
    query.prepare(select_answer_of_question());
    query.bindValue(":id_user",       get_id_user());
    query.bindValue(":id_theme",    get_theme_test());
    query.bindValue(":id_question", id_question);

    query.exec();

    if(query.next())
        return query.value("Answer").toInt();
    else
        return 0;
}

int TestWindow::get_correct_answer(int id_question)
{
    QSqlQuery query;
    query.prepare(select_question());
    query.bindValue(":id_theme",    get_theme_test());
    query.bindValue(":id_question", id_question);

    query.exec();

    if(query.next())
        return query.value("Right_Answer").toInt();
    else
        return 0;
}

int TestWindow::get_marked_answer()
{
    if(ui->first_answer->isChecked())
        return 1;
    else if(ui->second_answer->isChecked())
        return 2;
    else if(ui->third_answer->isChecked())
        return 3;
    else if(ui->fourth_answer->isChecked())
        return 4;
    else
        return 0;
}

void TestWindow::set_marked_answer(int answer)
{
    if(answer == 1)
        ui->first_answer->setChecked(1);
    else if(answer == 2)
        ui->second_answer->setChecked(1);
    else if(answer == 3)
        ui->third_answer->setChecked(1);
    else if(answer == 4)
        ui->fourth_answer->setChecked(1);
    else
        reset_answers();
}

void TestWindow::save_answer_of_question()
{
    int saved_answer = get_saved_answer(num_question);
    if(saved_answer != 0)
        edit_saved_answer(num_question, saved_answer);
    else
        if(get_marked_answer() != 0)
            add_marked_answer(num_question, get_marked_answer());
}

// 1.2
void TestWindow::on_button_prev_question_clicked()
{
    save_answer_of_question();

    if(num_question > 1 && num_question <= number_of_questions)
        num_question--;

    get_question(num_question);
    set_marked_answer(get_saved_answer(num_question));
}

void TestWindow::on_button_next_question_clicked()
{
    save_answer_of_question();

    if(num_question >= 1 && num_question < number_of_questions)
        num_question++;

    get_question(num_question);
    set_marked_answer(get_saved_answer(num_question));
}

// 1.3
void TestWindow::on_button_complete_test_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Завершить тестирование", "Вы уверены, что хотите завершить тестирование?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        end_of_test();
}

void TestWindow::end_of_test()
{
    save_answer_of_question();
    int num_correct_answers = determine_test_result();
    int rating_test = get_rating(num_correct_answers);
    QMessageBox::information(this, "Результат тестирования", "Тестирование завершено!\nВсего вопросов: 10\n"
                                                             "Правильных ответов: "     + QString::number(num_correct_answers) + "\n" +
                                                             "Неправильных ответов: " + QString::number(10 - num_correct_answers) + "\n\n" +
                                                             "Итоговая оценка: "           + QString::number(rating_test),
                                   QMessageBox::Ok);
    if(get_mode_test() == 1)
        save_test_result(rating_test);

    this->close();
}

// 1.3
int TestWindow::determine_test_result()
{
    int num_correct_answers = 0;
    for(int i = 0; i < number_of_questions; i++)
        if(get_saved_answer(i + 1) == get_correct_answer(i + 1) && get_saved_answer(i + 1) != 0)
            num_correct_answers++;

    return num_correct_answers;
}

// 1.3
int TestWindow::get_rating(int num_correct_answers)
{
    if(number_of_questions == 10)
        return num_correct_answers < 5 ? 2 :
                num_correct_answers >= 5 && num_correct_answers < 6 ? 3 :
                num_correct_answers >= 6 && num_correct_answers < 8 ? 4 : 5;
    else
        return num_correct_answers < 10 ? 2 :
                num_correct_answers >= 10 && num_correct_answers < 14 ? 3 :
                num_correct_answers >= 14 && num_correct_answers < 18 ? 4 : 5;
}

bool TestWindow::check_result_test()
{
    QSqlQuery query;
    query.prepare(select_test_result());
    query.bindValue(":id_user",         get_id_user());
    query.bindValue(":id_theme",      get_theme_test());
    query.exec();

    return query.next();
}

// 1.3
void TestWindow::save_test_result(int rating_test)
{
    QSqlQuery query;
    if(check_result_test())
        query.prepare(update_test_result());
    else
        query.prepare(insert_test_result());
    query.bindValue(":id_user",        get_id_user());
    query.bindValue(":id_theme",     get_theme_test());
    query.bindValue(":grade",          rating_test);
    query.bindValue(":date",            get_date_test());
    query.exec();

    QMessageBox::information(this, "Уведомление", "Результат пройденного теста записан/изменен.");
}

void TestWindow::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(12);

    uhw->exec();
    uhw->deleteLater();
}

// 1.3
void TestWindow::on_button_clue_clicked()
{
    if(num_hints != get_max_num_hints())
    {
        int correct_answer = get_correct_answer(num_question);
        QMessageBox::information(this, "Подсказка", "Правильный ответ на вопрос: " + QString::number(correct_answer));
        num_hints++;
    }
    else
        QMessageBox::warning(this, "Уведомление", "Количество подсказок ограничено.");
}

void TestWindow::closeEvent(QCloseEvent *event)
{
    if(event->spontaneous() && event->isAccepted())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Завершить тестирование",
                                                                  "Вы уверены, что хотите завершить тестирование?\nДанные не будут сохранены.",
                                                                  QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
            event->accept();
        else
            event->ignore();
    }
}

void TestWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        event->ignore();
    else if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}
