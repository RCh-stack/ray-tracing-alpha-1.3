#ifndef USERTESTSTATSWINDOW_H
#define USERTESTSTATSWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class UserTestStatsWindow;
}

class UserTestStatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserTestStatsWindow(QWidget *parent = 0);
    ~UserTestStatsWindow();

    void set_window_options();
    void set_title_information();
    QString get_name_theme_test(int id_theme);
    void output_table_information();

    void set_user_id(QString id) { user_id = id; }
    QString get_user_id() { return user_id; }

    void set_user_name(QString name) { user_name = name; }
    QString get_user_name() { return user_name; }

private slots:
    void on_button_exit_clicked();

    void on_button_help_clicked();

private:
    Ui::UserTestStatsWindow *ui;
    QSqlDatabase db;
    QString user_id;
    QString user_name;
};

#endif // USERTESTSTATSWINDOW_H
