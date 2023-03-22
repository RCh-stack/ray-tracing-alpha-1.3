#include "opentheoryfile.h"
#include "ui_opentheoryfile.h"

OpenTheoryFile::OpenTheoryFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenTheoryFile)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

OpenTheoryFile::~OpenTheoryFile()
{
    delete ui;
}

// 1.5
void OpenTheoryFile::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.5
void OpenTheoryFile::output_data()
{
    QSqlQuery query;
    query.prepare(select_all_theory_pages());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_themes->insertRow(i);
        ui->table_themes->setItem(i, 0, new QTableWidgetItem(query.value("ID_Page").toString()));
        ui->table_themes->setItem(i, 1, new QTableWidgetItem(query.value("Name_Theme").toString()));
    }
}

// 1.5
void OpenTheoryFile::on_table_themes_cellDoubleClicked(int row, int column)
{
    column = 0;
    QTableWidgetItem *item = ui->table_themes->item(row, column);
    set_id_page(item->text().toInt());
    this->close();
}
