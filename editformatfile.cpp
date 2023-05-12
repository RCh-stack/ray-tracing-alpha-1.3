#include "editformatfile.h"
#include "ui_editformatfile.h"

#define UNUSED(x) [&x]{}()

EditFormatFile::EditFormatFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFormatFile)
{
    ui->setupUi(this);

    set_window_options();
}

EditFormatFile::~EditFormatFile()
{
    delete ui;
}

void EditFormatFile::set_window_options()
{
    QPixmap edit(":/icons/images/complete-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");

    QIcon ButtonEdit(edit);
    QIcon ButtonCancel(cancel);

    ui->button_save->setIcon(ButtonEdit);
    ui->button_cancel->setIcon(ButtonCancel);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void EditFormatFile::set_initial_data()
{
    ui->text_name->setText(get_name_format());
    ui->used->setChecked(get_used_format());
}

void EditFormatFile::on_button_save_clicked()
{
    if(ui->text_name->text().simplified().length() == 0)
        QMessageBox::critical(this, "Ошибка", "Не заполнено поле 'Наименование'!");
    else
        edit_selected_format();
}

void EditFormatFile::edit_selected_format()
{
    QSqlQuery query;
    query.prepare(update_format_file());
    query.bindValue(":id",          get_id_format());
    query.bindValue(":name",    ui->text_name->text().simplified());
    query.bindValue(":used",     ui->used->isChecked());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Формат файла изменен.");
    this->close();
}

void EditFormatFile::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void EditFormatFile::on_EditFormatFile_finished(int result)
{
    UNUSED(result);
}
