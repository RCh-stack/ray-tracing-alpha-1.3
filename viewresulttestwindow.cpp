#include "viewresulttestwindow.h"
#include "ui_viewresulttestwindow.h"
#include "userhelpwindow.h"

ViewResultTestWindow::ViewResultTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewResultTestWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_enabled_elements_in_form();
}

ViewResultTestWindow::~ViewResultTestWindow()
{
    delete ui;
}

void ViewResultTestWindow::set_window_options()
{
    QPixmap prevQuestion (":/icons/images/prev-page.png");
    QPixmap nextQuestion (":/icons/images/next-page.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap exit(":/icons/images/exit-button.png");

    QIcon ButtonNextQues(nextQuestion);
    QIcon ButtonPrevQues(prevQuestion);
    QIcon ButtonInformation(help);
    QIcon ButtonExit(exit);

    ui->button_next_question->setIcon(ButtonNextQues);
    ui->button_prev_question->setIcon(ButtonPrevQues);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_exit->setIcon(ButtonExit);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    QFont font("Century Gothic", 14);
    ui->text_question->setFont(font);
}

void ViewResultTestWindow::set_enabled_elements_in_form()
{
    ui->first_answer->setEnabled(false);
    ui->second_answer->setEnabled(false);
    ui->third_answer->setEnabled(false);
    ui->fourth_answer->setEnabled(false);

    ui->text_first_answer->setEnabled(false);
    ui->text_second_answer->setEnabled(false);
    ui->text_third_answer->setEnabled(false);
    ui->text_fourth_answer->setEnabled(false);
}

void ViewResultTestWindow::set_enabled_button(int id_question)
{
    if(id_question == 1)
        ui->button_prev_question->setEnabled(false);
    else
        ui->button_prev_question->setEnabled(true);

    if(id_question == number_of_questions)
        ui->button_next_question->setEnabled(false);
    else
        ui->button_next_question->setEnabled(true);
}

void ViewResultTestWindow::reset_answers()
{
    ui->first_answer->setIcon(QIcon());
    ui->second_answer->setIcon(QIcon());
    ui->third_answer->setIcon(QIcon());
    ui->fourth_answer->setIcon(QIcon());

    QString standart_style("QLineEdit {color: #000000}");

    ui->text_first_answer->setStyleSheet(standart_style);
    ui->text_second_answer->setStyleSheet(standart_style);
    ui->text_third_answer->setStyleSheet(standart_style);
    ui->text_fourth_answer->setStyleSheet(standart_style);
}

int ViewResultTestWindow::get_number_of_questions(int id_test)
{
    QSqlQuery query;
    query.prepare(select_number_of_questions());
    query.bindValue(":id_theme",  id_test);
    query.exec();

    if(query.next())
        return query.value("NumberOfQuestions").toInt();

    return 10;
}

void ViewResultTestWindow::get_question(int id_question)
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

void ViewResultTestWindow::output_question(int id_question, QString question, QString answer1, QString answer2, QString answer3, QString answer4)
{
    ui->text_question->setText(QString::number(id_question) + ". " + question);
    ui->text_first_answer->setText(answer1);
    ui->text_second_answer->setText(answer2);
    ui->text_third_answer->setText(answer3);
    ui->text_fourth_answer->setText(answer4);

    set_enabled_button(id_question);
}

void ViewResultTestWindow::output_data_in_form()
{
    number_of_questions = get_number_of_questions(get_theme_test());
    num_question = 1;
    get_question(num_question);
    set_marked_answer(get_saved_answer(num_question), get_correct_answer(num_question));
}

int ViewResultTestWindow::get_saved_answer(int id_question)
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

int ViewResultTestWindow::get_correct_answer(int id_question)
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

QIcon ViewResultTestWindow::get_icon_checkbox(bool correct)
{
    if(correct)
        return QIcon{QPixmap{":/icons/images/checked-checkbox.png"}};
    else
        return QIcon{QPixmap{":icons/images/indeterminate-checkbox.png"}};
}

void ViewResultTestWindow::set_color_marks(int answer, bool correct)
{
    QString correct_answer_style("QLineEdit {background-color: rgb(204, 255, 229); color: #000000}");
    QString wrong_answer_style("QLineEdit {background-color: rgb(255, 102, 101); color: #000000}");

    if(answer == 1)
    {
        ui->first_answer->setIcon(get_icon_checkbox(correct));
        if(correct)
            ui->text_first_answer->setStyleSheet(correct_answer_style);
        else
            ui->text_first_answer->setStyleSheet(wrong_answer_style);
    }

    if(answer == 2)
    {
        ui->second_answer->setIcon(get_icon_checkbox(correct));
        if(correct)
            ui->text_second_answer->setStyleSheet(correct_answer_style);
        else
            ui->text_second_answer->setStyleSheet(wrong_answer_style);
    }

    if(answer == 3)
    {
        ui->third_answer->setIcon(get_icon_checkbox(correct));
        if(correct)
            ui->text_third_answer->setStyleSheet(correct_answer_style);
        else
            ui->text_third_answer->setStyleSheet(wrong_answer_style);
    }

    if(answer == 4)
    {
        ui->fourth_answer->setIcon(get_icon_checkbox(correct));
        if(correct)
            ui->text_fourth_answer->setStyleSheet(correct_answer_style);
        else
            ui->text_fourth_answer->setStyleSheet(wrong_answer_style);
    }
}

void ViewResultTestWindow::set_marked_answer(int answer, int correct_answer)
{
    reset_answers();
    if(answer == correct_answer)
        set_color_marks(answer, true);
    else
    {
        set_color_marks(answer, false);
        set_color_marks(correct_answer, true);
    }
}

void ViewResultTestWindow::on_button_prev_question_clicked()
{
    if(num_question > 1 && num_question <= number_of_questions)
        num_question--;

    get_question(num_question);
    set_marked_answer(get_saved_answer(num_question), get_correct_answer(num_question));
}

void ViewResultTestWindow::on_button_next_question_clicked()
{
    if(num_question >= 1 && num_question < number_of_questions)
        num_question++;

    get_question(num_question);
    set_marked_answer(get_saved_answer(num_question), get_correct_answer(num_question));
}

void ViewResultTestWindow::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(13);

    uhw->exec();
    uhw->deleteLater();
}

void ViewResultTestWindow::on_button_exit_clicked()
{
    this->close();
}

void ViewResultTestWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}
