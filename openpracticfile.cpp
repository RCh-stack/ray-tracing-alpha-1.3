#include "openpracticfile.h"
#include "ui_openpracticfile.h"

OpenPracticFile::OpenPracticFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenPracticFile)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

OpenPracticFile::~OpenPracticFile()
{
    delete ui;
}

// 1.6
void OpenPracticFile::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);

    ui->table_themes->setColumnWidth(0, 110);
    ui->table_themes->setColumnWidth(1, 380);
}

// 1.6
void OpenPracticFile::output_data()
{
    QSqlQuery query;
    query.prepare(select_all_themes_lab_works());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_themes->insertRow(i);
        ui->table_themes->setItem(i, 0, new QTableWidgetItem(query.value("ID_Theme").toString()));
        ui->table_themes->setItem(i, 1, new QTableWidgetItem(query.value("Name").toString()));
    }
}

// 1.6
void OpenPracticFile::on_table_themes_cellDoubleClicked(int row, int column)
{
    column = 0;
    QTableWidgetItem *item = ui->table_themes->item(row, column);
    set_id_work(item->text().toInt());
    this->close();
}
