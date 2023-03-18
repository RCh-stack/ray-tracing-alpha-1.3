#include "practicwindow.h"
#include "ui_practicwindow.h"
#include "addpracticwork.h"
#include "editpracticwork.h"

PracticWindow::PracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PracticWindow)
{
    ui->setupUi(this);
    set_window_options();
    ui->label_student->setText("Тест_Студент");
    output_table_of_contents(0);
}

PracticWindow::~PracticWindow()
{
    delete ui;
}

void PracticWindow::set_window_options()
{
    QPixmap attach (":/icons/images/attach-button.png");
    QPixmap edit (":/icons/images/edit-lab-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap close(":/icons/images/exit-button.png");

    QIcon ButtonAttach(attach);
    QIcon ButtonEdit(edit);
    QIcon ButtonInformation(help);
    QIcon ButtonClose(close);

    ui->button_send_work->setIcon(ButtonAttach);
    ui->button_edit_work->setIcon(ButtonEdit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_exit->setIcon(ButtonClose);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

void PracticWindow::output_table_of_contents(int row_index)
{
    if(row_index == 0)
        open_file(":/lab_files/files/lab/first_lab.html");
    else if(row_index == 1)
        open_file(":/lab_files/files/lab/second_lab.html");
    else if(row_index == 2)
        open_file(":/lab_files/files/lab/third_lab.html");
}

void PracticWindow::open_file(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        QString str = html.readAll();
        ui->text_lab_work->setText(str);
        file.close();
    }
}

void PracticWindow::on_comboBox_works_currentIndexChanged(int index)
{
    output_table_of_contents(index);
}

void PracticWindow::on_button_send_work_clicked()
{
    AddPracticWork *apw = new AddPracticWork;
    apw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    apw->exec();
}

void PracticWindow::on_button_edit_work_clicked()
{
    EditPracticWork *epw = new EditPracticWork;
    epw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    epw->exec();
}

void PracticWindow::on_button_help_clicked()
{

}

void PracticWindow::on_button_exit_clicked()
{
    this->close();
}
