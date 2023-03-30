#include "editingtoolswindow.h"
#include "ui_editingtoolswindow.h"

EditingToolsWindow::EditingToolsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditingToolsWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(1);

    set_window_options();
    set_default_edit_options();
}

EditingToolsWindow::~EditingToolsWindow()
{
    delete ui;
}

// 1.5
void EditingToolsWindow::set_window_options()
{
    QPixmap save (":/icons/images/save-button.png");
    QPixmap exit (":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonSave(save);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);

    ui->button_save->setIcon(ButtonSave);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.5
void EditingToolsWindow::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked())
        set_default_edit_options();
    else
        enabled_elements_in_form(true);
}

// 1.5
void EditingToolsWindow::enabled_elements_in_form(bool enable)
{
    ui->comboBox->setEnabled(enable);
    ui->fontComboBox->setEnabled(enable);
    ui->spinBox->setEnabled(enable);
}

// 1.5
void EditingToolsWindow::set_default_edit_options()
{
    set_size_font(12);
    set_name_font("Times New Roman");
    set_id_font_color(0);
    // -----------------------------------------------
    ui->comboBox->setCurrentIndex(get_id_font_color());
    ui->fontComboBox->setCurrentFont(QFont(get_name_font(), get_size_font()));
    enabled_elements_in_form(false);
}

void EditingToolsWindow::on_button_help_clicked()
{

}

// 1.5
void EditingToolsWindow::on_button_save_clicked()
{
    set_id_font_color(ui->comboBox->currentIndex());
    set_name_font(ui->fontComboBox->currentText());
    set_size_font(ui->spinBox->value());

    QMessageBox::information(this, "Уведомление", "Настройки ввода успешно сохранены.");
    this->close();
}

// 1.5
void EditingToolsWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}
