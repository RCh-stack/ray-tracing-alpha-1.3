/*
 *      // autorizationwindow.cpp
 *
 *      Форма для авторизации пользователя в системе
 *          Входные данные: логин, пароль
 *          Выходные данные: идентификатор пользователя, роль
 *
 *      Возможные ошибки:
 *          - не найдена база данных
 *          - ошибка подключения базы данных
 *          - отсутствие пользователя в базе
*/

#include "authorizationwindow.h"
#include "mainwindow.h"
#include "adminmainwindow.h"
#include "ui_authorizationwindow.h"
#include "ui_mainwindow.h"
#include "ui_adminmainwindow.h"

// -- конструктор класса --
AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    ui->text_password_user->setEchoMode(QLineEdit::Password); // -- режим пароля для поля ввода (замена символов на точки) --
    ui->text_code_admin->setEchoMode(QLineEdit::Password);
    ui->text_code_admin->setEnabled(0);

    db = QSqlDatabase::addDatabase("QSQLITE");  // -- подключение базы данных --
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite"); // -- путь к базе данных --
    //db.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "EducationSystem.sqlite");

    // -- если база не открылась --
    if (!db.open())
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text()); // -- выводим ошибку --

   set_window_options();
}

// -- деструктор класса --
AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

// -- установка дополнительных параметров для формы --
void AuthorizationWindow::set_window_options()
{
    QPixmap entry (":/icons/images/entry-button.png");
    QPixmap exit (":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap show_password(":/icons/images/show-password-button.png");

    QIcon ButtonEntry(entry);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);
    QIcon ButtonShow(show_password);

    ui->button_entry->setIcon(ButtonEntry);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_show_password->setIcon(ButtonShow);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// -- авторизация в системе --
void AuthorizationWindow::on_button_entry_clicked()
{
    if(ui->radioButton_user->isChecked())
    {
        if(ui->text_login_user->text().simplified().length() == 0 || ui->text_password_user->text().simplified().length() == 0)
            QMessageBox::critical(this, "Ошибка", "Не введен логин или пароль!"); // -- выводим ошибку --
        else
            user_authorization();
    }
    else if(ui->radioButton_admin->isChecked())
    {
        if(ui->text_login_user->text().simplified().length() == 0 || ui->text_password_user->text().simplified().length() == 0
                || ui->text_code_admin->text().simplified().length() == 0)
            QMessageBox::critical(this, "Ошибка", "Не введен логин, пароль или код доступа!"); // -- выводим ошибку --
        else
            admin_authorization();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не выбрана роль пользователя!");    // -- выводим ошибку --
    }
}

// -- авторизация под ролью пользователя --
void AuthorizationWindow::user_authorization()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE ID_User = :login AND Password = :password");    // -- запрос на поиск пользователя в системе --
    query.bindValue(":login",        ui->text_login_user->text().simplified());  // -- логин --
    query.bindValue(":password", ui->text_password_user->text().simplified());   // -- пароль --
    query.exec();   // -- выполнение запроса к БД --
    if(!query.next())   // -- если запрос пустой --
        QMessageBox::warning(this, "Авторизация", "Пользователь не найден!");
    else
    {
        if(query.value("Role").toInt() == 1)    // -- если роль - пользователь --
        {
            MainWindow *mw = new MainWindow;
            mw->setWindowFlags(Qt::Dialog);
            mw->show(); // -- открываем стартовое окно приложения --
        }
    }
}

// -- авторизация под ролью администратора --
void AuthorizationWindow::admin_authorization()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM User WHERE ID_User = :login AND Password = :password AND Code = :code");    // -- запрос на поиск пользователя в системе --
    query.bindValue(":login",        ui->text_login_user->text().simplified());  // -- логин --
    query.bindValue(":password", ui->text_password_user->text().simplified());   // -- пароль --
    query.bindValue(":code",        ui->text_code_admin->text().simplified()); // -- код доступа --
    query.exec();   // -- выполнение запроса к БД --
    if(!query.next())   // -- если запрос пустой --
        QMessageBox::warning(this, "Авторизация", "Пользователь не найден!");
    else
    {
        if(query.value("Role").toInt() == 2)    // -- если роль - администратор --
        {
            AdminMainWindow *amw = new AdminMainWindow;
            amw->setWindowFlags(Qt::Dialog);
            amw->show(); // -- открываем стартовое окно приложения --
        }
    }
}

// -- выход из приложения --
void AuthorizationWindow::on_button_exit_clicked()
{
    this->close();
}

// -- получение справки --
void AuthorizationWindow::on_button_help_clicked()
{

}

// -- установка роли "Пользователь" -
void AuthorizationWindow::on_radioButton_user_clicked()
{
    if(ui->radioButton_user->isChecked())
        ui->text_code_admin->setEnabled(0);
}

// -- установка роли "Администратор" --
void AuthorizationWindow::on_radioButton_admin_clicked()
{
    if(ui->radioButton_admin->isChecked())
        ui->text_code_admin->setEnabled(1);
}

// -- показывать пароль -- // 1.1
void AuthorizationWindow::on_button_show_password_pressed()
{
    ui->text_password_user->setEchoMode(QLineEdit::Normal);
}

// -- скрыть пароль -- // 1.1
void AuthorizationWindow::on_button_show_password_released()
{
    ui->text_password_user->setEchoMode(QLineEdit::Password);
}
