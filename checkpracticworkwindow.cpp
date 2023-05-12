#include "checkpracticworkwindow.h"
#include "ui_checkpracticworkwindow.h"
#include "formatnotewindow.h"
#include "adminhelpwindow.h"

CheckPracticWorkWindow::CheckPracticWorkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPracticWorkWindow)
{
    ui->setupUi(this);

    set_window_options();
    set_font_default();
    enabled_elements_in_form(false);
}

CheckPracticWorkWindow::~CheckPracticWorkWindow()
{
    delete ui;
}

// 1.6
void CheckPracticWorkWindow::set_window_options()
{
    QPixmap save(":/icons/images/save-button.png");
    QPixmap edit(":/icons/images/edit-lab-button.png");
    QPixmap exit(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap format(":/icons/images/format-note-button.png");
    QPixmap insert(":/icons/images/insert-note-button.png");
    QPixmap clear(":/icons/images/clear-text-button.png");

    QIcon ButtonSave(save);
    QIcon ButtonEdit(edit);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);
    QIcon ButtonFormatNote(format);
    QIcon ButtonInsertNote(insert);
    QIcon ButtonClear(clear);

    ui->button_save->setIcon(ButtonSave);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_note->setIcon(ButtonFormatNote);
    ui->button_enter_note->setIcon(ButtonInsertNote);
    ui->button_clear->setIcon(ButtonClear);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void CheckPracticWorkWindow::set_font_default()
{
    QFont font("Century Gothic", 10);
    ui->text_notes->setFont(font);
    ui->text_work->setFont(font);
}

// 1.6
void CheckPracticWorkWindow::enabled_elements_in_form(bool enable)
{
    ui->comboBox_statuses->setEnabled(enable);
    ui->text_notes->setEnabled(enable);
    ui->button_save->setEnabled(enable);
    ui->button_enter_note->setEnabled(enable);
    ui->button_clear->setEnabled(enable);
}

// 1.6
void CheckPracticWorkWindow::set_list_groups()
{
    ui->comboBox_groups->clear();

    QSqlQuery query;
    query.prepare(select_all_groups());
    query.exec();

    while(query.next())
        ui->comboBox_groups->addItem(query.value("Name_Group").toString());

    ui->comboBox_groups->removeItem(ui->comboBox_groups->count() - 1);
}

// 1.6
void CheckPracticWorkWindow::set_list_users(int id_group)
{
    ui->comboBox_users->clear();

    QSqlQuery query;
    query.prepare(select_all_users_with_selections());
    query.bindValue(":id_role",        1);
    query.bindValue(":id_group",     id_group);
    query.bindValue(":id_status",    1);

    query.exec();

    while(query.next())
        ui->comboBox_users->addItem(query.value("ID_User").toString() + " - " + query.value("Fullname").toString());

    set_id_user(QString::fromStdString(std::regex_replace(ui->comboBox_users->currentText().toStdString(), std::regex(R"([\D])"), "")));
}

// 1.6
void CheckPracticWorkWindow::set_list_statuses()
{
    ui->comboBox_statuses->clear();

    QSqlQuery query;
    query.prepare(select_all_statuses_works());
    query.exec();

    while(query.next())
        ui->comboBox_statuses->addItem(query.value("Name").toString());
}

// 1.6
void CheckPracticWorkWindow::set_list_works()
{
    ui->comboBox_works->clear();

    QSqlQuery query;
    query.prepare(select_all_themes_lab_works());
    query.exec();

    while(query.next())
        ui->comboBox_works->addItem(query.value("ID_Theme").toString() + ". " + query.value("Name").toString());
}

// 1.6
void CheckPracticWorkWindow::output_data_to_form()
{
    set_list_groups();
    set_list_statuses();
    set_list_users(ui->comboBox_groups->currentIndex() + 1);
    set_list_works();
}

// 1.6
void CheckPracticWorkWindow::output_text_work(QString id_user, int id_work)
{
    ui->text_work->clear();

    QSqlQuery query;
    query.prepare(select_lab_work());
    query.bindValue(":id_user",     id_user);
    query.bindValue(":id_work",    id_work);

    query.exec();

    if(query.next())
    {
        ui->text_work->setText(query.value("TextWork").toString());
        set_id_status(query.value("Status").toInt());
        ui->comboBox_statuses->setCurrentIndex(query.value("Status").toInt() - 1);
        ui->text_notes->setText(query.value("Note").toString());
    }
    else
        ui->comboBox_statuses->setCurrentIndex(0);
}

// 1.6
void CheckPracticWorkWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    set_list_users(index + 1);
    output_text_work(get_id_user(), get_id_work());
}

// 1.6
void CheckPracticWorkWindow::on_comboBox_users_currentIndexChanged(const QString &arg1)
{
    set_id_user(QString::fromStdString(std::regex_replace(arg1.toStdString(), std::regex(R"([\D])"), "")));
    output_text_work(get_id_user(), get_id_work());
}

// 1.6
void CheckPracticWorkWindow::on_comboBox_works_currentIndexChanged(int index)
{
    set_id_work(index + 1);
    output_text_work(get_id_user(), get_id_work());
}

// 1.6
void CheckPracticWorkWindow::on_comboBox_statuses_currentIndexChanged(int index)
{
    set_id_status(index + 1);
}

// 1.6
void CheckPracticWorkWindow::on_button_save_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Сохранить результат проверки данной работы?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QSqlQuery query;
        query.prepare(update_lab_work());
        query.bindValue(":id_user",          get_id_user());
        query.bindValue(":text_work",      ui->text_work->toPlainText());
        query.bindValue(":id_work",         get_id_work());
        query.bindValue(":id_status",       get_id_status());
        query.bindValue(":note",              ui->text_notes->toPlainText());
        query.exec();

        QMessageBox::information(this, "Уведомление", "Статус проверенной работы изменен.");

        enabled_elements_in_form(false);
    }
}

// 1.6
void CheckPracticWorkWindow::on_button_edit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Приступить к проверке данной работы?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        enabled_elements_in_form(true);
}

// 1.6
void CheckPracticWorkWindow::on_button_note_clicked()
{
    FormatNoteWindow *fnw = new FormatNoteWindow;
    fnw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    fnw->set_text_note(get_note());
    fnw->set_note_default();
    fnw->exec();

    set_note(fnw->get_text_note());

    fnw->deleteLater();
}

// 1.6
void CheckPracticWorkWindow::on_button_enter_note_clicked()
{
    ui->text_notes->insertPlainText("\n" + get_note());
}

void CheckPracticWorkWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

// 1.6
void CheckPracticWorkWindow::on_button_clear_clicked()
{
    ui->text_notes->clear();
}

// 1.6
void CheckPracticWorkWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}
