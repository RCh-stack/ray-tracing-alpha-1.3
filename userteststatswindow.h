#ifndef USERTESTSTATSWINDOW_H
#define USERTESTSTATSWINDOW_H

#include <QDialog>
#include <QMessageBox>
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
    void set_system_options();
    void set_title_information();
    void output_table_information();

    void set_user_id(QString id) { user_id = id; }
    QString get_user_id() { return user_id; }

    void set_user_name(QString name) { user_name = name; }
    QString get_user_name() { return user_name; }

    void set_allow_view(bool allow) { allow_view = allow; }
    bool get_allow_view() { return allow_view; }

private slots:
    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_table_stats_cellDoubleClicked(int row, int column);

private:
    Ui::UserTestStatsWindow *ui;
    QString user_id;
    QString user_name;
    bool allow_view;
};

#endif // USERTESTSTATSWINDOW_H
