#include "listformatfile.h"
#include "ui_listformatfile.h"
#include "addformatfile.h"
#include "editformatfile.h"
#include "adminhelpwindow.h"

ListFormatFile::ListFormatFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListFormatFile)
{
    ui->setupUi(this);

    set_window_options();
}

ListFormatFile::~ListFormatFile()
{
    delete ui;
}

void ListFormatFile::set_window_options()
{
    QPixmap add(":/icons/images/download.png");
    QPixmap edit(":/icons/images/edit-lab-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap close(":/icons/images/exit-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonInformation(help);
    QIcon ButtonClose(close);

    ui->button_help->setIcon(ButtonInformation);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_add->setIcon(ButtonAdd);
    ui->button_exit->setIcon(ButtonClose);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void ListFormatFile::output_data()
{
    clear_table();

    QSqlQuery query;
    query.prepare(select_all_formats_files());
    query.exec();

    for(int i = 0; query.next(); i++)
    {
        ui->table_formats->insertRow(i);
        ui->table_formats->setItem(i, 0, new QTableWidgetItem(query.value("ID_Format").toString()));
        ui->table_formats->setItem(i, 1, new QTableWidgetItem(query.value("Name").toString()));
        ui->table_formats->setItem(i, 2, new QTableWidgetItem(query.value("Used").toString()));

        if(query.value("Used").toBool())
        {
            ui->table_formats->item(i, 0)->setBackgroundColor(QColor(204, 255, 229));
            ui->table_formats->item(i, 1)->setBackgroundColor(QColor(204, 255, 229));
        }
        else
        {
            ui->table_formats->item(i, 0)->setBackgroundColor(QColor(255, 102, 101));
            ui->table_formats->item(i, 1)->setBackgroundColor(QColor(255, 102, 101));
        }
    }
}

void ListFormatFile::clear_table()
{
    ui->table_formats->clearContents();
    ui->table_formats->setRowCount(0);

    ui->table_formats->setColumnHidden(2, true);
    QTableWidgetItem *headerItem = new QTableWidgetItem("Used");
    ui->table_formats->setHorizontalHeaderItem(2, headerItem);
}

void ListFormatFile::on_button_add_clicked()
{
    AddFormatFile *aff = new AddFormatFile;
    aff->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    aff->setModal(true);
    aff->show();

    connect(aff, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
}

void ListFormatFile::on_button_edit_clicked()
{
    EditFormatFile *eff = new EditFormatFile;
    eff->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    eff->set_id_format(ui->table_formats->item(ui->table_formats->currentRow(), 0)->text().toInt());
    eff->set_name_format(ui->table_formats->item(ui->table_formats->currentRow(), 1)->text());
    eff->set_used_format(ui->table_formats->item(ui->table_formats->currentRow(), 2)->text().toInt());

    eff->setModal(true);
    eff->set_initial_data();
    eff->show();

    connect(eff, SIGNAL(finished(int)), SLOT(close_add_edit_window(int)));
}

void ListFormatFile::close_add_edit_window(int result)
{
    if(result == 0)
        output_data();
}

void ListFormatFile::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void ListFormatFile::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void ListFormatFile::keyPressEvent(QKeyEvent *event)
{
     if(event->key() == Qt::Key_F1)
        on_button_help_clicked();
    else
        QDialog::keyPressEvent(event);
}
