#include "checkpracticworkwindow.h"
#include "ui_checkpracticworkwindow.h"

CheckPracticWorkWindow::CheckPracticWorkWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckPracticWorkWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
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

    QIcon ButtonSave(save);
    QIcon ButtonEdit(edit);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);

    ui->button_save->setIcon(ButtonSave);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
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
    query.prepare(select_all_lab_works());
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
void CheckPracticWorkWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    set_list_users(index + 1);
}

void CheckPracticWorkWindow::on_comboBox_users_currentIndexChanged(int index)
{

}

void CheckPracticWorkWindow::on_comboBox_works_currentIndexChanged(int index)
{

}

void CheckPracticWorkWindow::on_button_save_clicked()
{

}

void CheckPracticWorkWindow::on_button_edit_clicked()
{

}

void CheckPracticWorkWindow::on_button_help_clicked()
{

}

// 1.6
void CheckPracticWorkWindow::on_button_exit_clicked()
{
    this->close();
}
