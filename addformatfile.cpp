#include "addformatfile.h"
#include "ui_addformatfile.h"

#define UNUSED(x) [&x]{}()

AddFormatFile::AddFormatFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFormatFile)
{
    ui->setupUi(this);

    set_window_options();
}

AddFormatFile::~AddFormatFile()
{
    delete ui;
}

void AddFormatFile::set_window_options()
{
    QPixmap add(":/icons/images/complete-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonCancel(cancel);

    ui->button_save->setIcon(ButtonAdd);
    ui->button_cancel->setIcon(ButtonCancel);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AddFormatFile::on_button_save_clicked()
{
    if(ui->text_name->text().simplified().length() == 0)
        QMessageBox::critical(this, "Ошибка", "Не заполнено поле 'Наименование'!");
    else
        add_new_format();
}

void AddFormatFile::add_new_format()
{
    QSqlQuery query;
    query.prepare(insert_format_file());
    query.bindValue(":name",    ui->text_name->text().simplified());
    query.bindValue(":used",     ui->used->isChecked());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Новый формат для входного файла добавлен.");

    ui->text_name->clear();
    ui->used->setChecked(false);
}

void AddFormatFile::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void AddFormatFile::on_AddFormatFile_finished(int result)
{
    UNUSED(result);
}
