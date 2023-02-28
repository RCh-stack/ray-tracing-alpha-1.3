#include "edituserwindow.h"
#include "ui_edituserwindow.h"

EditUserWindow::EditUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserWindow)
{
    ui->setupUi(this);
    set_window_options();

    ui->text_code->setEnabled(0);
}

EditUserWindow::~EditUserWindow()
{
    delete ui;
}

void EditUserWindow::set_window_options()
{
    QPixmap edit(":/icons/images/edit-user-button.png");
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

void EditUserWindow::on_comboBox_roles_currentIndexChanged(int index)
{
    if(index == 0)
        ui->text_code->setEnabled(0);
    else
        ui->text_code->setEnabled(1);
}

void EditUserWindow::on_button_edit_clicked()
{

}

void EditUserWindow::on_button_exit_clicked()
{
    this->close();
}

void EditUserWindow::on_button_help_clicked()
{

}
