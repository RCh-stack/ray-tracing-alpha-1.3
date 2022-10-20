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
#include "ui_authorizationwindow.h"
#include "ui_mainwindow.h"

// -- конструктор класса --
AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    ui->text_password->setEchoMode(QLineEdit::Password); // -- режим пароля для поля ввода (замена символов на точки) --

    db = QSqlDatabase::addDatabase("QSQLITE");  // -- подключение базы данных --
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite"); // -- путь к базе данных --

    // -- если база не открылась --
    if (!db.open())
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text()); // -- выводим ошибку --
}

// -- деструктор класса --
AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

// -- попытка входа в систему --
void AuthorizationWindow::on_button_input_clicked()
{
    // -- если логин или пароль не указаны --
    if(ui->text_login->text().simplified().length() == 0 || ui->text_password->text().simplified().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Не введен логин или пароль!");
    }
    else
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM User WHERE ID_User = :login AND Password = :password");    // -- запрос на поиск пользователя в системе --
        query.bindValue(":login",        ui->text_login->text().simplified());  // -- логин --
        query.bindValue(":password", ui->text_password->text().simplified());   // -- пароль --
        query.exec();   // -- выполнение запроса к БД --
        if(!query.next())   // -- если запрос пустой --
            QMessageBox::warning(this, "Авторизация", "Пользователь не найден!");
        else
        {
            if(query.value("Role").toInt() == 1)    // -- если роль - пользователь --
            {
                MainWindow *mw = new MainWindow;
                mw->show(); // -- открываем стартовое окно приложения --
            }
        }
    }
}
