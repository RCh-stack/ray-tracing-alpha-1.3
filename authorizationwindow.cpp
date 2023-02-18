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

    db = QSqlDatabase::addDatabase("QSQLITE");  // -- подключение базы данных --
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite"); // -- путь к базе данных --
    //db.setDatabaseName(QDir::toNativeSeparators(QApplication::applicationDirPath()) + "EducationSystem.sqlite");

    // -- если база не открылась --
    if (!db.open())
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text()); // -- выводим ошибку --

    QPixmap entry (":/icons/images/entry-button.png");
    QPixmap exit (":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonEntry(entry);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);

    ui->button_entry->setIcon(ButtonEntry);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// -- деструктор класса --
AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

// -- попытка входа в систему --
void AuthorizationWindow::on_button_entry_clicked()
{
    // -- если логин или пароль не указаны --
    if(ui->text_login_user->text().simplified().length() == 0 || ui->text_password_user->text().simplified().length() == 0)
    {
        QMessageBox::critical(this, "Ошибка", "Не введен логин или пароль!");
    }
    else
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
                mw->show(); // -- открываем стартовое окно приложения --
            }
            if(query.value("Role").toInt() == 2)
            {
                AdminMainWindow *mw = new AdminMainWindow;
                mw->show();
            }
        }
    }
}

void AuthorizationWindow::on_button_exit_clicked()
{

}

void AuthorizationWindow::on_button_help_clicked()
{

}
