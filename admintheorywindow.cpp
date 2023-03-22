#include "admintheorywindow.h"
#include "ui_admintheorywindow.h"
#include "opentheoryfile.h"

AdminTheoryWindow::AdminTheoryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminTheoryWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
}

AdminTheoryWindow::~AdminTheoryWindow()
{
    delete ui;
}

// 1.5
void AdminTheoryWindow::set_window_options()
{
    QPixmap generation(":/icons/images/generation-attributes-button.png");
    QPixmap add(":/icons/images/add-file-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap options(":/icons/images/edit-lab-button.png");

    QIcon ButtonGeneration(generation);
    QIcon ButtonAdd(add);
    QIcon ButtonClose(close);
    QIcon ButtonInformation(help);
    QIcon ButtonOptions(options);

    ui->button_generation->setIcon(ButtonGeneration);
    ui->button_add->setIcon(ButtonAdd);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_options->setIcon(ButtonOptions);

    ui->text_num->setEnabled(0);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.5
int AdminTheoryWindow::get_num_page()
{
    QSqlQuery query;
    query.prepare(select_last_num_page());
    query.exec();

    if(query.next())
        return query.value("LastNum").toInt() + 1;

    return 1;
}

// 1.5
void AdminTheoryWindow::open_and_output_file(QString path)
{
    QFile file(path);
    QTextStream html(&file);
    QString text_file;
    if ((file.exists()) && (file.open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        text_file = html.readAll();
        ui->html_theory->setText(text_file);
        ui->text_theory->setPlainText(text_file);
        file.close();
    }
}

// 1.5
void AdminTheoryWindow::on_action_create_triggered()
{
    ui->text_num->setText(QString::number(get_num_page()));
    ui->text_name_file->clear();
    ui->text_name_theme->clear();
    ui->text_theory->clear();
    ui->html_theory->clear();
}

// 1.5
void AdminTheoryWindow::on_action_save_triggered()
{

}

// 1.5
void AdminTheoryWindow::on_text_theory_textChanged()
{
    QString current_text = ui->text_theory->toPlainText();
    ui->html_theory->setText(current_text);
}

// 1.5
void AdminTheoryWindow::on_button_generation_clicked()
{

}

// 1.5
void AdminTheoryWindow::on_button_add_clicked()
{

}

// 1.5
void AdminTheoryWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Закрытие формы", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}

void AdminTheoryWindow::on_button_help_clicked()
{

}

// 1.5
//void AdminTheoryWindow::on_comboBox_fonts_currentIndexChanged(const QString &arg1)
//{
//    QFont font(arg1, 14);
//    ui->text_theory->setFont(font);
//}

// 1.5
void AdminTheoryWindow::set_options_for_file(int id_page)
{
    QSqlQuery query;
    query.prepare(select_theorypage_by_id());
    query.bindValue(":id",     id_page);
    query.exec();

    if(query.next())
    {
        ui->text_name_file->setText(query.value("Name_Page").toString());
        ui->text_name_theme->setText(query.value("Name_Theme").toString());
        ui->text_num->setText(query.value("ID_Page").toString());
    }
}

// 1.5
void AdminTheoryWindow::on_action_open_resource_triggered()
{
    OpenTheoryFile *otw = new OpenTheoryFile;
    otw->output_data();
    otw->exec();

    set_id_page(otw->get_id_page());
    otw->deleteLater();

    open_and_output_file(get_path_file(get_id_page()));
    set_options_for_file(get_id_page());
}

// 1.5
QString AdminTheoryWindow::get_path_file(int id_page)
{
    QSqlQuery query;
    query.prepare(select_theorypage_by_id());
    query.bindValue(":id",     id_page);
    query.exec();

    if(query.next())
        return query.value("Path").toString();

    return "";
}

// 1.5
void AdminTheoryWindow::on_action_open_directory_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", QString(), "*.html ");
    open_and_output_file(filePath);
}

// 1.5
void AdminTheoryWindow::on_button_options_clicked()
{

}
