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
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text());

    set_window_options();
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::set_window_options()
{
    QPixmap complete (":/icons/images/complete-button.png");
    QPixmap prevQuestion (":/icons/images/prev-page.png");
    QPixmap nextQuestion (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonComplete(complete);
    QIcon ButtonNextQues(nextQuestion);
    QIcon ButtonPrevQues(prevQuestion);
    QIcon ButtonInformation(help);

    ui->button_complete_test->setIcon(ButtonComplete);
    ui->button_next_question->setIcon(ButtonNextQues);
    ui->button_prev_question->setIcon(ButtonPrevQues);
    ui->button_help->setIcon(ButtonInformation);

    ui->radiobutton_null->setVisible(0);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    QFont font("Century Gothic", 14);
    ui->text_question->setFont(font);
}

// 1.2
void TestWindow::start_test()
{
    num_question = 1;
    get_question(num_question);
}

// 1.2
void TestWindow::set_enabled_button(int id_question)
{
    if(id_question == 1)
        ui->button_prev_question->setEnabled(0);
    else
        ui->button_prev_question->setEnabled(1);

    if(id_question == 10)
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
    if(num_question > 1 && num_question <= 10)
        num_question--;

    get_question(num_question);
    get_marked_answer(num_question, false);
}

void TestWindow::on_button_next_question_clicked()
{
    save_marked_answer(num_question);
    reset_answers();

    if(num_question >= 1 && num_question < 10)
        num_question++;

    get_question(num_question);
    //get_marked_answer(num_question, true);
}

// 1.2
void TestWindow::on_button_complete_test_clicked()
{
    save_marked_answer(num_question);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Завершить тестирование", "Вы уверены, что хотите завершить тестирование?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        determine_test_result();
        QMessageBox::information(this, "Результат тестирования", "Тестирование завершено!\nВсего вопросов: 10\n"
                                                                 "Правильных ответов: "     + QString::number(num_correct_answers) + "\n" +
                                                                 "Неправильных ответов: " + QString::number(num_wrong_answers) + "\n\n" +
                                                                 "Итоговая оценка: "           + QString::number(get_rating()),
                                       QMessageBox::Ok);
    }
    this->close();
}

// 1.2
void TestWindow::determine_test_result()
{
    num_correct_answers = 0, num_wrong_answers = 0;
    for(int i = 0; i < 10; i++)
    {
        if(current_answers[i] == correct_answers[i])
            num_correct_answers++;
        else
            num_wrong_answers++;
    }
}

// 1.2
int TestWindow::get_rating()
{
    return num_correct_answers < 5 ? 2 :
              num_correct_answers >= 5 && num_correct_answers < 6 ? 3 :
              num_correct_answers >= 6 && num_correct_answers < 8 ? 4 : 5;
}

void TestWindow::on_button_help_clicked()
{

}
