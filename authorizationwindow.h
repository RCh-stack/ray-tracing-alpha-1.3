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

private slots:
    void on_button_entry_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

private:
    Ui::AuthorizationWindow *ui;
    QSqlDatabase db;
};

#endif // AUTHORIZATIONWINDOW_H
