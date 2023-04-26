#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
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
    number_of_questuions = get_number_of_questions(get_theme_test());
    current_answers = new int[number_of_questuions];
    correct_answers = new int[number_of_questuions];
    num_question = 1;
    if(get_mode_test() == 0)
    {
        num_hints = 0;
        ui->button_clue->setVisible(1);
    }
    get_question(num_question);
}

// 1.2
void TestWindow::set_enabled_button(int id_question)
{
    if(id_question == 1)
        ui->button_prev_question->setEnabled(0);
    else
        ui->button_prev_question->setEnabled(1);

    if(id_question == number_of_questuions)
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
                        query.value("Answer_3").toString(), query.value("Answer_4").toString(), query.value("Right_Answer").toInt());
}

// 1.2
void TestWindow::output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4, int correct_answer)
{
    ui->text_question->setText(QString::number(id_question) + ". " + question);
    ui->first_answer->setText(answer1);
    ui->second_answer->setText(answer2);
    ui->third_answer->setText(answer3);
    ui->fourth_answer->setText(answer4);
    add_correct_answer(id_question - 1, correct_answer);
    set_enabled_button(id_question);
}

// 1.2
void TestWindow::save_marked_answer(int id_question)
{
    int index = id_question - 1;
    if(ui->first_answer->isChecked())
        add_saved_answer(index, 1);
    else if(ui->second_answer->isChecked())
        add_saved_answer(index, 2);
    else if(ui->third_answer->isChecked())
        add_saved_answer(index, 3);
    else if(ui->fourth_answer->isChecked())
        add_saved_answer(index, 4);
    else
        add_saved_answer(index, 0);
}

// 1.2
void TestWindow::get_marked_answer(int id_question, bool next_question)
{
    int last_answer;
    //if(next_question)
       // last_answer = get_saved_answer(id_question);
    //else
        last_answer = get_saved_answer(id_question - 1);

    if(last_answer == 1)
        ui->first_answer->setChecked(1);
    else if(last_answer == 2)
        ui->second_answer->setChecked(1);
    else if(last_answer == 3)
        ui->third_answer->setChecked(1);
    else if(last_answer == 4)
        ui->fourth_answer->setChecked(1);
    else
        reset_answers();
}

// 1.2
void TestWindow::on_button_prev_question_clicked()
{
    if(num_question > 1 && num_question <= number_of_questuions)
        num_question--;

    get_question(num_question);
    get_marked_answer(num_question, false);
}

void TestWindow::on_button_next_question_clicked()
{
    save_marked_answer(num_question);
    reset_answers();

    if(num_question >= 1 && num_question < number_of_questuions)
        num_question++;

    get_question(num_question);
    //get_marked_answer(num_question, true);
}

// 1.3
void TestWindow::on_button_complete_test_clicked()
{
    save_marked_answer(num_question);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Завершить тестирование", "Вы уверены, что хотите завершить тестирование?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        int num_correct_answers = determine_test_result();
        int rating_test = get_rating(num_correct_answers);
        QMessageBox::information(this, "Результат тестирования", "Тестирование завершено!\nВсего вопросов: 10\n"
                                                                 "Правильных ответов: "     + QString::number(num_correct_answers) + "\n" +
                                                                 "Неправильных ответов: " + QString::number(10 - num_correct_answers) + "\n\n" +
                                                                 "Итоговая оценка: "           + QString::number(rating_test),
                                       QMessageBox::Ok);
        if(get_mode_test() == 1)
            save_test_result(rating_test);
    }

    this->close();
}

// 1.3
int TestWindow::determine_test_result()
{
    int num_correct_answers = 0;
    for(int i = 0; i < number_of_questuions; i++)
        if(get_saved_answer(i) == get_correct_answer(i))
            num_correct_answers++;

    return num_correct_answers;
}

// 1.3
int TestWindow::get_rating(int num_correct_answers)
{
    if(number_of_questuions == 10)
        return num_correct_answers < 5 ? 2 :
                num_correct_answers >= 5 && num_correct_answers < 6 ? 3 :
                num_correct_answers >= 6 && num_correct_answers < 8 ? 4 : 5;
    else
        return num_correct_answers < 10 ? 2 :
                num_correct_answers >= 10 && num_correct_answers < 14 ? 3 :
                num_correct_answers >= 14 && num_correct_answers < 18 ? 4 : 5;
}

// 1.3
void TestWindow::save_test_result(int rating_test)
{
    QSqlQuery query;
    query.prepare(insert_test_result());
    query.bindValue(":id_user",        get_id_user());
    query.bindValue(":id_theme",     get_theme_test());
    query.bindValue(":grade",          rating_test);
    query.bindValue(":date",            get_date_test());
    query.exec();

    QMessageBox::information(this, "Уведомление", "Результат пройденного теста записан!");
}

void TestWindow::on_button_help_clicked()
{

}

// 1.3
void TestWindow::on_button_clue_clicked()
{
    if(num_hints != 3)
    {
        int correct_answer = get_correct_answer(num_question - 1);
        QMessageBox::information(this, "Подсказка", "Правильный ответ на вопрос: " + QString::number(correct_answer));
        num_hints++;
    }
    else
        QMessageBox::warning(this, "Уведомление", "Количество подсказок ограничено.");
}
