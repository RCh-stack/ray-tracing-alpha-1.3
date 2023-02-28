#include "addpracticwork.h"
#include "ui_addpracticwork.h"

AddPracticWork::AddPracticWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPracticWork)
{
    ui->setupUi(this);
    set_window_options();
    ui->label_name_work->setText("Уравнение траектории луча");
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

void AddPracticWork::on_button_path_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "*.cpp ");
    ui->text_path->setText(filePath);
}

void AddPracticWork::on_button_help_clicked()
{

}

void AddPracticWork::on_button_add_clicked()
{

}

void AddPracticWork::on_button_exit_clicked()
{
    this->close();
}
