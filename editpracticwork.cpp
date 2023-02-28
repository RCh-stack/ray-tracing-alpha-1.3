#include "editpracticwork.h"
#include "ui_editpracticwork.h"

EditPracticWork::EditPracticWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditPracticWork)
{
    ui->setupUi(this);
    set_window_options();
    ui->label_name_work->setText("Уравнение траектории луча");
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

void EditPracticWork::on_button_path_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "*.cpp ");
    ui->text_path->setText(filePath);
}

void EditPracticWork::on_button_help_clicked()
{

}

void EditPracticWork::on_button_edit_clicked()
{

}

void EditPracticWork::on_button_exit_clicked()
{
    this->close();
}
