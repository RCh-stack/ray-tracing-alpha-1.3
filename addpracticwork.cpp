#include "addpracticwork.h"
#include "ui_addpracticwork.h"
#include "userhelpwindow.h"

#define UNUSED(x) [&x]{}()

AddPracticWork::AddPracticWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPracticWork)
{
    ui->setupUi(this);

    set_window_options();
    set_system_options();
}

AddPracticWork::~AddPracticWork()
{
    delete ui;
}

void AddPracticWork::set_window_options()
{
    QPixmap add(":/icons/images/complete-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonClose(close);
    QIcon ButtonInformation(help);

    ui->button_add->setIcon(ButtonAdd);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AddPracticWork::set_system_options()
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

void AddPracticWork::set_default_format_file(int id_format)
{
    QSqlQuery query;
    query.prepare(select_format_file());
    query.bindValue(":id_format",       id_format);

    query.exec();

    if(query.next())
        format_file = "*" + query.value("Name").toString();
}

// 1.4
void AddPracticWork::set_visible_information()
{
    ui->label_name_work->setText(get_name_work());
}

void AddPracticWork::on_button_path_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), get_format_file());
    ui->text_path->setText(filePath);
}

// 1.4
QString AddPracticWork::read_text_work_from_file(QString path)
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
void AddPracticWork::insert_new_work()
{
    QSqlQuery query;
    query.prepare(insert_lab_work());
    query.bindValue(":id_user",      get_id_user());
    query.bindValue(":id_work",     get_id_work());
    query.bindValue(":text_work",  read_text_work_from_file(get_path_to_file()));
    query.bindValue(":id_status",   2);
    query.bindValue(":note",         "");
    query.bindValue(":date",        QDate::currentDate());
    query.exec();

    QMessageBox::information(this, "Прикрепление работы", "Лабораторная работа успешно прикреплена.");
}

void AddPracticWork::on_button_help_clicked()
{
    UserHelpWindow *uhw = new UserHelpWindow;
    uhw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    uhw->open_file_by_code(6);

    uhw->exec();
    uhw->deleteLater();
}

void AddPracticWork::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}

// 1.4
void AddPracticWork::on_button_add_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Прикрепление работы", "Вы уверены, что хотите прикрепить работу к сдаче?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        set_path_to_file(ui->text_path->text());
        if(get_path_to_file().length() == 0)
            QMessageBox::critical(this, "Ошибка", "Путь к файлу некорректный!");
        else
        {
            insert_new_work();
            ui->button_path->setEnabled(0);
            ui->text_path->setEnabled(0);
        }
    }
}

// 1.4
void AddPracticWork::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Закрытие формы", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void AddPracticWork::on_AddPracticWork_finished(int result)
{
    UNUSED(result);
}
