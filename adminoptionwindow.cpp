#include "adminoptionwindow.h"
#include "ui_adminoptionwindow.h"
#include "adminhelpwindow.h"
#include "listformatfile.h"

AdminOptionWindow::AdminOptionWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOptionWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminOptionWindow::~AdminOptionWindow()
{
    delete ui;
}

// 1.3
void AdminOptionWindow::set_window_options()
{
    QPixmap save(":/icons/images/save-button.png");
    QPixmap cancel(":/icons/images/cancel-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonSave(save);
    QIcon ButtonCancel(cancel);
    QIcon ButtonInformation(help);

    ui->button_save->setIcon(ButtonSave);
    ui->button_cancel->setIcon(ButtonCancel);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AdminOptionWindow::set_enabled_elements_in_form()
{
    if(ui->use_select_in_list->isChecked())
        ui->value_color_selected->setEnabled(true);
    else
        ui->value_color_selected->setEnabled(false);

    if(ui->use_some_format->isChecked())
        ui->button_all_format->setEnabled(true);
    else
        ui->button_all_format->setEnabled(false);

    if(ui->use_hints->isChecked())
        ui->value_hints->setEnabled(true);
    else
        ui->value_hints->setEnabled(false);

    if(ui->use_time->isChecked())
        ui->value_time->setEnabled(true);
    else
        ui->value_time->setEnabled(false);
}

void AdminOptionWindow::set_combobox_values()
{
    QSqlQuery query;
    query.prepare(select_all_formats_files());
    query.exec();

    while(query.next())
        ui->list_default_format->addItem(query.value("Name").toString());

    query.prepare(select_all_rgb_colors());
    query.exec();

    while(query.next())
        ui->value_color_selected->addItem(query.value("Name").toString());
}

void AdminOptionWindow::set_default_options()
{
    set_combobox_values();

    QSqlQuery query;
    query.prepare(select_system_options());

    query.exec();

    if(query.next())
    {
        ui->use_more_theory->setChecked(query.value("UseMoreTheoryPages").toBool());
        ui->value_primary_page->setValue(query.value("NumberPrimaryPage").toInt());
        ui->use_copy_select_page->setChecked(query.value("UseCopySelectPage").toBool());
        ui->use_select_in_list->setChecked(query.value("UseSelectPageInList").toBool());
        ui->value_color_selected->setCurrentIndex(query.value("NumberColorSelectedPage").toInt() - 1);
        ui->use_deadline->setChecked(query.value("UseDeadLineWork").toBool());
        ui->list_default_format->setCurrentIndex(query.value("NumberDefaultFormatFile").toInt() - 1);
        ui->use_some_format->setChecked(query.value("UseSomeFormatFile").toBool());
        ui->allow_delivery->setChecked(query.value("AllowDeliveryWorkAfterEndTerm").toBool());
        ui->use_hints->setChecked(query.value("UseHintsInTest").toBool());
        ui->value_hints->setValue(query.value("NumberHints").toInt());
        ui->view_stats->setChecked(query.value("UseViewResult").toBool());
        ui->repeat_passage->setChecked(query.value("UseRepeatPassage").toBool());
        ui->use_time->setChecked(query.value("UseTimer").toBool());
        ui->value_time->setTime(query.value("TimerValue").toTime());
    }

    set_enabled_elements_in_form();
}

void AdminOptionWindow::on_button_all_format_clicked()
{
    ListFormatFile *lff = new ListFormatFile;
    lff->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    lff->output_data();

    lff->exec();
    lff->deleteLater();
}

void AdminOptionWindow::on_button_save_clicked()
{
    // проверки

    save_system_options();
}

void AdminOptionWindow::save_system_options()
{
    QSqlQuery query;
    query.prepare(update_system_options());
    query.bindValue(":use_more_theory",                 ui->use_more_theory->isChecked());
    query.bindValue(":number_primary",                  ui->value_primary_page->value());
    query.bindValue(":use_copy_select",                  ui->use_copy_select_page->isChecked());
    query.bindValue(":use_select_page",                  ui->use_select_in_list->isChecked());
    query.bindValue(":number_color_select",            ui->value_color_selected->currentIndex() + 1);
    query.bindValue(":use_deadline",                       ui->use_deadline->isChecked());
    query.bindValue(":number_format_file",              ui->list_default_format->currentIndex() + 1);
    query.bindValue(":use_some_format",                ui->use_some_format->isChecked());
    query.bindValue(":format_file",                           get_format_files());
    query.bindValue(":allow_delivery_work",             ui->allow_delivery->isChecked());
    query.bindValue(":use_hints",                             ui->use_hints->isChecked());
    query.bindValue(":number_hints",                       ui->value_hints->value());
    query.bindValue(":use_view_result",                   ui->view_stats->isChecked());
    query.bindValue(":use_repeat_passage",            ui->repeat_passage->isChecked());
    query.bindValue(":use_timer",                            ui->use_time->isChecked());
    query.bindValue(":value_timer",                         ui->value_time->time());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Настройки сохранены.");
    set_enabled_elements_in_form();
}

QString AdminOptionWindow::get_format_files()
{
    QString formats;

    QSqlQuery query;
    query.prepare(select_used_formats_files());
    query.exec();

    while(query.next())
    {
        QString format = query.value("Name").toString();
        if(!formats.isEmpty())
            formats.append("; ");
        formats.append("*.").append(format);
    }

    return formats;
}

void AdminOptionWindow::on_button_help_clicked()
{
    AdminHelpWindow *ahw = new AdminHelpWindow;
    ahw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ahw->open_file_by_code(0); // -- УКАЗАТЬ НУЖНЫЙ --

    ahw->exec();
    ahw->deleteLater();
}

void AdminOptionWindow::on_button_cancel_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void AdminOptionWindow::on_use_some_format_clicked()
{
    if(ui->use_some_format->isChecked())
        ui->button_all_format->setEnabled(true);
    else
        ui->button_all_format->setEnabled(false);
}

void AdminOptionWindow::on_use_select_in_list_clicked()
{
    if(ui->use_select_in_list->isChecked())
        ui->value_color_selected->setEnabled(true);
    else
        ui->value_color_selected->setEnabled(false);
}

void AdminOptionWindow::on_use_hints_clicked()
{
    if(ui->use_hints->isChecked())
        ui->value_hints->setEnabled(true);
    else
        ui->value_hints->setEnabled(false);
}

void AdminOptionWindow::on_use_time_clicked()
{
    if(ui->use_time->isChecked())
        ui->value_time->setEnabled(true);
    else
        ui->value_time->setEnabled(false);
}
