/*
 *      // autorizationwindow.cpp
 *
 *      Rus:
 *          Реализация класса формы для авторизации пользователя в системе
 *
 *      Eng:
 *          Implementation of the form class for user authorization in the system
*/

#include "authorizationwindow.h"
#include "mainwindow.h"
#include "adminmainwindow.h"
#include "ui_authorizationwindow.h"
#include "ui_mainwindow.h"
#include "ui_adminmainwindow.h"

/*
 *  Rus:
 *      Конструктор класса AuthorizationWindow
 *      Инициализирует параметры формы, режим ввода пароля и кода, подключает базу данных
 *  Eng:
 *      AuthorizationWindow class constructor
 *      Initializes form parameters, password and code input mode, connects the database
*/
AuthorizationWindow::AuthorizationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationWindow)
{
    ui->setupUi(this);
    ui->text_password_user->setEchoMode(QLineEdit::Password);
    ui->text_code_admin->setEchoMode(QLineEdit::Password);
    ui->text_code_admin->setEnabled(0);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(NULL, QObject::tr("Ошибка!"), db.lastError().text());

   set_window_options();
}

/*
 *  Rus:
 *      Деструктор класса
 *      Вызывается при закрытии формы
 *  Eng:
 *      Class destructor
  *     Called when the form is closed
*/
AuthorizationWindow::~AuthorizationWindow()
{
    delete ui;
}

/*
 *  Rus:
 *      Функция для установки параметров окна
 *      Устанавливает параметры для отображаемых на форме элементов интерфейса
 *  Eng:
 *      Function to set window parameters
  *     Sets parameters for interface elements displayed on the form
*/
void AuthorizationWindow::set_window_options()
{
    QPixmap entry (":/icons/images/entry-button.png");
    QPixmap exit (":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap show_password(":/icons/images/show-password-button.png");
    QPixmap show_code(":/icons/images/show-password-button.png");

    QIcon ButtonEntry(entry);
    QIcon ButtonExit(exit);
    QIcon ButtonInformation(help);
    QIcon ButtonShowPassword(show_password);
    QIcon ButtonShowCode(show_code);

    ui->button_entry->setIcon(ButtonEntry);
    ui->button_exit->setIcon(ButtonExit);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_show_password->setIcon(ButtonShowPassword);
    ui->button_show_code->setIcon(ButtonShowCode);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

/*
 *  Rus:
 *      Событие при нажатии на кнопку "Войти"
 *      Вызывает функцию для авторизации пользователя по выбранной роли при нажатии на кнопку
 *  Eng:
 *      Event when clicking on the "Login" button
 *      Calls a function to authorize the user by the selected role when the button is clicked
*/
void AuthorizationWindow::on_button_entry_clicked()
{
    if(ui->radioButton_user->isChecked())
    {
        if(ui->text_login_user->text().simplified().length() == 0 || ui->text_password_user->text().simplified().length() == 0)
            QMessageBox::critical(this, "Ошибка", "Не введен логин или пароль!");
        else
            user_authorization();
    }
    else if(ui->radioButton_admin->isChecked())
    {
        if(ui->text_login_user->text().simplified().length() == 0 || ui->text_password_user->text().simplified().length() == 0
                || ui->text_code_admin->text().simplified().length() == 0)
            QMessageBox::critical(this, "Ошибка", "Не введен логин, пароль или код доступа!");
        else
            admin_authorization();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка", "Не выбрана роль пользователя!");    // -- выводим ошибку --
    }
}

/*
 *  Rus:
 *      Функция для авторизации под ролью "Пользователь"
 *      Выполняет запрос на получение данных по введенным данным и передает их при открытии главного меню подсистемы "Студент"
 *  Eng:
 *      Function for authorization under the role "User"
 *      Performs a request to receive data on the entered data and transmits them when the main menu of the "Student" subsystem is opened
*/
void AuthorizationWindow::user_authorization()
{
    QSqlQuery query;
    query.prepare(select_user());
    query.bindValue(":login",        ui->text_login_user->text().simplified());
    query.bindValue(":password", ui->text_password_user->text().simplified());
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Авторизация", "Пользователь не найден!");
    else
    {
        if(query.value("Role").toInt() == 1)
        {
            MainWindow *mw = new MainWindow;
            mw->setWindowFlags(Qt::Dialog);
            mw->show();
        }
    }
}

/*
 *  Rus:
 *      Функция для авторизации под ролью "Администратор"
 *      Выполняет запрос на получение данных по введенным данным и передает их при открытии главного меню подсистемы "Преподаватель"
 *  Eng:
 *      Function for authorization under the role "Administrator"
 *      Performs a request to receive data on the entered data and transmits them when the main menu of the "Teacher" subsystem is opened
*/
void AuthorizationWindow::admin_authorization()
{
    QSqlQuery query;
    query.prepare(select_admin());
    query.bindValue(":login",        ui->text_login_user->text().simplified());
    query.bindValue(":password", ui->text_password_user->text().simplified());
    query.bindValue(":code",        ui->text_code_admin->text().simplified());
    query.exec();
    if(!query.next())
        QMessageBox::warning(this, "Авторизация", "Пользователь не найден!");
    else
    {
        if(query.value("Role").toInt() == 2)
        {
            AdminMainWindow *amw = new AdminMainWindow;
            amw->setWindowFlags(Qt::Dialog);
            amw->show();
        }
    }
}

/*
 *  Rus:
 *      Событие при нажатии на кнопку "Выйти"
 *      Закрывает форму для авторизации при нажатии на кнопку
 *  Eng:
 *      Event when clicking on the "Exit" button
 *      Closes the authorization form when the button is clicked
*/
void AuthorizationWindow::on_button_exit_clicked()
{
    this->close();
}

/*
 *  Rus:
 *      Событие при нажатии на кнопку "Получить справку"
 *      Открывает форму с контекстной справкой для данного раздела
 *  Eng:
 *      Event when clicking on the "Get help" button
*       Opens a form with contextual help for this topic
*/
void AuthorizationWindow::on_button_help_clicked()
{

}

/*
 *  Rus:
 *      Событие при переключении выбранной роли на "Пользователь"
 *      Устанавливает доступность поля ввода кода доступа при выбранной роли "Пользователь"
 *  Eng:
 *      Event when switching the selected role to "User"
 *      Sets the availability of the access code entry field when the selected role is "User"
*/
void AuthorizationWindow::on_radioButton_user_clicked()
{
    if(ui->radioButton_user->isChecked())
    {
        ui->text_code_admin->clear();
        ui->text_code_admin->setEnabled(0);
    }
}

/*
 *  Rus:
 *      Событие при переключении выбранной роли на "Администратор"
 *      Устанавливает доступность поля ввода кода доступа при выбранной роли "Администратор"
 *  Eng:
 *      Event when switching the selected role to "Administrator"
 *      Sets the availability of the access code entry field when the selected role is "Administrator"
*/
void AuthorizationWindow::on_radioButton_admin_clicked()
{
    if(ui->radioButton_admin->isChecked())
        ui->text_code_admin->setEnabled(1);
}

/*
 *  Rus:
 *      Событие при зажатой кнопке "Показать пароль"
 *      Устанавливает режим отображения поля ввода пароля при зажатой кнопке
 *  Eng:
 *      Event when the "Show password" button is pressed
 *      Sets the display mode of the password input field when the button is pressed
*/
void AuthorizationWindow::on_button_show_password_pressed()
{
    ui->text_password_user->setEchoMode(QLineEdit::Normal);
}

/*
 *  Rus:
 *      Событие при отжатии кнопки "Показать пароль"
 *      Устанавливает режим отображения поля ввода пароля после отжатия кнопки
 *  Eng:
 *      Event when the "Show password" button is pressed
 *      Sets the display mode of the password input field after the button is released
*/
void AuthorizationWindow::on_button_show_password_released()
{
    ui->text_password_user->setEchoMode(QLineEdit::Password);
}

// 1.3
void AuthorizationWindow::on_button_show_code_pressed()
{
    ui->text_code_admin->setEchoMode(QLineEdit::Normal);
}

// 1.3
void AuthorizationWindow::on_button_show_code_released()
{
    ui->text_code_admin->setEchoMode(QLineEdit::Password);
}
