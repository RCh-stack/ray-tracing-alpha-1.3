#include "practicwindow.h"
#include "ui_practicwindow.h"
#include "addpracticwork.h"
#include "editpracticwork.h"

PracticWindow::PracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PracticWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

PracticWindow::~PracticWindow()
{
    delete ui;
}

void PracticWindow::set_window_options()
{
    QPixmap attach (":/icons/images/attach-button.png");
    QPixmap edit (":/icons/images/edit-lab-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap close(":/icons/images/exit-button.png");

    QIcon ButtonAttach(attach);
    QIcon ButtonEdit(edit);
    QIcon ButtonInformation(help);
    QIcon ButtonClose(close);

    ui->button_send_work->setIcon(ButtonAttach);
    ui->button_edit_work->setIcon(ButtonEdit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_exit->setIcon(ButtonClose);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.4
void PracticWindow::set_enabled_button(int id_status)
{
    if(id_status == 1)
    {
        ui->button_send_work->setEnabled(1);
        ui->button_edit_work->setEnabled(1);
    }
    else if(id_status == 2 || id_status == 4)
    {
        ui->button_send_work->setEnabled(0);
        ui->button_edit_work->setEnabled(0);
    }
    else
    {
        ui->button_send_work->setEnabled(0);
        ui->button_edit_work->setEnabled(1);
    }
}

// 1.4
int PracticWindow::get_id_status(QString id_user, int id_work)
{
    QSqlQuery query;
    query.prepare(select_id_status_work());
    query.bindValue(":id_user",     id_user);
    query.bindValue(":id_work",    id_work);
    query.exec();

    if(query.next())
        return query.value("Status").toInt();

    return 1;
}

// 1.4
void PracticWindow::output_table_of_contents(int row_index)
{
    open_file(get_lab_work(row_index + 1));
    ui->label_student->setText(get_fullname_user());
    ui->label_status->setText(get_status_work(get_id_user(), row_index + 1));
    set_enabled_button(get_id_status(get_id_user(), row_index + 1));
}

// 1.4
QString PracticWindow::get_lab_work(int id_work)
{
    QSqlQuery query;
    query.prepare(select_lab_work());
    query.bindValue(":id_theme",  id_work);
    query.exec();

    if(query.next())
        return query.value("Path").toString();

    return "";
}

// 1.4
QString PracticWindow::get_status_work(QString id_user, int id_work)
{
    QSqlQuery query;
    query.prepare(select_status_work());
    query.bindValue(":id_user",     id_user);
    query.bindValue(":id_work",    id_work);
    query.exec();

    if(query.next())
        return query.value("Status").toString();

    return "Не сдано";
}

void PracticWindow::open_file(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_lab_work->setText(str);
        file.close();
    }
}

void PracticWindow::on_comboBox_works_currentIndexChanged(int index)
{
    output_table_of_contents(index);
}

void PracticWindow::on_button_send_work_clicked()
{
    AddPracticWork *apw = new AddPracticWork;
    apw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    apw->exec();
}

void PracticWindow::on_button_edit_work_clicked()
{
    EditPracticWork *epw = new EditPracticWork;
    epw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    epw->exec();
}

void PracticWindow::on_button_help_clicked()
{

}

void PracticWindow::on_button_exit_clicked()
{
    this->close();
}
