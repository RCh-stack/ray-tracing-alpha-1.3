#include "changetestwindow.h"
#include "ui_changetestwindow.h"
#include "adminhelpwindow.h"

ChangeTestWindow::ChangeTestWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeTestWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_default_options();
}

ChangeTestWindow::~ChangeTestWindow()
{
    delete ui;
}

// 1.7
void ChangeTestWindow::set_window_options()
{
    QPixmap generation(":/icons/images/generation-attributes-button.png");
    QPixmap edit(":/icons/images/edit-test-button.png");
    QPixmap complete(":/icons/images/complete-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonEdit(edit);
    QIcon ButtonGeneration(generation);
    QIcon ButtonComplete(complete);
    QIcon ButtonExit(close);
    QIcon ButtonInformation(help);

    ui->button_generation->setIcon(ButtonGeneration);
    ui->button_edit_test->setIcon(ButtonEdit);
    ui->button_edit_question->setIcon(ButtonComplete);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.7
void ChangeTestWindow::set_default_options()
{
    ui->text_number->setEnabled(false);
    ui->text_num_question->setEnabled(false);

    ui->answer_null->setVisible(false);

    QFont font("Times New Roman", 12);
    ui->text_question->setFont(font);
}

// 1.7
void ChangeTestWindow::get_data_from_db()
{
    QSqlQuery query;
    query.prepare(select_theme_test());
    query.bindValue(":id_theme",    get_id_theme());
    query.exec();

    if(query.next())
    {
        ui->text_number->setText(QString::number(get_id_theme()));
        ui->text_num_question->setText(query.value("NumberOfQuestions").toString());
        ui->text_theme->setText(query.value("Name").toString());
        ui->comboBox_types->setCurrentIndex(query.value("NumberOfQuestions").toInt() == 10 ? 0 : 1);

        set_list_question_numbers();
        get_select_question(get_id_theme(), 1);
    }
}

// 1.7
void ChangeTestWindow::set_list_question_numbers()
{
    ui->comboBox_numbers->clear();

    int number_of_questions = ui->text_num_question->text().toInt();

    for(int i = 0; i < number_of_questions; i++)
        ui->comboBox_numbers->addItem(QString::number(i + 1));
}

// 1.7
void ChangeTestWindow::edit_test_in_database()
{
    QSqlQuery query;
    query.prepare(update_theme_test());
    query.bindValue(":id_theme",            get_id_theme());
    query.bindValue(":name_theme",      ui->text_theme->text().simplified());
    query.bindValue(":num_questions",   ui->text_num_question->text().toInt());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Изменения в теме теста внесены в базу данных.");

    set_list_question_numbers();
}

// 1.7
void ChangeTestWindow::on_button_generation_clicked()
{
    ui->text_number->setText(QString::number(get_id_theme()));
    ui->text_theme->setText("Тестирование по теме №" + QString::number(get_id_theme()));
}

// 1.7
void ChangeTestWindow::on_button_edit_test_clicked()
{
    if(ui->text_theme->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с наименованием теста!");
    else if(ui->text_number->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с номером теста!");
    else if(ui->text_num_question->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с количеством вопросов к тесту!");
    else
        edit_test_in_database();
}

// 1.7
void ChangeTestWindow::on_comboBox_types_currentIndexChanged(int index)
{
    if(index == 0)
        ui->text_num_question->setText("10");
    else
        ui->text_num_question->setText("20");
}

// 1.7
void ChangeTestWindow::on_comboBox_numbers_currentIndexChanged(int index)
{
     get_select_question(get_id_theme(), index + 1);
}

// 1.7
int ChangeTestWindow::get_selected_answer()
{
    return ui->right_1->isChecked() ? 1 :
              ui->right_2->isChecked() ? 2 :
              ui->right_3->isChecked() ? 3 :
              ui->right_4->isChecked() ? 4 : 0;
}

// 1.7
void ChangeTestWindow::get_select_question(int id_theme, int id_question)
{
    QSqlQuery query;
    query.prepare(select_question());
    query.bindValue(":id_theme",     id_theme);
    query.bindValue(":id_question",  id_question);
    query.exec();

    if(query.next())
    {
        ui->text_question->setText(query.value("Text_Question").toString());
        ui->text_answer_1->setText(query.value("Answer_1").toString());
        ui->text_answer_2->setText(query.value("Answer_2").toString());
        ui->text_answer_3->setText(query.value("Answer_3").toString());
        ui->text_answer_4->setText(query.value("Answer_4").toString());
        set_flag_correct_answer(query.value("Right_Answer").toInt());
    }
    else
    {
        ui->text_question->clear();
        ui->text_answer_1->clear();
        ui->text_answer_2->clear();
        ui->text_answer_3->clear();
        ui->text_answer_4->clear();
        ui->answer_null->setChecked(true);
    }
}

// 1.7
void ChangeTestWindow::set_flag_correct_answer(int id_right_answer)
{
    if(id_right_answer == 1)
        ui->right_1->setChecked(true);
    else if(id_right_answer == 2)
        ui->right_2->setChecked(true);
    else if(id_right_answer == 3)
        ui->right_3->setChecked(true);
    else if(id_right_answer == 4)
        ui->right_4->setChecked(true);
    else
        ui->answer_null->setChecked(true);
}

// 1.7
void ChangeTestWindow::on_button_edit_question_clicked()
{
    if(ui->text_question->toPlainText().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с вопросом");
    else if(ui->text_answer_1->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с первым номером ответа!");
    else if(ui->text_answer_2->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле со вторым номером ответа!");
    else if(ui->text_answer_3->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с третьим номером ответа!");
    else if(ui->text_answer_4->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с четвертым номером ответа!");
    else if(get_selected_answer() == 0)
        QMessageBox::critical(this, "Уведомление", "Не выбран правильный для вопроса ответ!");
    else
        edit_question_from_test();
}

// 1.7
void ChangeTestWindow::edit_question_from_test()
{
    QSqlQuery query;
    query.prepare(update_question());
    query.bindValue(":id_theme",        get_id_theme());
    query.bindValue(":id_question",     ui->comboBox_numbers->currentIndex() + 1);
    query.bindValue(":text_question",  ui->text_question->toPlainText().simplified());
    query.bindValue(":answer_1",        ui->text_answer_1->text().simplified());
    query.bindValue(":answer_2",        ui->text_answer_2->text().simplified());
    query.bindValue(":answer_3",        ui->text_answer_3->text().simplified());
    query.bindValue(":answer_4",        ui->text_answer_4->text().simplified());
    query.bindValue(":right_answer",   get_selected_answer());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Изменения в вопросе к тесту внесены.");
}

void ChangeTestWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void ChangeTestWindow::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}

// 1.7
void ChangeTestWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}
