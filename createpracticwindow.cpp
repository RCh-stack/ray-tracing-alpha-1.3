#include "createpracticwindow.h"
#include "ui_createpracticwindow.h"
#include "editingtoolswindow.h"

CreatePracticWindow::CreatePracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePracticWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
    set_default_options();
}

CreatePracticWindow::~CreatePracticWindow()
{
    delete ui;
}

// 1.6
void CreatePracticWindow::set_window_options()
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

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void CreatePracticWindow::set_font_options()
{
    ui->text_work->setFont(QFont(get_name_font(), get_size_font()));
    ui->text_work->setTextColor(QColor::fromRgb(255, 255, 255));
}

// 1.6
int CreatePracticWindow::get_num_work()
{
    QSqlQuery query;
    query.prepare(select_last_num_work());
    query.exec();

    if(query.next())
        return query.value("LastNum").toInt() + 1;

    return 1;
}

// 1.6
void CreatePracticWindow::on_text_work_textChanged()
{
    QString current_text = ui->text_work->toPlainText();
    ui->html_work->setText(current_text);
}

// 1.6
void CreatePracticWindow::set_default_options()
{
    ui->text_number->setEnabled(0);
    ui->text_path->setEnabled(0);

    QFont font("Times New Roman", 12);
    ui->text_work->setFont(font);
    ui->html_work->setFont(font);
}

// 1.6
void CreatePracticWindow::on_button_generation_clicked()
{
    QString id_num_page = QString::number(get_num_work());
    ui->text_number->setText(id_num_page);
    ui->text_path->setText("/files/lab/");

    if(ui->text_name_file->text().simplified().length() == 0)
        ui->text_name_file->setText("filename");

    if(ui->text_name_work->text().simplified().length() == 0)
        ui->text_name_work->setText("Лабораторная работа №" + id_num_page);
}

// 1.6
QString CreatePracticWindow::generate_path_file(QString filename)
{
    return "/files/lab/" + filename + ".html";
}

// 1.6
void CreatePracticWindow::save_text_in_file()
{
    QString full_path_to_file = QDir().absolutePath() + generate_path_file(ui->text_name_file->text().simplified());

    QFile file(full_path_to_file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->text_work->toPlainText() << "\n";
    file.close();
}

// 1.6
void CreatePracticWindow::on_button_add_clicked()
{
    if(ui->text_name_file->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с наименованием файла!");
    else if(ui->text_name_work->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с наименованием работы!");
    else if(ui->text_number->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с номером страницы!");
    else
        add_file_in_database();
}

// 1.6
void CreatePracticWindow::add_file_in_database()
{
    save_text_in_file();

    QSqlQuery query;
    query.prepare(insert_theme_work());
    query.bindValue(":id_theme",        ui->text_number->text().simplified());
    query.bindValue(":name_theme",  ui->text_name_work->text().simplified());
    query.bindValue(":path",               generate_path_file(ui->text_name_file->text().simplified()));

    query.exec();

    QMessageBox::information(this, "Уведомление", "Лабораторная работа добавлена в базу данных.");
}

// 1.6
void CreatePracticWindow::on_button_options_clicked()
{
    EditingToolsWindow *etw = new EditingToolsWindow;
    etw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    etw->exec();

    set_name_font(etw->get_name_font());
    set_id_font_color(etw->get_id_font_color());
    set_size_font(etw->get_size_font());

    etw->deleteLater();

    set_font_options();
}

void CreatePracticWindow::on_button_help_clicked()
{

}

// 1.6
void CreatePracticWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}
