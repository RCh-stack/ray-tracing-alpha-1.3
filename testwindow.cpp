#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    set_window_options();
    num_question = 1;
    // -- ДЛЯ ТЕСТА (ДЕМО) --
    QFont font("Century Gothic", 14);
    ui->text_question->setFont(font);

    ui->text_question->setText("1. Что понимают под термином визуализация(рендеринг)");
    ui->first_answer->setText("получение изображения по модели");
    ui->second_answer->setText("отражение объекта от света");
    ui->third_answer->setText("программа для моделирования");
    ui->fourth_answer->setText("процесс взаимодействия двух систем");
    // -- --
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

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void TestWindow::reset_answers()
{
    ui->first_answer->setChecked(0);
    ui->second_answer->setChecked(0);
    ui->third_answer->setChecked(0);
    ui->fourth_answer->setChecked(0);
}

void TestWindow::on_button_prev_question_clicked()
{
    // -- ДЛЯ ДЕМО --
    QFont font("Century Gothic", 12);
    ui->text_question->setFont(font);

    if(num_question > 0)
        num_question--;

    if(num_question == 1)
    {
        ui->first_answer->setChecked(1);
        ui->text_question->setText("1. Что понимают под термином визуализация(рендеринг)");
        ui->first_answer->setText("получение изображения по модели");
        ui->second_answer->setText("отражение объекта от света");
        ui->third_answer->setText("программа для моделирования");
        ui->fourth_answer->setText("процесс взаимодействия двух систем");
    }
    else if(num_question == 2)
    {
        ui->text_question->setText("2. Что относится к методам визуализации");
        ui->first_answer->setText("трассировка модели");
        ui->second_answer->setText("трассировка света");
        ui->third_answer->setText("трассировка кода");
        ui->fourth_answer->setText("трассировка пути");
    }
    else if(num_question == 3)
    {
        ui->text_question->setText("3. Где используется трассировка лучей?");
        ui->first_answer->setText("программирование процессоров");
        ui->second_answer->setText("разработка систем учета");
        ui->third_answer->setText("создание веб-приложений");
        ui->fourth_answer->setText("компьютерные игры");
    }
    else if(num_question == 4)
    {
        ui->text_question->setText("4. Где было получено первое изображение с трассировкой лучей?");
        ui->first_answer->setText("Университет Мэриленда");
        ui->second_answer->setText("Стэнфордский университет");
        ui->third_answer->setText("Оксфорд");
        ui->fourth_answer->setText("Йельский университет");
    }
    // -- --
}

void TestWindow::on_button_next_question_clicked()
{
    // -- ДЛЯ ДЕМО --
    QFont font("Century Gothic", 12);
    ui->text_question->setFont(font);

    if(num_question > 0 && num_question < 5)
        num_question++;

    if(num_question == 2)
    {
        ui->text_question->setText("2. Что относится к методам визуализации?");
        ui->first_answer->setText("трассировка модели");
        ui->second_answer->setText("трассировка света");
        ui->third_answer->setText("трассировка кода");
        ui->fourth_answer->setText("трассировка пути");
    }
    else if(num_question == 3)
    {
        ui->text_question->setText("3. Где используется трассировка лучей?");
        ui->first_answer->setText("программирование процессоров");
        ui->second_answer->setText("разработка систем учета");
        ui->third_answer->setText("создание веб-приложений");
        ui->fourth_answer->setText("компьютерные игры");
    }
    else if(num_question == 4)
    {
        ui->text_question->setText("4. Где было получено первое изображение с трассировкой лучей?");
        ui->first_answer->setText("Университет Мэриленда");
        ui->second_answer->setText("Стэнфордский университет");
        ui->third_answer->setText("Оксфорд");
        ui->fourth_answer->setText("Йельский университет");
    }
    else
    {
        ui->text_question->setText("5. Какой главный недостаток у алгоритма трассировки лучей?");
        ui->first_answer->setText("отсечение невидимых поверхностей");
        ui->second_answer->setText("распараллеливаемость вычислений");
        ui->third_answer->setText("производительность");
        ui->fourth_answer->setText("вычислительная сложность");
    }
    // -- --
}

void TestWindow::on_button_complete_test_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Завершить тестирование", "Вы уверены, что хотите завершить тестирование?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        QMessageBox::information(this, "Результат тестирования", "Тестирование завершено!\nВсего вопросов: 5\nПравильных ответов: 5\nИтоговая оценка: 5",
                                       QMessageBox::Ok);
    this->close();
}

void TestWindow::on_button_help_clicked()
{

}
