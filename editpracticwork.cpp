#include "editpracticwork.h"
#include "ui_editpracticwork.h"
#include "userhelpwindow.h"

#define UNUSED(x) [&x]{}()

EditPracticWork::EditPracticWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPracticWork)
{
    ui->setupUi(this);

    set_window_options();
}

EditPracticWork::~EditPracticWork()
{
    delete ui;
}

void EditPracticWork::set_window_options()
{
    QPixmap edit(":/icons/images/complete-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonEdit(edit);
    QIcon ButtonClose(close);
    QIcon ButtonInformation(help);

    ui->button_edit->setIcon(ButtonEdit);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void EditPracticWork::set_system_options()
{
    QSqlQuery query;
    query.prepare(select_system_options());
    query.exec();

    if(query.next())
    {
        int id_format = query.value("NumberDefaultFormatFile").toInt();
        if(id_format > 0)
            set_default_format_file(id_format);

        if(query.value("UseSomeFormatFile").toBool())
            set_formats_files (query.value("FormatFileList").toString());
    }
}

void EditPracticWork::set_default_format_file(int id_format)
{
    QSqlQuery query;
    query.prepare(select_format_file());
    query.bindValue(":id_format",       id_format);

    query.exec();

    if(query.next())
        format_file = "*" + query.value("Name").toString();
}

// 1.4
void EditPracticWork::set_visible_information()
{
    ui->label_name_work->setText(get_name_work());
    ui->text_path->setText(get_path_to_file());
}

void EditPracticWork::on_button_path_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), get_format_file());
    ui->text_path->setText(filePath);
}

// 1.4
QString EditPracticWork::read_text_work_from_file(QString path)
{
    QFile file(path);
    QTextStream text(&file);
    QString text_work;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        text_work = text.readAll();
        file.close();
    }

    return text_work;
}

// 1.4
void EditPracticWork::update_select_work()
{
    QSqlQuery query;
    query.prepare(update_lab_work());
    query.bindValue(":id_user",      get_id_user());
    query.bindValue(":id_work",     get_id_work());
    query.bindValue(":text_work",  read_text_work_from_file(get_path_to_file()));
    query.bindValue(":id_status",   2);
    query.bindValue(":note",          "");
    query.bindValue(":date",           QDate::currentDate());
    query.exec();

    QMessageBox::information(this, "Редактирование работы", "Лабораторная работа успешно прикреплена.");
}

void EditPracticWork::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    uhw->exec();
    uhw->deleteLater();
}

// 1.4
void EditPracticWork::on_button_edit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Редактирование работы", "Вы уверены, что хотите прикрепить работу к сдаче?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        set_path_to_file(ui->text_path->text());
        update_select_work();
        ui->button_path->setEnabled(0);
        ui->text_path->setEnabled(0);
    }
}

// 1.4
void EditPracticWork::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Закрытие формы", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void EditPracticWork::on_EditPracticWork_finished(int result)
{
    UNUSED(result);
}
