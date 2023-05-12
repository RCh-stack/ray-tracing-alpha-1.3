/*
 *      // autorizationwindow.h
 *
 *      Rus:
 *          Описание класса формы для авторизации пользователя в системе
 *
 *      Eng:
 *          Description of the form class for user authorization in the system
*/

#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <QDir>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QDialog
{
    Q_OBJECT

/*
 *  Rus:
 *      Область объявления основных методов класса
 *  Eng:
 *      Declaration scope of the main class methods
*/
public:
    explicit AuthorizationWindow(QWidget *parent = 0);
    ~AuthorizationWindow();

    void set_window_options();
    void user_authorization();
    void admin_authorization();

// **********************************************************

/*
*  Rus:
 *      Область объявления методов-событий
 *  Eng:
 *      Event method declaration scope
*/
private slots:
    void on_button_entry_clicked();
    void on_button_exit_clicked();
    void on_button_help_clicked();
    void on_radioButton_user_clicked();
    void on_radioButton_admin_clicked();
    void on_button_show_password_pressed();
    void on_button_show_password_released();

// **********************************************************

/*
 *  Rus:
 *      Область объявления переменных
 *  Eng:
 *      Variable declaration scope
*/
    void on_button_show_code_pressed();

    void on_button_show_code_released();

// **********************************************************

protected:
    void keyPressEvent(QKeyEvent *event);

// **********************************************************

private:
    Ui::AuthorizationWindow *ui;
    QSqlDatabase db;
};

#endif // AUTHORIZATIONWINDOW_H
