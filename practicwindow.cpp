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

    QFont font("Century Gothic", 10);
    ui->text_note->setFont(font);
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
    QPixmap update(":/icons/images/update-button.png");

    QIcon ButtonAttach(attach);
    QIcon ButtonEdit(edit);
    QIcon ButtonInformation(help);
    QIcon ButtonClose(close);
    QIcon ButtonUpdate(update);

    ui->button_send_work->setIcon(ButtonAttach);
    ui->button_edit_work->setIcon(ButtonEdit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_update->setIcon(ButtonUpdate);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void PracticWindow::set_list_works()
{
    ui->comboBox_works->clear();

    QSqlQuery query;
    query.prepare(select_all_themes_lab_works());
    query.exec();

    while(query.next())
        ui->comboBox_works->addItem(query.value("ID_Theme").toString() + ". " + query.value("Name").toString().simplified());
}

// 1.4
void PracticWindow::set_enabled_button(int id_status)
{
    if(id_status == 1)
    {
        ui->button_send_work->setEnabled(1);
        ui->button_edit_work->setEnabled(0);
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
    update_status_work();
}

// 1.4
QString PracticWindow::get_lab_work(int id_work)
{
    QSqlQuery query;
    query.prepare(select_theme_lab_work());
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

// 1.6
QString PracticWindow::get_note(QString id_user, int id_work)
{
    QSqlQuery query;
    query.prepare(select_lab_work());
    query.bindValue(":id_user",     id_user);
    query.bindValue(":id_work",    id_work);

    query.exec();

    if(query.next())
        return query.value("Note").toString();

    return "";
}

void PracticWindow::open_file(QString path)
{
    if(path[0] != ':')
        path = QDir().absolutePath() + path;
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
    apw->set_id_user(get_id_user());
    apw->set_name_work(ui->comboBox_works->currentText());
    apw->set_id_work(ui->comboBox_works->currentIndex() + 1);
    apw->set_visible_information();

    apw->setModal(true);
    apw->show();

    connect(apw, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
}

// 1.4
void PracticWindow::close_add_edit_window(int result)
{
    if(result == 0)
        update_status_work();
}

// 1.6
void PracticWindow::update_status_work()
{
    int current_lab = ui->comboBox_works->currentIndex() + 1;
    ui->label_status->setText(get_status_work(get_id_user(), current_lab));
    ui->text_note->setText(get_note(get_id_user(), current_lab));
    set_enabled_button(get_id_status(get_id_user(), current_lab));
}

// 1.4
void PracticWindow::on_button_edit_work_clicked()
{
    EditPracticWork *epw = new EditPracticWork;
    epw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    epw->set_id_user(get_id_user());
    epw->set_name_work(ui->comboBox_works->currentText());
    epw->set_id_work(ui->comboBox_works->currentIndex() + 1);
    epw->set_visible_information();

    epw->setModal(true);
    epw->show();

    connect(epw, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
}

void PracticWindow::on_button_help_clicked()
{

}

void PracticWindow::on_button_exit_clicked()
{
    this->close();
}

// 1.4
void PracticWindow::on_button_update_clicked()
{
    update_status_work();
}
