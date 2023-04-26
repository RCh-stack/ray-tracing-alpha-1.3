#include "instructionwindow.h"
#include "ui_instructionwindow.h"

InstructionWindow::InstructionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InstructionWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

InstructionWindow::~InstructionWindow()
{
    delete ui;
}

void InstructionWindow::set_window_options()
{
    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void InstructionWindow::open_file(int id_page)
{
    QSqlQuery query;
    query.prepare(select_help_file());
    query.bindValue(":id_page",  id_page);
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Справка", "Страница со справкой не найдена!");
    else
        output_table_of_contents(query.value("Path").toString());
}

void InstructionWindow::output_table_of_contents(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_instruction->setText(str);
        file.close();
    }
}
