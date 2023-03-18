#include "userteststatswindow.h"
#include "ui_userteststatswindow.h"

UserTestStatsWindow::UserTestStatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserTestStatsWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

UserTestStatsWindow::~UserTestStatsWindow()
{
    delete ui;
}

// 1.3
void UserTestStatsWindow::set_window_options()
{
    QPixmap exit(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonExit(exit);
    QIcon ButtonHelp(help);

    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonHelp);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->text_id_user->setEnabled(0);
    ui->text_user_name->setEnabled(0);
}

// 1.3
void UserTestStatsWindow::set_title_information()
{
    ui->text_id_user->setText(get_user_id());
    ui->text_user_name->setText(get_user_name());
}

// 1.3
QString UserTestStatsWindow::get_name_theme_test(int id_theme)
{
    QSqlQuery query;
    query.prepare(select_name_test());
    query.bindValue(":id_theme",    id_theme);
    query.exec();

    if(query.next())
        return query.value("Name").toString();

    return "";
}

// 1.3
void UserTestStatsWindow::output_table_information()
{
    QSqlQuery query;
    query.prepare(select_test_results_for_user());
    query.bindValue(":id_user",     get_user_id());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_stats->insertRow(i);
        ui->table_stats->setItem(i, 0, new QTableWidgetItem(query.value("ID_User").toString()));
        ui->table_stats->setItem(i, 1, new QTableWidgetItem(get_name_theme_test(query.value("ID_Theme").toInt())));
        ui->table_stats->setItem(i, 2, new QTableWidgetItem(query.value("Grade").toString()));
        ui->table_stats->setItem(i, 3, new QTableWidgetItem(query.value("Date").toString()));
    }
}

// 1.3
void UserTestStatsWindow::on_button_exit_clicked()
{
    this->close();
}

// 1.3
void UserTestStatsWindow::on_button_help_clicked()
{

}
