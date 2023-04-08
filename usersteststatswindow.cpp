#include "usersteststatswindow.h"
#include "ui_usersteststatswindow.h"

UsersTestStatsWindow::UsersTestStatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersTestStatsWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
    set_enabled_combobox(false);
}

UsersTestStatsWindow::~UsersTestStatsWindow()
{
    delete ui;
}

// 1.6
void UsersTestStatsWindow::set_window_options()
{
    QPixmap exit(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap update(":/icons/images/update-button.png");

    QIcon ButtonExit(exit);
    QIcon ButtonHelp(help);
    QIcon ButtonUpdate(update);

    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonHelp);
    ui->button_update->setIcon(ButtonUpdate);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->table_list->setColumnWidth(0, 100);
    ui->table_list->setColumnWidth(1, 220);
    ui->table_list->setColumnWidth(2, 340);
    ui->table_list->setColumnWidth(3, 120);
}

// 1.6
void UsersTestStatsWindow::set_enabled_combobox(bool status)
{
    ui->comboBox_grades->setEnabled(status);
    ui->comboBox_groups->setEnabled(status);
    ui->comboBox_tests->setEnabled(status);
}

// 1.6
void UsersTestStatsWindow::clear_table()
{
    ui->table_list->clearContents();
    ui->table_list->setRowCount(0);
}

// 1.6
void UsersTestStatsWindow::output_data_in_lists_to_form()
{
    set_list_of_groups();
    set_list_of_tests();
}

// 1.6
int UsersTestStatsWindow::get_grade(QString grade)
{
    return grade == "неудовлетворительно" ? 2 :
              grade == "удовлетворительно" ? 3 :
              grade == "хорошо" ? 4 : 5;
}

// 1.6
void UsersTestStatsWindow::set_list_of_groups()
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
void UsersTestStatsWindow::set_list_of_tests()
{
    ui->comboBox_tests->clear();

    QSqlQuery query;
    query.prepare(select_all_tests());
    query.exec();

    while(query.next())
        ui->comboBox_tests->addItem(query.value("ID_Theme").toString() + ". " + query.value("Name").toString().simplified());
}

// 1.6
void UsersTestStatsWindow::output_list_tests()
{
    QSqlQuery query;
    query.prepare(select_all_tests_results());

    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_list->insertRow(i);
        ui->table_list->setItem(i, 0, new QTableWidgetItem(query.value("GroupName").toString()));
        ui->table_list->setItem(i, 1, new QTableWidgetItem(query.value("ID_User").toString() + " - " + query.value("Fullname").toString()));
        ui->table_list->setItem(i, 2, new QTableWidgetItem(query.value("NameTest").toString()));
        ui->table_list->setItem(i, 3, new QTableWidgetItem(query.value("Grade").toString()));
    }
}

// 1.6
void UsersTestStatsWindow::output_list_tests_with_selection(int id_group, int id_test, int grade)
{
    QSqlQuery query;
    query.prepare(select_all_tests_results_with_selections());
    query.bindValue(":id_group",    id_group);
    query.bindValue(":id_test",      id_test);
    query.bindValue(":grade",        grade);

    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_list->insertRow(i);
        ui->table_list->setItem(i, 0, new QTableWidgetItem(query.value("GroupName").toString()));
        ui->table_list->setItem(i, 1, new QTableWidgetItem(query.value("ID_User").toString() + " - " + query.value("Fullname").toString()));
        ui->table_list->setItem(i, 2, new QTableWidgetItem(query.value("NameTest").toString()));
        ui->table_list->setItem(i, 3, new QTableWidgetItem(query.value("Grade").toString()));
    }
}

// 1.6
void UsersTestStatsWindow::on_use_selection_clicked()
{
    clear_table();
    if(ui->use_selection->isChecked())
    {
        set_enabled_combobox(true);
        output_list_tests_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_tests->currentIndex() + 1, get_grade(ui->comboBox_grades->currentText()));
    }
    else
    {
        set_enabled_combobox(false);
        output_list_tests();
    }
}

// 1.6
void UsersTestStatsWindow::on_comboBox_groups_currentIndexChanged(int index)
{
    clear_table();
    output_list_tests_with_selection(index + 1, ui->comboBox_tests->currentIndex() + 1, get_grade(ui->comboBox_grades->currentText()));
}

// 1.6
void UsersTestStatsWindow::on_comboBox_tests_currentIndexChanged(int index)
{
    clear_table();
    output_list_tests_with_selection(ui->comboBox_groups->currentIndex() + 1, index + 1, get_grade(ui->comboBox_grades->currentText()));
}

// 1.6
void UsersTestStatsWindow::on_comboBox_grades_currentIndexChanged(const QString &arg1)
{
    clear_table();
    output_list_tests_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_tests->currentIndex() + 1, get_grade(arg1));
}

// 1.6
void UsersTestStatsWindow::on_button_update_clicked()
{
    clear_table();
    if(ui->use_selection->isChecked())
        output_list_tests_with_selection(ui->comboBox_groups->currentIndex() + 1, ui->comboBox_tests->currentIndex() + 1, get_grade(ui->comboBox_grades->currentText()));
    else
        output_list_tests();
}

void UsersTestStatsWindow::on_button_help_clicked()
{

}

// 1.6
void UsersTestStatsWindow::on_button_exit_clicked()
{
    this->close();
}
