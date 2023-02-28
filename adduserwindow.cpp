#include "adduserwindow.h"
#include "ui_adduserwindow.h"

AddUserWindow::AddUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserWindow)
{
    ui->setupUi(this);
    set_window_options();

    ui->text_code->setEnabled(0);
}

AddUserWindow::~AddUserWindow()
{
    delete ui;
}

void AddUserWindow::set_window_options()
{
    QPixmap add(":/icons/images/add-user-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonClose(close);
    QIcon ButtonInformation(help);

    ui->buttod_add->setIcon(ButtonAdd);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void AddUserWindow::on_comboBox_roles_currentIndexChanged(int index)
{
    if(index == 0)
        ui->text_code->setEnabled(0);
    else
        ui->text_code->setEnabled(1);
}

void AddUserWindow::on_buttod_add_clicked()
{

}

void AddUserWindow::on_button_exit_clicked()
{
    this->close();
}

void AddUserWindow::on_button_help_clicked()
{

}
