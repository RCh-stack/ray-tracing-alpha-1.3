#include "addpracticwork.h"
#include "ui_addpracticwork.h"

AddPracticWork::AddPracticWork(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPracticWork)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
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

// 1.4
void AddPracticWork::set_visible_information()
{
    ui->label_name_work->setText(get_name_work());
}

void AddPracticWork::on_button_path_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "*.cpp ");
    ui->text_path->setText(filePath);
}

void AddPracticWork::on_button_help_clicked()
{

}

// 1.4
void AddPracticWork::on_button_add_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Добавление лабораторной работы", "Вы уверены, что хотите прикрепить работу к сдаче?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        // sql func...
        return; // del
}

void AddPracticWork::on_button_exit_clicked()
{
    this->close();
}
