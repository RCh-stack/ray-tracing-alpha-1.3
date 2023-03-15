#include "edituserwindow.h"
#include "ui_edituserwindow.h"

EditUserWindow::EditUserWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserWindow)
{
    ui->setupUi(this);
    set_window_options();
    list_available_groups(0);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

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

// 1.3
void EditUserWindow::set_user_data_by_id()
{
    QSqlQuery query;
    query.prepare(select_user_by_id());
    query.bindValue(":id_user",     get_current_id());
    query.exec();

    if(query.next())
    {
        ui->text_login->setText(query.value("ID_User").toString());
        ui->text_password->setText(query.value("Password").toString());
        ui->text_code->setText(query.value("Code").toString());
        ui->text_fullname->setText(query.value("Fullname").toString());
        ui->comboBox_groups->setCurrentIndex(query.value("ID_Group").toInt() - 1);
        ui->comboBox_roles->setCurrentIndex(query.value("Role").toInt() - 1);
    }
}

// 1.3
void EditUserWindow::on_comboBox_roles_currentIndexChanged(int index)
{
    list_available_groups(index);
    if(index == 0)
    {
        ui->text_code->setEnabled(0);
        ui->comboBox_groups->setEnabled(1);
    }
    else
    {
        ui->text_code->setEnabled(1);
        ui->comboBox_groups->setEnabled(0);
    }
}

// 1.3
void EditUserWindow::list_available_groups(int id_role)
{
    ui->comboBox_groups->clear();
    if(id_role == 0)
    {
        ui->comboBox_groups->addItem("ДИПРБ_21/1");
        ui->comboBox_groups->addItem("ДИПРБ_21/2");
    }
    else
        ui->comboBox_groups->addItem("АСОИУ");
}

// 1.3
bool EditUserWindow::input_validation()
{
    if(ui->text_login->text().length() != 8)
    {
        QMessageBox::critical(this, "Ошибка", "Логин должен состоять из 8 символов!");
        return false;
    }
    else if(ui->text_fullname->text().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Не введено ФИО пользователя!");
        return false;
    }
    else if(ui->text_password->text().length() < 10 || ui->text_password->text().length() > 20)
    {
        QMessageBox::critical(this, "Ошибка", "Пароль должен состоять из не менее 10 символов");
        return false;
    }
    else if(ui->comboBox_roles->currentIndex() == 1 && ui->text_code->text().length() != 6)
    {
        QMessageBox::critical(this, "Ошибка", "Код доступа должен состоять из 6 чисел!");
        return false;
    }
    else if(ui->comboBox_roles->currentIndex() == 1 && !code_is_number(ui->text_code->text().simplified().toStdString()))
    {
        QMessageBox::critical(this, "Ошибка", "Код доступа должен состоять только из цифр!");
        return false;
    }

    return true;
}

// 1.3
void EditUserWindow::on_button_edit_clicked()
{
    if(input_validation())
        edit_current_user();
}

// 1.3
void EditUserWindow::edit_current_user()
{
    QSqlQuery query;
    query.prepare(edit_user());
    query.bindValue(":id_user",         ui->text_login->text().simplified());
    query.bindValue(":fullname",       ui->text_fullname->text().simplified());
    query.bindValue(":group",           get_id_group());
    query.bindValue(":role",              ui->comboBox_roles->currentIndex() + 1);
    query.bindValue(":password",     ui->text_password->text().simplified());
    query.bindValue(":code",            ui->text_code->text().simplified());
    query.exec();

    QMessageBox::information(this, "Уведомление", "Данные о пользователе изменены!");
    clear_input_fields();
}

// 1.3
int EditUserWindow::get_id_group()
{
    return ui->comboBox_roles->currentIndex() == 3 ? 0 : ui->comboBox_groups->currentIndex() + 1;
}

// 1.3
void EditUserWindow::clear_input_fields()
{
    ui->text_login->clear();
    ui->text_fullname->clear();
    ui->text_password->clear();
    ui->text_code->clear();
}

void EditUserWindow::on_button_exit_clicked()
{
    this->close();
}

void EditUserWindow::on_button_help_clicked()
{

}

// 1.3
bool EditUserWindow::code_is_number(const std::string& s)
{
    return !s.empty() && (s.find_first_not_of("0123456789") == s.npos);
}
