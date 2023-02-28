#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = 0);
    ~AuthorizationWindow();
    void user_authorization();
    void admin_authorization();

private slots:
    void on_button_entry_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_radioButton_user_clicked();

    void on_radioButton_admin_clicked();

private:
    Ui::AuthorizationWindow *ui;
    QSqlDatabase db;
};

#endif // AUTHORIZATIONWINDOW_H
